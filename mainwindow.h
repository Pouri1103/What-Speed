#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Start_clicked();

    void on_saveName_clicked();

    void on_actionDatas_triggered();

    void on_actionStart_triggered();

    void on_deleteName_clicked();

    void setTable();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
