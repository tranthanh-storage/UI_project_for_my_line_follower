#include "automode.h"
#include "ui_automode.h"
#include "mainwindow.h"

autoMode::autoMode(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::autoMode)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &autoMode::onNetworkReply2);
}

autoMode::~autoMode()
{
    delete ui;
}

void autoMode::on_pushButton_clicked()
{
    this->hide();
    MainWindow *v = new MainWindow ();
    v->show();
}
void autoMode::onNetworkReply2(QNetworkReply* reply)
{
    QString response = reply->readAll();
    if (reply->error() == QNetworkReply::NoError) {
        ui->label->setText("Response: " + response);
    } else {
        ui->label->setText("Error: " + reply->errorString());
    }
    qDebug () << response;
    reply->deleteLater();
}



void autoMode::on_start_clicked()
{
    QNetworkRequest request(QUrl("http://192.168.1.127/automode")); // Replace with your ESP32 IP address
    networkManager->get(request);
}

