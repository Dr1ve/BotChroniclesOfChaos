#ifndef BotChroniclesOfChaos_h
#define BotChroniclesOfChaos_h

#include <QWidget>
#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>

class BotChroniclesOfChaos : public QWidget
{
	Q_OBJECT

public:
	BotChroniclesOfChaos(QWidget *parent = Q_NULLPTR);

private slots:
	void replyFinished(QNetworkReply*);
	void getHtml();
	void parsingHtml();

private:
	QNetworkAccessManager manager;

	QPlainTextEdit *htmlText;
	QLineEdit *urlText;
	QPushButton *sendBtn;
};


#endif // !BotChroniclesOfChaos_h