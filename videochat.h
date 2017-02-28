#ifndef VIDEOCHAT_H
#define VIDEOCHAT_H

#include <QWidget>
#include <QImage>
#include <QThread>

#include "video_client.h"
#include "video_server.h"
#include "audioGet.h"

namespace Ui {
class VideoChat;
}

class VideoChat : public QWidget
{
    Q_OBJECT

public:
    explicit VideoChat(QWidget *parent = 0);
    ~VideoChat();
public:
    static QString IpAddress;

private slots:
    void on_start_clicked();
    void on_stop_clicked();
//    void on_setIp_clicked();
    void showSendImage(const QImage &iamge);
    void showRecvImage(const QImage &iamge);

private:
    Ui::VideoChat *ui;

    QThread *videoClientFather;
    QThread *videoServerFather;
    QThread *udpThreadFather;

    AudioGet *audioGet;
signals:
    void signalStart();
    void signalStop();
};

#endif // VIDEOCHAT_H
