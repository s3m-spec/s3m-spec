#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QProgressDialog>
#include <QTextCodec>
#include <QFileDialog>

class DialogOBJToS3MB : public QDialog
{
	Q_OBJECT

public:
	DialogOBJToS3MB(QWidget *parent = Q_NULLPTR);

private slots:
	void handleTextEditedEvent();
	void handleConfirmButtonClickedEvent();
	void handleCancelButtonClickedEvent();
    void handleSrcFileButtonClickedEvent();
    void handleDesFileButtonClickedEvent();
	void handleThreadFinishedEvent();

private:
	QLineEdit* m_srcEdit;
	QLineEdit* m_desEdit;
	QPushButton* m_confirmButton;
	QButtonGroup* m_btnGroup;
	QProgressDialog* m_progressDialog;
#ifdef WIN32
	QString buttonOK = "ȷ��";
	QString buttonCancle = "ȡ��";
	QString waitText = "...";
	QString sourceSCP = "Դ�����ļ�:";
	QString outputDir = "Ŀ��·��:";
	QString threadCount = "�߳���:";
	QString exeResult = "ִ�н��";
	QString isDone = "���";
	QString waiting = "����ִ��...";
	QString openFile = "��";
#else
	QTextCodec* codec = QTextCodec::codecForName("GBK");
	QString buttonOK = codec->toUnicode("ȷ��");
	QString buttonCancle = codec->toUnicode("ȡ��");
	QString waitText = codec->toUnicode("...");
	QString sourceSCP = codec->toUnicode("Դ�����ļ�:");
	QString outputDir = codec->toUnicode("Ŀ��·��:");
	QString threadCount = codec->toUnicode("�߳���:");
	QString exeResult = codec->toUnicode("ִ�н��");
	QString isDone = codec->toUnicode("���:");
	QString waiting = codec->toUnicode("����ִ��...");
	QString openFile = codec->toUnicode("��");
#endif
};
