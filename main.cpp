#include <QApplication>

#include "BotChroniclesOfChaos.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BotChroniclesOfChaos w;
	w.show();
	return a.exec();
}
