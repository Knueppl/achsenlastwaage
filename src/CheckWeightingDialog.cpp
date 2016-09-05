#include "CheckWeightingDialog.h"
#include "ui_CheckWeightingDialog.h"

#include <QDebug>

CheckWeightingDialog::CheckWeightingDialog(Weighting* weighting, QWidget* parent)
 : QDialog(parent),
   _ui(new Ui::CheckWeightingDialog)
{
   _ui->setupUi(this);
   _ui->_pushAccept->setText(QString());
   _ui->_pushReject->setText(QString());

   QPixmap iconReject;
   QPixmap iconAccept;

   switch (weighting->axes ())
   {
   case 2:
      {
         iconReject = QPixmap(":vehicle/truck-two-axes-boxed-r.png");
         iconAccept = QPixmap(":vehicle/truck-two-axes-boxed-g.png");
      }
      break;

   case 3:
         iconReject = QPixmap(":vehicle/truck-three-axes-boxed-r.png");
         iconAccept = QPixmap(":vehicle/truck-three-axes-boxed-g.png");
      break;

   case 4:
         iconReject = QPixmap(":vehicle/truck-four-axes-boxed-r.png");
         iconAccept = QPixmap(":vehicle/truck-four-axes-boxed-g.png");
      break;

   case 5:
         iconReject = QPixmap(":vehicle/truck-five-axes-boxed-r.png");
         iconAccept = QPixmap(":vehicle/truck-fiveh-axes-boxed-g.png");
      break;

   default:
      qDebug() << __PRETTY_FUNCTION__ << ": axes count " << weighting->axes () << " is invalid.";
      this->reject();
      return;
   }

   _ui->_pushAccept->setIconSize(iconAccept.size());
   _ui->_pushReject->setIconSize(iconReject.size());
   _ui->_pushAccept->setIcon(iconAccept);
   _ui->_pushReject->setIcon(iconReject);

   this->connect(_ui->_pushAccept, SIGNAL(clicked()), this, SLOT(accept()));
   this->connect(_ui->_pushReject, SIGNAL(clicked()), this, SLOT(reject()));
}
