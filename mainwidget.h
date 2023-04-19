#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
  Q_OBJECT

public:
  explicit MainWidget(QWidget *parent = 0);
  ~MainWidget();

private slots:

  void on_btnSubmit_clicked();

  void on_btnRevert_clicked();

private:
  Ui::MainWidget *ui;
  QSqlDatabase db;
  QSqlTableModel* model;
};

#endif // MAINWIDGET_H
