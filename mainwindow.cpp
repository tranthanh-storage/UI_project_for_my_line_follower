#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "automode.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
   connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkReply);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_up_clicked()
{
    QNetworkRequest request(QUrl("http://172.20.10.13/goStraight")); // Replace with your ESP32 IP address
    networkManager->get(request);
}



void MainWindow::on_left_clicked()
{
    QNetworkRequest request(QUrl("http://172.20.10.13/turnLeft")); // Replace with your ESP32 IP address
    networkManager->get(request);
}



void MainWindow::on_stop_clicked()
{
    QNetworkRequest request(QUrl("http://172.20.10.13/stop")); // Replace with your ESP32 IP address
    networkManager->get(request);
}



void MainWindow::on_right_clicked()
{
    QNetworkRequest request(QUrl("http://172.20.10.13/turnRight")); // Replace with your ESP32 IP address
    networkManager->get(request);
}



void MainWindow::on_down_clicked()
{
    QNetworkRequest request(QUrl("http://172.20.10.13/goBack")); // Replace with your ESP32 IP address
    networkManager->get(request);
}
void MainWindow::onNetworkReply(QNetworkReply* reply)
{
    QString response = reply->readAll();
    if (reply->error() == QNetworkReply::NoError) {
        ui->statusLabel->setText("Response: " + response);
    } else {
        ui->statusLabel->setText("Error: " + reply->errorString());
    }
    qDebug () << response;
    reply->deleteLater();
}




void MainWindow::on_pushButton_clicked()
{
    if (ui->horizontalSlider->value() < 25) {
        QNetworkRequest request(QUrl("http://192.168.1.127/lowSpeed")); // Replace with your ESP32 IP address
        networkManager->get(request);
    }
    if (ui->horizontalSlider->value() >=25 && ui->horizontalSlider->value() < 80) {
        QNetworkRequest request(QUrl("http://192.168.1.127/midSpeed")); // Replace with your ESP32 IP address
        networkManager->get(request);
    }
    if (ui->horizontalSlider->value() >=80) {
        QNetworkRequest request(QUrl("http://192.168.1.127/highSpeed")); // Replace with your ESP32 IP address
        networkManager->get(request);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    autoMode *x = new autoMode ();
    x->show();
}

