#include "weight_note.h"
#include <QDebug>
#include <QStringList>
#include <QDir>

QString WeightNote::s_rootDirectory("");
QProcess WeightNote::s_process;
int WeightNote::s_currentWeightNoteNumber(0);

WeightNote::WeightNote(const QString& templateFile)
{
    QString directory(s_rootDirectory);
    directory.append("template/");
    directory.append(templateFile);
    QFile file(directory);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Fehler beim öffnen des Wiegescheins-Template: " << directory;
    }
    else
    {
        QTextStream stream(&file);

        m_text = stream.readAll();
        file.close();
    }
}

void WeightNote::saveFile(void)
{
    QString fileName("Wiegeschein_Nr.");
    fileName.append(QString::number(this->getCurrentWeightNoteNumber()));
    fileName.append(".tex");
    QString tmp(s_rootDirectory);
    QFile file(tmp.append(fileName));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Kann Wiegeschein nicht speichern!";
        qDebug() << "Datei: " << fileName;
    }
    else
    {
        QTextStream textStream(&file);
        m_text.replace("<Wiegeschein>", QString::number(s_currentWeightNoteNumber));
        textStream << m_text;
        file.close();
        m_fileName = fileName;
    }
    qDebug() << "fileName: " << m_fileName;
}

void WeightNote::compile(void) const
{
    if (m_fileName.isEmpty())
    {
        return;
    }

    QStringList arg;
    arg << m_fileName;
    s_process.setWorkingDirectory(s_rootDirectory);
    s_process.start("pdflatex", arg);

    if (!s_process.waitForFinished())
    {
        qDebug() << "Fehler mit LaTex!";
    }
    else
    {
        this->cleanUpDirectory();
    }
}

void WeightNote::cleanUpDirectory(void) const
{
    if (m_fileName.isEmpty())
    {
        return;
    }

    QDir dir(s_rootDirectory);
    QString tmp(m_fileName);
    tmp.replace(".tex", ".aux");
    dir.remove(tmp);
    tmp.replace(".aux", ".log");
    dir.remove(tmp);
}

void WeightNote::setWeight(const Weight* weight)
{
    m_weight = weight;

    m_text.replace("<Fahrzeug>", weight->vehicle());
    m_text.replace("<Lieferant>", weight->supplier());
    m_text.replace("<Ware>", weight->product());
    m_text.replace("<Datum/Uhrzeit>", weight->dateTime().toString());
    m_text.replace("<Gesamtgewicht>", QString::number(weight->brutto()).append(" kg"));
    m_text.replace("<Tara>", QString::number(weight->tara()).append(" kg"));
    m_text.replace("<Netto>", QString::number(weight->netto()).append(" kg"));
}

void WeightNote::setRootDirectory(const QString& rootDirectory)
{
    s_rootDirectory = rootDirectory;
}

int WeightNote::getCurrentWeightNoteNumber(void)
{
    QDir dir(s_rootDirectory);

    while (1)
    {
        s_currentWeightNoteNumber++;
        QString fileName("Wiegeschein_Nr.");
        fileName.append(QString::number(s_currentWeightNoteNumber));
        fileName.append(".pdf");

        if (!dir.exists(fileName))
        {
            return s_currentWeightNoteNumber;
        }
    }
}
