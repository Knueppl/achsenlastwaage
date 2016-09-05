#ifndef ___CHECK_WEIGHTING_DIALOG_H___
#define ___CHECK_WEIGHTING_DIALOG_H___

#include <QDialog>

#include <Weighting.h>

namespace Ui {
   class CheckWeightingDialog;
}

class CheckWeightingDialog : public QDialog
{
   Q_OBJECT

public:
   explicit CheckWeightingDialog(Weighting* weighting, QWidget* parent = 0);

private:
   Ui::CheckWeightingDialog* _ui;
};

#endif

