#ifndef VIDEO_SERVER_H
#define VIDEO_SERVER_H

#include <QWidget>
#include<QTcpSocket>
#include<QTcpServer>
#include<QString>
#include<QtNetwork>
#include<QMessageBox>
#include<QImage>

class video_server : public QWidget
{
    Q_OBJECT
public:
    video_server();
    ~video_server();
public:
    QTcpServer *video_tcpServer;
    QTcpSocket *video_tcpServerConnection;
    QStringList *fortunes;
    QImage *img;
    quint64 basize;
private:
    bool stopFlag;
public slots:
    void run();
    void enable_run();
    void disable_run();
    void sendFortune();
    void DisplayError(QAbstractSocket::SocketError socketError);
    void ReadMyData();
signals:
    void signalRecvImageShow(const QImage &image);
};

#endif // VIDEO_SERVER_H
