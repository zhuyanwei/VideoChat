#ifndef AUDIOGET_H
#define AUDIOGET_H

#include <QWidget>
#include <QAudioInput>
#include <QAudioOutput>
#include <QByteArray>
#include "cg729encoder.h"
#include "cg729decoder.h"
#include "audio_udpthread.h"
#include <QThread>

class AudioGet : public QWidget
{
    Q_OBJECT
public:
    AudioGet();
    ~AudioGet();
private slots:
    void startRecording();
    void player(const QByteArray &byte_array);
public slots:
    void enable_run();
    void disable_run();
signals:
    void signalSendData(const QByteArray &byte_array);

private:
    CG729Encoder cg729Encoder;
    QAudioInput* audioInput;
//    QIODevice * streamIn;

    CG729Decoder cg729Decoder;
    QAudioOutput* audioOutput;
    QIODevice * streamOut;

    QByteArray tempBuffer;
    QByteArray tempframe;

    QThread * udpThreadFather;
public:
    AudioUdpThread *udpThread;
    QIODevice * streamIn;
};

#endif // AUDIOGET_H
