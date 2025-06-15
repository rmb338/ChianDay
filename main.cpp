#include "ChinaDay.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ChinaDay w;
	w.show();
	return a.exec();
}
