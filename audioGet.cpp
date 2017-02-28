#include "AudioGet.h"

const int BUFFER_SIZE=2048;
AudioGet::AudioGet()
{
    QAudioFormat AudioGetFormat;
    AudioGetFormat.setSampleRate(8000);
    AudioGetFormat.setChannelCount(1);
    AudioGetFormat.setSampleSize(16);
    AudioGetFormat.setCodec("AudioGet/pcm");
    AudioGetFormat.setByteOrder(QAudioFormat::LittleEndian);
    AudioGetFormat.setSampleType(QAudioFormat::UnSignedInt);
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(AudioGetFormat))
    {
        qDebug()<<"default format not supported try to use nearest";
        AudioGetFormat = info.nearestFormat(AudioGetFormat);
    }
    info = QAudioDeviceInfo::defaultOutputDevice();
    if (!info.isFormatSupported(AudioGetFormat)) {
        qDebug()<<"default format not supported try to use nearest";
        AudioGetFormat = info.nearestFormat(AudioGetFormat);
    }
    audioInput = new QAudioInput(AudioGetFormat, this);
    streamIn = audioInput->start();
    audioInput->suspend();
//    connect(streamIn, SIGNAL(readyRead()), SLOT(startRecording()));

    audioOutput = new QAudioOutput(AudioGetFormat, this);
    streamOut = audioOutput->start();
    audioOutput->suspend();
    //creat AudioGet thread
//    udpThread=new AudioUdpThread();
//    udpThreadFather=new QThread();
//    udpThread->moveToThread(udpThreadFather);
//    connect(udpThreadFather,SIGNAL(started()),udpThread,SLOT(run()));
//    udpThreadFather->start();
}
AudioGet::~AudioGet()
{
    close();
}
void AudioGet::enable_run()
{
    audioInput->resume();
    audioOutput->resume();
}
void AudioGet::disable_run()
{
    audioInput->suspend();
    audioOutput->suspend();
}
void AudioGet::startRecording()
{
    short srcAudio[L_FRAME]={0};
    unsigned char dstAudio[L_FRAME_COMPRESSED]={'\0'};
    if (!audioInput)
    {
        qDebug() << "AudioInput Error";
        return;
    }
    QByteArray dataBuffer(BUFFER_SIZE,0);
    qint64 len1 = audioInput->bytesReady();
    if (len1 > BUFFER_SIZE)
    {
        qDebug()<<"BUFFER_SIZE too small";
        return;
    }
    qint64 len2 = streamIn->read(dataBuffer.data(), len1);
    tempBuffer.append(dataBuffer.data(),len2);
    for(int i=0;i<tempBuffer.length()/(L_FRAME*2);i++)
    {
        //char2short
        memcpy(srcAudio,tempBuffer.data()+i*L_FRAME*2,L_FRAME*2);
        //encode
        cg729Encoder.encode(srcAudio, dstAudio);
        QByteArray frame;
        //reinterpret_cast use to unsigned char * to const char *
        frame.append(reinterpret_cast<const char*>(dstAudio),L_FRAME_COMPRESSED);
        signalSendData(frame);
    }
    tempBuffer.clear();
}
void AudioGet::player(const QByteArray &byte_array)
{
    qDebug()<<"play begin";
    for(int i=0;i<byte_array.length()/L_FRAME_COMPRESSED;i++)
    {
        unsigned char srcAudio[L_FRAME_COMPRESSED]={'\0'};
        short dstAudio[L_FRAME]={0};
        memcpy(srcAudio,(unsigned char*)byte_array.data()+i * L_FRAME_COMPRESSED,L_FRAME_COMPRESSED);
        //G729encode
        cg729Decoder.decode(srcAudio,dstAudio,0);
        //short2char
        tempframe.append((char *)dstAudio,L_FRAME * 2);
        if(audioOutput&&audioOutput->state()!=QAudio::StoppedState&&
                audioOutput->state()!=QAudio::SuspendedState)
        {
              int chunks = audioOutput->bytesFree()/audioOutput->periodSize();
              while (chunks)
              {
                  if (tempframe.length() >= audioOutput->periodSize())
                  {
                      //
                      streamOut->write(tempframe.data(),audioOutput->periodSize());
                      tempframe = tempframe.mid(audioOutput->periodSize());
                  }
                  else
                  {
                      //
                      streamOut->write(tempframe);
                      tempframe.clear();
                      break;
                  }
                  --chunks;
              }
         }
    }
}
