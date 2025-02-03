#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QDebug>

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

    void on_up_clicked();

    void on_left_clicked();

    void on_stop_clicked();

    void on_right_clicked();

    void on_down_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void onNetworkReply(QNetworkReply* reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;

};

#endif // MAINWINDOW_H

