#include <QThread>
#include <QMutex>
#include <iostream>

QMutex m1;
QMutex m2;

class MyThread1 : public QThread
{
public:
  void run();
};

void MyThread1::run()
{
  m1.lock();
  m2.lock();

  m1.unlock();
  m2.unlock();
}

class MyThread2 : public QThread
{
public:
  void run();
};

void MyThread2::run()
{
  m2.lock();
  m1.lock();

  m1.unlock();
  m2.unlock();
}

int main()
{
  MyThread1 t1;
  MyThread2 t2;

  t1.run();
  t2.run();

  t1.wait();
  t2.wait();
}
