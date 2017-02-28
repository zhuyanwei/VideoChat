#include "video_server.h"

video_server::video_server()
{
    stopFlag = true;
}
video_server::~video_server()
{
    stopFlag=false;
    close();
//    delete video_server;
}
void video_server::DisplayError(QAbstractSocket::SocketError socketError)
{
    video_tcpServerConnection->close();
    qDebug()<<"Socket error";
}
void video_server::enable_run()
{
    stopFlag = false;
    if(!video_tcpServer->listen(QHostAddress::Any,8888))
    {
//        QMessageBox::critical(this,tr("Fortune Server"),tr("Unable to start the server:%l.").arg(tcpServer->errorString()));
        qDebug()<<"Unable to start the server";
        close();
        return;
    }
    qDebug()<<"SendImagetimer start";
}
void video_server::disable_run()
{
    stopFlag = true;
    video_tcpServer->close();
    qDebug()<<"SendImagetimer stop";
}
void video_server::run()
{
//    if(stopFlag) return;
    qDebug()<<"videoServer thread run";
    video_tcpServer = new QTcpServer(this);
//    if(!video_tcpServer->listen(QHostAddress::Any,8888))
//    {
////        QMessageBox::critical(this,tr("Fortune Server"),tr("Unable to start the server:%l.").arg(tcpServer->errorString()));
//        qDebug()<<"Unable to start the server";
//        close();
//        return;
//    }
    connect(video_tcpServer, SIGNAL(newConnection()), this, SLOT(sendFortune()));
}
void video_server::sendFortune()
{
    basize=0;
    video_tcpServerConnection = video_tcpServer->nextPendingConnection();
    connect(video_tcpServerConnection,SIGNAL(readyRead()),this,SLOT(ReadMyData()));
    connect(video_tcpServerConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(DisplayError(QAbstractSocket::SocketError)));

}
void video_server::ReadMyData()
{
    QByteArray message;//sava the image

    QDataStream in(video_tcpServerConnection);
    in.setVersion(QDataStream::Qt_5_6);
    if (basize==0)
    {
        if (video_tcpServerConnection->bytesAvailable()<(int)sizeof(quint64))
        {
            return;
        }
        in>>basize;
    }
    if (video_tcpServerConnection->bytesAvailable()<basize)
    {
        return;
    }
    in>>message;
    QString ss=QString::fromLatin1(message.data(),message.size());
    QByteArray rc;
    rc=QByteArray::fromBase64(ss.toLatin1());
    QByteArray rdc=qUncompress(rc);
    QImage img;
    img.loadFromData(rdc);

    QMatrix martix;
    martix.scale(1,1);
    img = img.transformed(martix);

    signalRecvImageShow(img);
//    ui->image_label->setPixmap(QPixmap::fromImage(img));
//    ui->image_label->resize(img.size());
}
