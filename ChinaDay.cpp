#include "ChinaDay.h"
#include <QPainter>
#include <qmath.h>
#include <QMediaPlayer>

ChinaDay::ChinaDay(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	backImg.load(":/ChinaDay/qigan.png");
	resize(backImg.width(), backImg.height());
	player = new QMediaPlayer(this);
	connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
	player->setMedia(QUrl::fromLocalFile("guoge.wav"));
	player->setVolume(80);
	setWindowTitle(QStringLiteral("������"));
}

void ChinaDay::positionChanged(qint64 pos)
{
	//�ܹ���49��
	if (pos / 1000 >= 48)
	{
		//���һ����첻��
		return;
	}
	this->flagStartY = 334 - (334 - 4) / (49.0) * (pos/1000.0);//���3��û����
	update();
}

void ChinaDay::paintEvent(QPaintEvent * e)
{
	//qint64 k = 5;//�Ŵ���С����ֵ
	//qint64 width = 24;
	//qint64 height = 16;
	//QPainter p(this);

	////������ͼƬ
	//p.drawImage(0, 0, backImg);

	//p.setBrush(QColor("#F40002"));
	//p.setPen(QColor("#FFFFFF"));
	////�������ʼ����
	//int xStart = /*124*/0, yStart = /*334*/0;
	//p.drawRect(xStart, yStart, width*k, height*k);
	////���Ƚ�����ԭ����Ϊ������ǵ�����
	//int starCenterX = k * 20, starCenterY = k * 20;
	//p.translate(starCenterX + xStart, yStart + starCenterY);
	//p.setBrush(QColor("#FAF408"));
	//p.setPen(QColor("#FAF408"));

	////���������
	//int bigStarConvexLen = 4;//�����εı߳�
	//QPoint points[3] = { QPoint(xStart, yStart- bigStarConvexLen*3), QPoint(-bigStarConvexLen, 0),QPoint(bigStarConvexLen, 0) };
	//p.setRenderHint(QPainter::Antialiasing);
	//for (int i = 0; i < 5; i++)
	//{
	//	//�������ι��������
	//	p.rotate(72);
	//	p.drawConvexPolygon(points, 3);
	//}

	////�Ŀ�С�ǵ����ĵ�
	//QPoint transLate[4] = { QPoint(xStart+20, yStart-12), QPoint(xStart+8, yStart+8), QPoint(0, 36), QPoint(-24, 24) };
	////�Ŀ�С�ǵ�ƫת�Ƕ�
	//qreal rotateAngle[4] = { -90 - qRadiansToDegrees(qAtan(0.6)), -90 - qRadiansToDegrees(qAtan(1.0 / 7.0)),
	//						 -qRadiansToDegrees(qAtan(3.5)), -qRadiansToDegrees(qAtan(1.25)) };
	////1
	//int smallStarConvexLen = 2;
	//QPoint points1[3] = { QPoint(0, -smallStarConvexLen*2), QPoint(-smallStarConvexLen, 0),QPoint(smallStarConvexLen, 0) };

	//for (int i = 0; i < 4; i++)
	//{
	//	p.translate(transLate[i]);
	//	//ÿ�λ�С�����ǰ��������ΪҪ��������ǵ�����
	//	p.rotate(rotateAngle[i]);
	//	//����ÿ�ζ���תһ���Ƕ��Զ�׼�������
	//	for (int i = 0; i < 5; i++)
	//	{
	//		p.rotate(72);//������������������ɣ�ÿ����ת72�㣬��ת5�εõ������
	//		p.drawConvexPolygon(points1, 3);
	//		//���������ǵ�������
	//	}
	//	p.rotate(-rotateAngle[i]);

	//}


	qint64 k = 15;
	qint32 kScale = k / 5;
	qint64 width = 24;
	qint64 height = 16;
	QPainter p(this);
	//������ͼƬ
	p.drawImage(0, 0, backImg);
	p.setBrush(QColor("#F40002"));
	p.setPen(QColor("#FFFFFF"));
	int flagStartX = 124;
	p.drawRect(flagStartX, flagStartY, width*k/kScale, height*k/kScale);
	//���Ƚ�����ԭ����Ϊ������ǵ�����
	p.translate(flagStartX+60/kScale, flagStartY+60/kScale);
	p.setBrush(QColor("#FAF408"));
	p.setPen(QColor("#FAF408"));

	//
	//���������
	QPoint points[3] = { QPoint(0/kScale, -36/kScale), 
						 QPoint(-12/kScale, 0/kScale),
						 QPoint(12/kScale, 0/kScale) };
	p.setRenderHint(QPainter::Antialiasing);
	for (int i = 0; i < 5; i++)
	{
		//�������ι��������
		p.rotate(72);
		p.drawConvexPolygon(points, 3);
	}

	//�Ŀ�С�ǵ����ĵ�
	QPoint transLate[4] = { QPoint(60/kScale,-36/kScale),
							QPoint(24/kScale,+24/kScale), 
							QPoint(0/kScale,+36/kScale), 
							QPoint(-24/kScale,+24/kScale) };
	//�Ŀ�С�ǵ�ƫת�Ƕ�
	qreal rotateAngle[4] = { -90 - qRadiansToDegrees(qAtan(0.6)), -90 - qRadiansToDegrees(qAtan(1.0 / 7.0)),
							 -qRadiansToDegrees(qAtan(3.5)), -qRadiansToDegrees(qAtan(1.25)) };
	//1
	QPoint points1[3] = { QPoint(0/kScale, -12/kScale), 
						  QPoint(-5/kScale, +0/kScale),
						  QPoint(+5/kScale, +0/kScale) };

	for (int i = 0; i < 4; i++)
	{
		p.translate(transLate[i]);
		//ÿ�λ�С�����ǰ��������ΪҪ��������ǵ�����
		p.rotate(rotateAngle[i]);
		//����ÿ�ζ���תһ���Ƕ��Զ�׼�������
		for (int i = 0; i < 5; i++)
		{
			p.rotate(72);//������������������ɣ�ÿ����ת72�㣬��ת5�εõ������
			p.drawConvexPolygon(points1, 3);
			//���������ǵ�������
		}
		p.rotate(-rotateAngle[i]);

	}
}

void ChinaDay::showEvent(QShowEvent * e)
{
	player->play();
}
