#include "DummyScale.h"

#include <QDebug>

DummyScale::DummyScale(void)
    : Scale()
{

}

DummyScale::~DummyScale(void)
{

}

void DummyScale::receiveAxisWeight(const int kg)
{
    this->setNextAxisWeight(kg);
}

