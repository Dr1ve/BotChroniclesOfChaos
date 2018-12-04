#ifndef TextCodec_h
#define TextCodec_h

#include <QTextCodec>

static const QString c2s(const char *c)
{
	QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
	return codec->toUnicode(c);
}


#endif // !TextCodec_h

