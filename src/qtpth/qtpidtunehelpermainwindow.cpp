#include "qtpidtunehelpermainwindow.h"
#include "ui_qtpidtunehelpermainwindow.h"

QtPidTuneHelperMainWindow::QtPidTuneHelperMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::QtPidTuneHelperMainWindow)
{
  ui->setupUi(this);
}

QtPidTuneHelperMainWindow::~QtPidTuneHelperMainWindow()
{
  delete ui;
}
