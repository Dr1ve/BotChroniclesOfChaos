#include "BotChroniclesOfChaos.h"

#include <QVBoxLayout>
#include "TextCodec.h"
#include <QNetworkReply>
#include <QXmlStreamReader>

BotChroniclesOfChaos::BotChroniclesOfChaos(QWidget *parent)
	: QWidget(parent),
	htmlText(new QPlainTextEdit),
	urlText(new QLineEdit("m.vk.com")),
	sendBtn(new QPushButton(c2s("���������")))
{
	QVBoxLayout *lay = new QVBoxLayout;
	setLayout(lay);
	
	connect(&manager, &QNetworkAccessManager::finished, this, &BotChroniclesOfChaos::replyFinished);
	connect(sendBtn, &QPushButton::pressed, this, &BotChroniclesOfChaos::getHtml);

	QPushButton *pars = new QPushButton(c2s("�������"));
	connect(pars, &QPushButton::pressed, this, &BotChroniclesOfChaos::parsingHtml);

	QHBoxLayout *hlay = new QHBoxLayout;
	hlay->addWidget(urlText);
	hlay->addWidget(sendBtn);
	lay->addLayout(hlay);

	lay->addWidget(pars);
	lay->addWidget(htmlText);
	//// ������ �����������
	//QDialog dlg;
	//QVBoxLayout *dlgLay = new QVBoxLayout;
	//QFormLayout *formLay = new QFormLayout;
	//dlgLay->addLayout(formLay);
	//dlg.setLayout(dlgLay);

	//formLay->addRow(c2s("�����: "), new QLineEdit);
	//formLay->addRow(c2s("������: "), new QLineEdit);

	//QPushButton *btn1 = new QPushButton(c2s("�����"));
	//connect(btn1, SIGNAL(pressed()), &dlg, SLOT(accept()));
	//QPushButton *btn2 = new QPushButton(c2s("������"));
	//connect(btn2, SIGNAL(pressed()), &dlg, SLOT(reject()));
	//QHBoxLayout *dlgHLay = new QHBoxLayout;
	//dlgHLay->addWidget(btn1);
	//dlgHLay->addWidget(btn2);
	//dlgLay->addLayout(dlgHLay);

	//dlg.show();
	//if (dlg.exec() == QDialog::Accepted)
	//{
	//	// ������ �����
	//	//QMessageBox::information(&dlg, c2s("�������"), c2s("����������� ���� � �������"), QMessageBox::Ok, QMessageBox::Ok);
	//	QString urlSpec = "https://ya.ru";
	//	const QUrl Url = QUrl::fromUserInput(urlSpec);
	//	if (!Url.isValid())
	//	{
	//		QMessageBox::information(this, c2s("������"), c2s("�� �������� url: %1: %2").arg(urlSpec, Url.errorString()));
	//		return;
	//	}
	//	QString fileName = Url.fileName();
	//	reply = qnam.get(QNetworkRequest(Url));
	//	connect(reply, &QIODevice::readyRead, this, &BotChroniclesOfChaos::httpReadyRead);
	//	connect(reply, &QNetworkReply::finished, this, &BotChroniclesOfChaos::httpFinished);
	//	file = new QFile("httpfile.txt");
	//	if (!file->open(QIODevice::WriteOnly))
	//	{
	//		QMessageBox::information(this, c2s("������"), c2s("�� ���� ������� ���� ��� ������"));
	//	}

	//}

	//lay->addWidget(new QLabel(c2s("����")));
	//lay->addWidget(new QPushButton(c2s("������� ���������� ������")));
	//lay->addWidget(new QPushButton(c2s("������ �����")));
	//lay->addWidget(new QPushButton(c2s("������� ������ ������ ����������")));
	//lay->addWidget(new QPushButton(c2s("���������")));
	//lay->addWidget(new QPushButton(c2s("��������� �������� ���������� �������")));
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