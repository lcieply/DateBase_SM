#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QtCore>
#include <QComboBox>

class MyTimer : public QObject
{
    Q_OBJECT
public:
    MyTimer(QComboBox **combo);
    QTimer* myTimer;

signals:

public slots:
    void MySlot(QComboBox* combo);
};

#endif // MYTIMER_H
