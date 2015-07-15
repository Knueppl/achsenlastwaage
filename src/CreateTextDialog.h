#ifndef ___CREATE_TEXT_DIALOG_H___
#define ___CREATE_TEXT_DIALOG_H___

namespace Ui {
class CreateTextDialog;
}

#include <QDialog>
#include <QString>

class CreateTextDialog : public QDialog
{
public:
    CreateTextDialog(QWidget* parent = 0);

    QString text(void) const;

private:
    Ui::CreateTextDialog* _ui;
};

#endif
