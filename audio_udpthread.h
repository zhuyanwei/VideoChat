#ifndef AUDIO_UDPTHREAD_H
#define AUDIO_UDPTHREAD_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QByteArray>
#include <QUdpSocket>
#include <QThread>
class AudioUdpThread : public QObject
{
    Q_OBJECT

public:
    AudioUdpThread();
    ~AudioUdpThread();
public:
    static QString IpAddress;

private:
    QUdpSocket * udpsocketSend;
    QUdpSocket * udpSocketRecv;
    bool stopFlag;
private slots:
     void ReadPendingDatagrams();
     void run();
     void slotSendData(const QByteArray &byte_array);
signals:
     void signalPlay(const QByteArray &byte_array);
};

#endif // CUDPTHREAD_H
