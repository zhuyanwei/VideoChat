#include "videochat.h"
#include "ui_videochat.h"

VideoChat::VideoChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoChat)
{
    ui->setupUi(this);

    //creat the video_server thread
    video_server *videoServer = new video_server();
    videoServerFather=new QThread();
    videoServer->moveToThread(videoServerFather);
    connect(videoServerFather,SIGNAL(started()),videoServer,SLOT(run()));
    connect(videoServerFather,&QThread::finished,videoServer,&QObject::deleteLater);
    videoServerFather->start();

    //creat the video_client thread
    video_client *videoClient = new video_client();
    videoClientFather=new QThread();
    videoClient->moveToThread(videoClientFather);
    connect(videoClientFather,SIGNAL(started()),videoClient,SLOT(run()));
    connect(videoClientFather,&QThread::finished,videoClient,&QObject::deleteLater);
    videoClientFather->start();
    //
    audioGet = new AudioGet();
    audioGet->udpThread=new AudioUdpThread();
    udpThreadFather=new QThread();
    audioGet->udpThread->moveToThread(udpThreadFather);
    connect(udpThreadFather,SIGNAL(started()),audioGet->udpThread,SLOT(run()));
    connect(udpThreadFather,&QThread::finished,audioGet->udpThread,&QObject::deleteLater);
    udpThreadFather->start();

    connect(audioGet->streamIn, SIGNAL(readyRead()),audioGet, SLOT(startRecording()));
    connect(audioGet,SIGNAL(signalSendData(QByteArray)),audioGet->udpThread,SLOT(slotSendData(QByteArray)));
    connect(audioGet->udpThread,SIGNAL(signalPlay(QByteArray)),audioGet,SLOT(player(QByteArray)));
    //
    connect(this,SIGNAL(signalStart()),audioGet,SLOT(enable_run()));
    connect(this,SIGNAL(signalStop()),audioGet,SLOT(disable_run()));
    //connect the pushbutton to the thread
    connect(this,SIGNAL(signalStart()),videoClient,SLOT(enable_run()));
    connect(this,SIGNAL(signalStop()),videoClient,SLOT(disable_run()));
    //
    connect(this,SIGNAL(signalStart()),videoServer,SLOT(enable_run()));
    connect(this,SIGNAL(signalStop()),videoServer,SLOT(disable_run()));

    connect(videoClient,SIGNAL(signalSendImageShow(QImage)),this,SLOT(showSendImage(QImage)));
    connect(videoServer,SIGNAL(signalRecvImageShow(QImage)),this,SLOT(showRecvImage(QImage)));

}

VideoChat::~VideoChat()
{
    delete ui;
//    delete VideoChat;
//    videoServerFather->quit();
//    videoClientFather->quit();
//    udpThreadFather->quit();
//    videoServerFather->wait();
//    videoClientFather->wait();
//    udpThreadFather->wait();

//    videoServerFather->isFinished();
//    videoClientFather->isFinished();
//    udpThreadFather->isFinished();

//    this->close();
}
void VideoChat::showSendImage(const QImage &image)
{
    qDebug()<<"showSendImage start";
    ui->send_image->setPixmap(QPixmap::fromImage(image));
    ui->send_image->resize(image.size());
}
void VideoChat::showRecvImage(const QImage &image)
{
    qDebug()<<"showRecvImage start";
    ui->rece_Image->setPixmap(QPixmap::fromImage(image));
    ui->rece_Image->resize(image.size());
}

//connect the pushbutton to signal
void VideoChat::on_start_clicked()
{
    video_client::IpAddress=ui->ip->text();
    AudioUdpThread::IpAddress=ui->ip->text();
//    audio->IpAddress=ui->ip->text();
    qDebug()<<"IP :"<<video_client::IpAddress;
    signalStart();
}

void VideoChat::on_stop_clicked()
{
    signalStop();
}

//void VideoChat::on_setIp_clicked()
//{
//    video_client::IpAddress=ui->ip->text();
//    AudioUdpThread::IpAddress=ui->ip->text();
////    audio->IpAddress=ui->ip->text();
//    qDebug()<<"IP :"<<video_client::IpAddress;
//}
