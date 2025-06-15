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
	setWindowTitle(QStringLiteral("升国旗"));
}

void ChinaDay::positionChanged(qint64 pos)
{
	//总共是49秒
	if (pos / 1000 >= 48)
	{
		//最后一秒国旗不动
		return;
	}
	this->flagStartY = 334 - (334 - 4) / (49.0) * (pos/1000.0);//最后3秒没声音
	update();
}

void ChinaDay::paintEvent(QPaintEvent * e)
{
	//qint64 k = 5;//放大缩小基础值
	//qint64 width = 24;
	//qint64 height = 16;
	//QPainter p(this);

	////画背景图片
	//p.drawImage(0, 0, backImg);

	//p.setBrush(QColor("#F40002"));
	//p.setPen(QColor("#FFFFFF"));
	////国旗的起始坐标
	//int xStart = /*124*/0, yStart = /*334*/0;
	//p.drawRect(xStart, yStart, width*k, height*k);
	////首先将坐标原点设为大五角星的中心
	//int starCenterX = k * 20, starCenterY = k * 20;
	//p.translate(starCenterX + xStart, yStart + starCenterY);
	//p.setBrush(QColor("#FAF408"));
	//p.setPen(QColor("#FAF408"));

	////画大五角星
	//int bigStarConvexLen = 4;//三角形的边长
	//QPoint points[3] = { QPoint(xStart, yStart- bigStarConvexLen*3), QPoint(-bigStarConvexLen, 0),QPoint(bigStarConvexLen, 0) };
	//p.setRenderHint(QPainter::Antialiasing);
	//for (int i = 0; i < 5; i++)
	//{
	//	//画三角形构成五角星
	//	p.rotate(72);
	//	p.drawConvexPolygon(points, 3);
	//}

	////四颗小星的中心点
	//QPoint transLate[4] = { QPoint(xStart+20, yStart-12), QPoint(xStart+8, yStart+8), QPoint(0, 36), QPoint(-24, 24) };
	////四颗小星的偏转角度
	//qreal rotateAngle[4] = { -90 - qRadiansToDegrees(qAtan(0.6)), -90 - qRadiansToDegrees(qAtan(1.0 / 7.0)),
	//						 -qRadiansToDegrees(qAtan(3.5)), -qRadiansToDegrees(qAtan(1.25)) };
	////1
	//int smallStarConvexLen = 2;
	//QPoint points1[3] = { QPoint(0, -smallStarConvexLen*2), QPoint(-smallStarConvexLen, 0),QPoint(smallStarConvexLen, 0) };

	//for (int i = 0; i < 4; i++)
	//{
	//	p.translate(transLate[i]);
	//	//每次画小五角星前将坐标设为要画的五角星的中心
	//	p.rotate(rotateAngle[i]);
	//	//并且每次都旋转一个角度以对准大五角星
	//	for (int i = 0; i < 5; i++)
	//	{
	//		p.rotate(72);//五角星由五个三角形组成，每次旋转72°，旋转5次得到五角星
	//		p.drawConvexPolygon(points1, 3);
	//		//画组成五角星的三角形
	//	}
	//	p.rotate(-rotateAngle[i]);

	//}


	qint64 k = 15;
	qint32 kScale = k / 5;
	qint64 width = 24;
	qint64 height = 16;
	QPainter p(this);
	//画背景图片
	p.drawImage(0, 0, backImg);
	p.setBrush(QColor("#F40002"));
	p.setPen(QColor("#FFFFFF"));
	int flagStartX = 124;
	p.drawRect(flagStartX, flagStartY, width*k/kScale, height*k/kScale);
	//首先将坐标原点设为大五角星的中心
	p.translate(flagStartX+60/kScale, flagStartY+60/kScale);
	p.setBrush(QColor("#FAF408"));
	p.setPen(QColor("#FAF408"));

	//
	//画大五角星
	QPoint points[3] = { QPoint(0/kScale, -36/kScale), 
						 QPoint(-12/kScale, 0/kScale),
						 QPoint(12/kScale, 0/kScale) };
	p.setRenderHint(QPainter::Antialiasing);
	for (int i = 0; i < 5; i++)
	{
		//画三角形构成五角星
		p.rotate(72);
		p.drawConvexPolygon(points, 3);
	}

	//四颗小星的中心点
	QPoint transLate[4] = { QPoint(60/kScale,-36/kScale),
							QPoint(24/kScale,+24/kScale), 
							QPoint(0/kScale,+36/kScale), 
							QPoint(-24/kScale,+24/kScale) };
	//四颗小星的偏转角度
	qreal rotateAngle[4] = { -90 - qRadiansToDegrees(qAtan(0.6)), -90 - qRadiansToDegrees(qAtan(1.0 / 7.0)),
							 -qRadiansToDegrees(qAtan(3.5)), -qRadiansToDegrees(qAtan(1.25)) };
	//1
	QPoint points1[3] = { QPoint(0/kScale, -12/kScale), 
						  QPoint(-5/kScale, +0/kScale),
						  QPoint(+5/kScale, +0/kScale) };

	for (int i = 0; i < 4; i++)
	{
		p.translate(transLate[i]);
		//每次画小五角星前将坐标设为要画的五角星的中心
		p.rotate(rotateAngle[i]);
		//并且每次都旋转一个角度以对准大五角星
		for (int i = 0; i < 5; i++)
		{
			p.rotate(72);//五角星由五个三角形组成，每次旋转72°，旋转5次得到五角星
			p.drawConvexPolygon(points1, 3);
			//画组成五角星的三角形
		}
		p.rotate(-rotateAngle[i]);

	}
}

void ChinaDay::showEvent(QShowEvent * e)
{
	player->play();
}
