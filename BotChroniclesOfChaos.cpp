#include "BotChroniclesOfChaos.h"

#include <QVBoxLayout>
#include "TextCodec.h"
#include <QNetworkReply>
#include <QXmlStreamReader>

BotChroniclesOfChaos::BotChroniclesOfChaos(QWidget *parent)
	: QWidget(parent),
	htmlText(new QPlainTextEdit),
	urlText(new QLineEdit("m.vk.com")),
	sendBtn(new QPushButton(c2s("Отправить")))
{
	QVBoxLayout *lay = new QVBoxLayout;
	setLayout(lay);
	
	connect(&manager, &QNetworkAccessManager::finished, this, &BotChroniclesOfChaos::replyFinished);
	connect(sendBtn, &QPushButton::pressed, this, &BotChroniclesOfChaos::getHtml);

	QPushButton *pars = new QPushButton(c2s("Парсинг"));
	connect(pars, &QPushButton::pressed, this, &BotChroniclesOfChaos::parsingHtml);

	QHBoxLayout *hlay = new QHBoxLayout;
	hlay->addWidget(urlText);
	hlay->addWidget(sendBtn);
	lay->addLayout(hlay);

	lay->addWidget(pars);
	lay->addWidget(htmlText);
	//// Диалог авторизации
	//QDialog dlg;
	//QVBoxLayout *dlgLay = new QVBoxLayout;
	//QFormLayout *formLay = new QFormLayout;
	//dlgLay->addLayout(formLay);
	//dlg.setLayout(dlgLay);

	//formLay->addRow(c2s("Логин: "), new QLineEdit);
	//formLay->addRow(c2s("Пароль: "), new QLineEdit);

	//QPushButton *btn1 = new QPushButton(c2s("Войти"));
	//connect(btn1, SIGNAL(pressed()), &dlg, SLOT(accept()));
	//QPushButton *btn2 = new QPushButton(c2s("Отмена"));
	//connect(btn2, SIGNAL(pressed()), &dlg, SLOT(reject()));
	//QHBoxLayout *dlgHLay = new QHBoxLayout;
	//dlgHLay->addWidget(btn1);
	//dlgHLay->addWidget(btn2);
	//dlgLay->addLayout(dlgHLay);

	//dlg.show();
	//if (dlg.exec() == QDialog::Accepted)
	//{
	//	// Нажали войти
	//	//QMessageBox::information(&dlg, c2s("Заходим"), c2s("Выполняется вход в соцсеть"), QMessageBox::Ok, QMessageBox::Ok);
	//	QString urlSpec = "https://ya.ru";
	//	const QUrl Url = QUrl::fromUserInput(urlSpec);
	//	if (!Url.isValid())
	//	{
	//		QMessageBox::information(this, c2s("Ошибка"), c2s("Не валидный url: %1: %2").arg(urlSpec, Url.errorString()));
	//		return;
	//	}
	//	QString fileName = Url.fileName();
	//	reply = qnam.get(QNetworkRequest(Url));
	//	connect(reply, &QIODevice::readyRead, this, &BotChroniclesOfChaos::httpReadyRead);
	//	connect(reply, &QNetworkReply::finished, this, &BotChroniclesOfChaos::httpFinished);
	//	file = new QFile("httpfile.txt");
	//	if (!file->open(QIODevice::WriteOnly))
	//	{
	//		QMessageBox::information(this, c2s("Ошибка"), c2s("Не смог открыть файл для записи"));
	//	}

	//}

	//lay->addWidget(new QLabel(c2s("Меню")));
	//lay->addWidget(new QPushButton(c2s("Собрать ежедневный сундук")));
	//lay->addWidget(new QPushButton(c2s("Пройти башню")));
	//lay->addWidget(new QPushButton(c2s("Собрать добычу Боссов Запределья")));
	//lay->addWidget(new QPushButton(c2s("Дирижабль")));
	//lay->addWidget(new QPushButton(c2s("Запустить автосбор ежедневных заданий")));
}

void BotChroniclesOfChaos::parsingHtml()
{
	QFile file("htmlVK.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QString html = QString(file.readAll());

	htmlText->setPlainText(html);

	QXmlStreamReader xml = QXmlStreamReader(html);
	
}

void BotChroniclesOfChaos::getHtml()
{
	manager.get(QNetworkRequest(QUrl::fromUserInput(urlText->text())));
}

void BotChroniclesOfChaos::replyFinished(QNetworkReply *reply)
{
	if (reply->error())
	{
		qDebug() << "ERROR!";
		qDebug() << reply->errorString();
	}
	else
	{
		qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
		qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();;
		qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
		qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
		qDebug() << reply->header(QNetworkRequest::KnownHeaders::LocationHeader).toString();

		QString html = reply->readAll();
		htmlText->setPlainText(html);
		QFile file("htmlVK.html");
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;

		file.write(html.toStdString().c_str());
	}
	
	reply->deleteLater();
}