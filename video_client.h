#ifndef VIDEO_CLIENT_H
#define VIDEO_CLIENT_H

#include <QWidget>
#include<QtNetwork>
#include<QTcpServer>
#include<QTcpSocket>
#include<QImage>
#include<QImageReader>
#include<QTime>
#include<QDebug>
#include<QMessageBox>
#include<QFileDialog>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv/cv.h>
#include<opencv2/opencv.hpp>
//#include<QThread>

using namespace cv;
class video_client : public QObject
{
    Q_OBJECT

public:
    video_client();
    ~video_client();
public:
//    quint64 blockSize;
    QTcpSocket *video_tcpSocket;
    VideoCapture *video_cap;
    QTimer *SendImagetimer;
public:
    static QString IpAddress;
private:
    bool stopFlag;
private slots:
    void SendVideo();
    void displayError(QAbstractSocket::SocketError);
    void run();
    void enable_run();
    void disable_run();
signals:
    void signalSendImageShow(const QImage &image);

};

#endif // VIDEO_CLIENT_H
