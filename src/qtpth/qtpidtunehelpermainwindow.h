#ifndef QTPIDTUNEHELPERMAINWINDOW_H
#define QTPIDTUNEHELPERMAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>

namespace Ui {
class QtPidTuneHelperMainWindow;
}

class QtPidTuneHelperMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit QtPidTuneHelperMainWindow(QWidget *parent = nullptr);
  ~QtPidTuneHelperMainWindow();

  // setters:
  void setPen(const QPen& pen);
  void setBrush(const QBrush& brush);
  void setText(const QString& text);

  // getters:
  QPen pen() const { return mLabel->pen(); }
  QBrush brush() const { return mLabel->brush(); }
  QString text() const { return mLabel->text(); }

  // other methods:
  void updatePosition(double value);

private:
  QCPAxis* mAxis;
  QPointer<QCPItemTracer> mDummyTracer;
  QPointer<QCPItemLine> mArrow;
  QPointer<QCPItemText> mLabel;

private:
  Ui::QtPidTuneHelperMainWindow *ui;
};

#endif // QTPIDTUNEHELPERMAINWINDOW_H
