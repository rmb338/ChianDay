#pragma once

#include <QtWidgets/QDialog>
#include "ui_ChinaDay.h"
#include <QPaintEvent>
#include <QImage>

class QMediaPlayer;
class ChinaDay : public QDialog
{
	Q_OBJECT

public:
	ChinaDay(QWidget *parent = Q_NULLPTR);
protected:
	void paintEvent(QPaintEvent* e);
	void showEvent(QShowEvent* e);
public slots:
	void positionChanged(qint64 pos);
private:
	QMediaPlayer* player;
	QImage backImg;
	int flagStartY = 334;
private:
	Ui::ChinaDayClass ui;
};
