#include "D3DSound.h"
#include <QAudioOutput>
#include <QAudioFormat>
#include <QAudioDeviceInfo>


CD3DSound::CD3DSound(QObject *parent)
	: QObject(parent)
{
	// Set up the format, eg.
	m_AudioFormat.setSampleRate(1411000);
	m_AudioFormat.setChannelCount(1);
	m_AudioFormat.setSampleSize(16);
	m_AudioFormat.setCodec("audio/pcm");
	m_AudioFormat.setByteOrder(QAudioFormat::LittleEndian);
	m_AudioFormat.setSampleType(QAudioFormat::UnSignedInt);
	m_pIDirectSound=new QAudioOutput(m_AudioFormat,this);
	connect(m_pIDirectSound, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
	if (m_pD3DSound==NULL)
	{
		m_pD3DSound=this;
	}
	m_Sound=NULL;
}

CD3DSound::~CD3DSound()
{
	if (m_pIDirectSound)
	{
		m_pIDirectSound->stop();
		m_D3DSoundBufferActive.close();
		delete m_pIDirectSound;
		m_pIDirectSound=NULL;
	}
	if (m_Sound)
	{
		delete m_Sound;
		m_Sound=NULL;
	}
}

bool CD3DSound::StopSound()
{
	m_SoundMutex.lock();
	if (m_Sound)
	{
		m_Sound->stop();
	}
	m_SoundMutex.unlock();
	return true;
}

bool CD3DSound::PlaySound( const QString& pszFileName, bool bRepetition/*=false*/ )
{
	m_SoundMutex.lock();

	//QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
	//if (!info.isFormatSupported(m_AudioFormat)) {
	//	assert(false);
	//	return false;
	//}
	SoundBuffer sb;
	sb.sSoundFileName=pszFileName;
	sb.bRepetition=bRepetition;
	m_D3DSoundBufferBuffer.push_back(sb);

	if (m_pIDirectSound->state()==QAudio::StoppedState
		||m_pIDirectSound->state()==QAudio::IdleState)
	{
		m_D3DSoundBufferActive.setFileName(pszFileName);
		m_D3DSoundBufferActive.open(QIODevice::ReadOnly);
		m_pIDirectSound->start(&m_D3DSoundBufferActive);
	}
	else if (m_pIDirectSound->state()==QAudio::SuspendedState)
	{
		m_pIDirectSound->resume();
	}
	m_SoundMutex.unlock();
	return  true;
}

bool CD3DSound::PlaySound( const QString& pszResource, const QString& pszTypeName, bool bRepetition/*=false*/ )
{
	return PlaySound(pszResource,bRepetition);
}

void CD3DSound::handleStateChanged(QAudio::State newState)
{
	switch (newState) {
	case QAudio::IdleState:
		{
			//取出队列里面的数据判断是否要重复播放;
			SoundBuffer lastSoundBuffer=m_D3DSoundBufferBuffer.head();
			if (!lastSoundBuffer.bRepetition)
			{
				m_D3DSoundBufferBuffer.pop_front();
				lastSoundBuffer=m_D3DSoundBufferBuffer.head();
				m_D3DSoundBufferActive.close();
				m_D3DSoundBufferActive.setFileName(lastSoundBuffer.sSoundFileName);
				m_D3DSoundBufferActive.open(QIODevice::ReadOnly);
			}
			m_pIDirectSound->start(&m_D3DSoundBufferActive);
		}
		break;

	case QAudio::StoppedState:
		// Stopped for other reasons
		m_D3DSoundBufferActive.close();
		if (m_pIDirectSound->error() != QAudio::NoError) {
			// Error handling
		}
		break;

	default:
		// ... other cases as appropriate
		break;
	}
}

CD3DSound * CD3DSound::GetInstance()
{
	if (!m_pD3DSound)
	{
		m_pD3DSound = new CD3DSound();
	}
	return m_pD3DSound;
}

CD3DSound * CD3DSound::m_pD3DSound=NULL;
