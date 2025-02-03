#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "mainwindow.h"
#include "loginsite.h"

const QString serverUrl = "http://192.168.1.127/distance"; // Replace with the IP address of your ESP32
void checkDistance(QNetworkAccessManager *manager) {
    QNetworkRequest request((QUrl(serverUrl)));
    QNetworkReply *reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QString value = reply->readAll().trimmed();
            bool ok;
            int distance = value.toInt(&ok);
            qDebug () << "ok";
            qDebug () <<distance;

            if (ok && distance < 6) {
                QMessageBox::warning(nullptr, "Warning", "Object detected closer than 5 cm!");
            }
        } else {
            qDebug() << "Network error:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginSite w;
    w.show();

    QNetworkAccessManager manager;
    QTimer timer;

    QObject::connect(&timer, &QTimer::timeout, [&]() { checkDistance(&manager); });
    timer.start(1000); // Check distance every second

    return a.exec();
}
