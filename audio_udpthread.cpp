#include "audio_udpthread.h"
#include <QDebug>

QString AudioUdpThread::IpAddress;

AudioUdpThread::AudioUdpThread()
{
    stopFlag=true;
}
AudioUdpThread::~AudioUdpThread()
{
    stopFlag=false;
//    close();
//    delete AudioUdpThread;
}

void AudioUdpThread::run()
{
    udpsocketSend=new QUdpSocket(this);
    udpSocketRecv = new QUdpSocket(this);
    udpSocketRecv->bind(25000, QUdpSocket::ShareAddress);
    connect(udpSocketRecv, SIGNAL(readyRead()), this, SLOT(ReadPendingDatagrams()),Qt::DirectConnection);
}

void AudioUdpThread::ReadPendingDatagrams()
{
    QByteArray datagram;
    while (udpSocketRecv->hasPendingDatagrams())
    {
       datagram.resize(udpSocketRecv->pendingDatagramSize());
       QHostAddress sender;
       quint16 senderPort;

       udpSocketRecv->readDatagram(
       datagram.data(),
       datagram.size(),
       &sender,
       &senderPort);
       if(datagram.size()>0)
       {
           emit signalPlay(datagram);
       }
     }
}

void AudioUdpThread::slotSendData(const QByteArray &byte_array)
{
    udpsocketSend->writeDatagram(byte_array,QHostAddress(IpAddress), 25000);
}
