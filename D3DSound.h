#ifndef D3DSOUND_H
#define D3DSOUND_H

#include <QObject>
#include <QFile>
#include <QAudio>
#include <QSound>
#include <QAudioFormat>
#include <QMutex>
#include <QQueue>

//��ʱ���Žӿ�;
class QAudioOutput;

//��������;
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
	static CD3DSound *				m_pD3DSound;						//����ָ��;
private:
	QAudioOutput*					m_pIDirectSound;					//����������;
	QFile							m_D3DSoundBufferActive;				//��ǰ����;
	QQueue<SoundBuffer>				m_D3DSoundBufferBuffer;				//���Ŷ���;
	QSound*							m_Sound;							//�򵥵Ĳ���;
	QMutex							m_SoundMutex;						//������;
public:
	QAudioFormat					m_AudioFormat;						//����������;
	//��̬����;
public:
	//��ȡ����;
	static CD3DSound * GetInstance();
	//��������;
public:
	//ֹͣ����;
	bool StopSound();
	//��������;
	bool PlaySound(const QString& pszFileName, bool bRepetition=false);
	//��������;
	bool PlaySound(const QString& pszResource, const QString& pszTypeName, bool bRepetition=false);
protected slots:
	void handleStateChanged(QAudio::State newState);
};

#endif // D3DSOUND_H
