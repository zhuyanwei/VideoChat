#include "video_client.h"

QString video_client::IpAddress;

video_client::video_client()
{
    stopFlag=true;
}
video_client::~video_client()
{
//    stopFlag=false;
//    delete video_client;
//    close();

}
void video_client::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<"transform fail";
}
void video_client::enable_run()
{
    stopFlag = false;
    SendImagetimer->start(30);
    qDebug()<<"SendImagetimer start";
}
void video_client::disable_run()
{
    stopFlag = true;
    SendImagetimer->stop();
    video_tcpSocket->disconnectFromHost();
    qDebug()<<"SendImagetimer stop";
}
void video_client::run()
{
//    if(stopFlag) return;
    qDebug()<<"videoClient thread run";
    SendImagetimer=new QTimer();
    connect(SendImagetimer,SIGNAL(timeout()),this,SLOT(SendVideo()));


    video_tcpSocket = new QTcpSocket(this);
    video_cap = new VideoCapture(0);
    video_cap->set(CV_CAP_PROP_FRAME_WIDTH,640);
    video_cap->set(CV_CAP_PROP_FRAME_HEIGHT,480);
    if(!video_cap->isOpened()){
//        QMessageBox::information(this,tr("warning"),tr("camera cannot open"));
        qDebug()<<"camera cannot open";
    }
//    SendVideo();
}
void video_client::SendVideo()
{
//    blockSize=0;
    qDebug()<<"SendVideo start";
    video_tcpSocket->abort();
    video_tcpSocket->connectToHost(QHostAddress(IpAddress),8888);
    Mat frame;
    *video_cap>>frame;
    cvtColor(frame,frame,CV_BGR2RGB);

    QByteArray byte;
    QBuffer buf(&byte);
    QImage image((unsigned const char*)frame.data,frame.cols,frame.rows,QImage::Format_RGB888);
    image.save(&buf,"JPEG");
    QByteArray ss=qCompress(byte,1);
    QByteArray vv=ss.toBase64();

    QByteArray ba;
    QDataStream out(&ba,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_6);

    out<<(quint64)0;
    out<<vv;
    out.device()->seek(0);
    out<<(quint64)(ba.size()-sizeof(quint64));
    video_tcpSocket->write(ba);

    QMatrix martix;
    martix.scale(0.25,0.25);
    image = image.transformed(martix);
    signalSendImageShow(image);
    qDebug()<<"SendVieo stop";
}
