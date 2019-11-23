#include "qtpidtunehelpermainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QtPidTuneHelperMainWindow w;
  w.show();

  return a.exec();
}
