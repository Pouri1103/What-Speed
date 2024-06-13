#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <chrono>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>


//-------------------------

QSqlDatabase db;
int averageAll=0,count=0;

//-------------------------

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("ListResult.db");
    db.open();
    db.exec("create table list(Name text unique, ValueInt integer)");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Start_clicked()
{
    int average=0;
    for (int i=1;i<=5;i++)
    {
        auto start = std::chrono::high_resolution_clock::now();

        // For additional processing only
        long number=22222,a=0,a2=222222,a3=0;
        for (long i=1;i<=number;i++)
            a %=i;
        for (long i=1;i<=a2;i++)
            a2 -=1;
        for (long i=1;i<=a2;i++)
            a3 +=1;

        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        ui->Display->setText(ui->Display->toPlainText() + QString::number(time.count()) + "   ");
        average +=time.count();
    }
    ui->Display->setText(ui->Display->toPlainText() + "-->   " + QString::number(average/5) + "µs \n");

    averageAll +=average/5;
    count++;

    ui->Average->setText(QString::number(averageAll/count));
    ui->Count->setText(QString::number(count));
}


void MainWindow::on_saveName_clicked()
{
    QString name = ui->Name->text();
    QString valueInt = ui->Average->text();

    QSqlQuery q;
    q.prepare("insert into list(name,valueInt) values(:name,:valueInt)");
    q.bindValue(":name",name);
    q.bindValue(":valueInt",valueInt);

    if (q.exec())
        QMessageBox::information(this,"Saved !","Data saved successfully !");

    else if (q.lastError().nativeErrorCode().toInt() == 2067)
        QMessageBox::critical(this,"Non-unique (Duplicate value) !!!","Please enter a unique name !!!");

    else
        QMessageBox::critical(this,"Error !!!", q.lastError().text());
}


void MainWindow::on_actionStart_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionDatas_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);

    setTable();
}


void MainWindow::on_deleteName_clicked()
{
    QString name2 = ui->Name_2->text();
    ui->Name_2->setText("");

    // QSqlQuery("delete from list where name='"+name2+"'");  OR
    QSqlQuery q;
    q.prepare("delete from list where name=:name");
    q.bindValue(":name",name2);
    q.exec();

    setTable();
}


void MainWindow::setTable()
{
    QSqlTableModel *model = new QSqlTableModel(nullptr,db);
    model->setTable("list");
    model->select();
    ui->tableView->setModel(model);

    ui->tableView->setColumnWidth(0,300);
}

