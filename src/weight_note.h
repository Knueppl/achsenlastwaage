#ifndef _WEIGHT_NOTE_H_
#define _WEIGHT_NOTE_H_

#include <QString>
#include <QFile>
#include <QProcess>
#include "weight_list.h"

class WeightNote
{
public:
    WeightNote(const QString& templateFile);

    void setWeight(const Weight* weight);
    void saveFile(void);

    void compile(void) const;

    static void setRootDirectory(const QString& rootDirectory);
    static int getCurrentWeightNoteNumber(void);

private:
    QString       m_fileName;
    QString       m_text;
    const Weight* m_weight;

    void cleanUpDirectory(void) const;

    static QString  s_rootDirectory;
    static QProcess s_process;
    static int      s_currentWeightNoteNumber;
};

#endif
