#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
#include <QSqlError>

MainWidget::MainWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MainWidget)
{
  ui->setupUi(this);

  //Настройки для подключения к СУБД MySQL
//  db = QSqlDatabase::addDatabase("QMYSQL");
//  db.setHostName("192.168.1.2"); //адрес или имя компьютера, на котором запущен MySQL
//  db.setDatabaseName("test");    //имя вашей БД
//  db.setUserName("root");        //имя пользователя базы, указанной в setDatabaseName()
//  db.setPassword("");            //пароль пользователя, указанного в setPassword()

  //Настройки для подключения к СУБД Interbase/Firebird
  db = QSqlDatabase::addDatabase("QIBASE");
  db.setDatabaseName("d:\\Tutorials\\TUTORIALDB.FDB"); //Ваш путь к файлу БД
  db.setUserName("SYSDBA");    //или какой-то другой пользователь БД
  db.setPassword("masterkey"); //или пароль пользователя, указанного через setUserName()

  //Проверка соединения с БД
  if (!db.open()){
    qDebug() << db.lastError().text();
    return;
  }
  else {
    qDebug() << "Success!";
  }

  model = new QSqlTableModel(this, db);
  //Указываем стратегию кэширования изменений
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);
  //Указываем имя таблицы, данные которой хотим загрузить в модель
  model->setTable("products");
  //Загрузка актуальных данных таблицы из БД
  model->select();
  //Назначаем модель объектам представлений
  ui->tableView->setModel(model);
  ui->comboBox->setModel(model);
  ui->comboBox->setModelColumn(2);
}

MainWidget::~MainWidget()
{
  delete ui;
}

void MainWidget::on_btnSubmit_clicked()
{
  //Применение всех закэшированных изменений к БД
  model->submitAll();
}

void MainWidget::on_btnRevert_clicked()
{
  //Откат всех закэшированных (то есть не сохраненных в БД) изменений
  model->revertAll();
}
