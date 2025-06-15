#ifndef D3DSOUND_H
#define D3DSOUND_H

#include <QObject>
#include <QFile>
#include <QAudio>
#include <QSound>
#include <QAudioFormat>
#include <QMutex>
#include <QQueue>

//声时播放接口;
class QAudioOutput;

//播放配置;
struct AudioConfig
{
	int mSampleRate;
	int mChannelCount;
	int mSampleSize;
	QString mCodec;
};

struct SoundBuffer 
{
	QString sSoundFileName;
	bool    bRepetition;
};

class CD3DSound : public QObject
{
	Q_OBJECT

public:
	CD3DSound(QObject *parent=NULL);
	~CD3DSound();
	static CD3DSound *				m_pD3DSound;						//对象指针;
private:
	QAudioOutput*					m_pIDirectSound;					//播放器对象;
	QFile							m_D3DSoundBufferActive;				//当前播放;
	QQueue<SoundBuffer>				m_D3DSoundBufferBuffer;				//播放队列;
	QSound*							m_Sound;							//简单的播放;
	QMutex							m_SoundMutex;						//互斥量;
public:
	QAudioFormat					m_AudioFormat;						//播放器配置;
	//静态函数;
public:
	//获取对象;
	static CD3DSound * GetInstance();
	//声音播放;
public:
	//停止声音;
	bool StopSound();
	//播放声音;
	bool PlaySound(const QString& pszFileName, bool bRepetition=false);
	//播放声音;
	bool PlaySound(const QString& pszResource, const QString& pszTypeName, bool bRepetition=false);
protected slots:
	void handleStateChanged(QAudio::State newState);
};

#endif // D3DSOUND_H
