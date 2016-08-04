#ifndef ___FZW12_H___
#define ___FZW12_H___

#include "Scale.h"
#include "SerialPort.h"

#include <QTimer>

class Fzw12 : public Scale
{
  Q_OBJECT

public:
  Fzw12(const char* port);
  ~Fzw12(void);

public slots:
  virtual void start(const Vehicle* vehicle, const int goodId, const int supplierId, const int fieldId);
  virtual void cancel(void);

private slots:
  void readPort(void);
  void stop(Weighting* weighting = 0);

private:
  SerialPort* m_port;
  QTimer      m_timer;
};

#endif
