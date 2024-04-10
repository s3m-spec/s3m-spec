#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "Dialog3DTilesToS3MB.h"
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QStringListModel>
#include <QMessageBox>
#include "ProcessTools.h"
#include "ProcessThread.h"

using namespace S3MB;

const char* FileTypeModel = "��ά��Ƭ";
const char* FileTypeObliquePhotogrammetry = "��б��Ӱ";
const char* TexCompDXT = "DXT";
const char* TexCompNONE = "��ѹ��";
const char* VerCompNONE = "��ѹ��";

Dialog3DTilesToS3MB::Dialog3DTilesToS3MB(QWidget *parent)
	: QDialog(parent)
{
	QVBoxLayout* vctLayout = new QVBoxLayout(this);

	m_srcEdit = new QLineEdit();
	m_srcEdit->setFixedSize(250, 20);
	m_desEdit = new QLineEdit();

    connect(m_srcEdit, SIGNAL(textEdited(QString)), this, SLOT(handleTextEditedEvent()));
    connect(m_desEdit, SIGNAL(textEdited(QString)), this, SLOT(handleTextEditedEvent()));

	QStringListModel* fileTypeModel = new QStringListModel(this);
    fileTypeModel->setStringList(QStringList()<< codec->toUnicode(FileTypeModel) << codec->toUnicode(FileTypeObliquePhotogrammetry));
	m_fileTypeBox = new QComboBox();
	m_fileTypeBox->setModel(fileTypeModel);

	QStringListModel* texCompModel = new QStringListModel(this);
    texCompModel->setStringList(QStringList()<< codec->toUnicode(TexCompDXT) << codec->toUnicode(TexCompNONE));
	m_texCompBox = new QComboBox();
	m_texCompBox->setModel(texCompModel);

	QStringListModel* verCompModel = new QStringListModel(this);
    verCompModel->setStringList(QStringList()<< codec->toUnicode(VerCompNONE));
	m_verCompBox = new QComboBox();
	m_verCompBox->setModel(verCompModel);

    m_confirmButton = new QPushButton(codec->toUnicode("ȷ��"));
	m_confirmButton->setEnabled(false);
    QPushButton* cancelButton = new QPushButton(codec->toUnicode("ȡ��"));
    connect(m_confirmButton, SIGNAL(clicked()), this, SLOT(handleConfirmButtonClickedEvent()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(handleCancelButtonClickedEvent()));


    QPushButton* srcFileButton = new QPushButton(codec->toUnicode("..."));
    srcFileButton->setFixedSize(25, 20);
    connect(srcFileButton, SIGNAL(clicked()), this, SLOT(handleSrcFileButtonClickedEvent()));
    QGridLayout* gridSrcLayout = new QGridLayout();
    gridSrcLayout->addWidget(m_srcEdit, 0,0);
    gridSrcLayout->addWidget(srcFileButton, 0,2);

    QPushButton* desFileButton = new QPushButton(codec->toUnicode("..."));
    desFileButton->setFixedSize(25, 20);
    connect(desFileButton, SIGNAL(clicked()), this, SLOT(handleDesFileButtonClickedEvent()));
    QGridLayout* gridDesLayout = new QGridLayout();
    gridDesLayout->addWidget(m_desEdit, 0,0);
    gridDesLayout->addWidget(desFileButton, 0,2);

	QFormLayout* formLayout = new QFormLayout();
	formLayout->setHorizontalSpacing(20);
	formLayout->setVerticalSpacing(10);
    formLayout->addRow(codec->toUnicode("Դ�����ļ�:"), gridSrcLayout);
    formLayout->addRow(codec->toUnicode("Ŀ��·��:"), gridDesLayout);
    formLayout->addRow(codec->toUnicode("�ļ�����:"), m_fileTypeBox);
    formLayout->addRow(codec->toUnicode("����ѹ����ʽ:"), m_texCompBox);
    formLayout->addRow(codec->toUnicode("�����Ż���ʽ:"), m_verCompBox);

	QHBoxLayout* bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(m_confirmButton);
	bottomLayout->addWidget(cancelButton);

	vctLayout->setMargin(15);
	vctLayout->setSpacing(15);
	vctLayout->addLayout(formLayout);
	vctLayout->addLayout(bottomLayout);
	vctLayout->setSizeConstraint(QLayout::SetFixedSize);
}

void Dialog3DTilesToS3MB::handleTextEditedEvent()
{
    QString strSrcPath = m_srcEdit->text();
    QString strDesPath = m_desEdit->text();
    bool isEmpty = !strSrcPath.isEmpty() && !strSrcPath.isEmpty();
    bool isExists = false;
    QFileInfo srcFile(strSrcPath);
    QFileInfo desFile(strDesPath);
    if (srcFile.isDir() || !srcFile.exists() || !desFile.isDir() || !desFile.exists())
    {
        isExists = false;
    }
    else
    {
        isExists = true;
    }
    bool isEnabled = isEmpty && isExists;
	m_confirmButton->setEnabled(isEnabled);
}

void Dialog3DTilesToS3MB::handleThreadFinishedEvent()
{
	if (m_progressDialog != nullptr)
	{
		m_progressDialog->close();
		m_progressDialog = nullptr;
	}
	
    QMessageBox::information(this, codec->toUnicode("ִ�н��"), codec->toUnicode("���!"));
}

void Dialog3DTilesToS3MB::handleConfirmButtonClickedEvent()
{
    std::wstring strSrcPath = StringUtil::UTF8_to_UNICODE(m_srcEdit->text().toStdString());
    std::wstring strDesPath = StringUtil::UTF8_to_UNICODE(m_desEdit->text().toStdString());

	bool isModel = true;
	QString fileType = m_fileTypeBox->currentText();
    if (fileType == codec->toUnicode(FileTypeObliquePhotogrammetry))
	{
		isModel = false;
	}

	TextureCompressType texCompType = TC_NONE;
	QString texComp = m_texCompBox->currentText();
	if (texComp == TexCompDXT)
	{
		texCompType = TC_DXT5;
	}

	S3MBVertexTag verCompType = SV_Standard;
	QString verComp = m_verCompBox->currentText();
	if (verComp == VerCompNONE)
	{
		verCompType = SV_Standard;
	}

	m_progressDialog = new QProgressDialog(this);
	m_progressDialog->setWindowModality(Qt::ApplicationModal);
	m_progressDialog->setMinimum(0);
	m_progressDialog->setMaximum(0);
    m_progressDialog->setWindowTitle(codec->toUnicode("����ִ��..."));
	m_progressDialog->setCancelButtonText(nullptr);
	m_progressDialog->setWindowFlags(Qt::Window | Qt::WindowTitleHint);
	m_progressDialog->show();

	ThreeDTilesParams* pParam = new ThreeDTilesParams();
	pParam->SetTilesetPath(strSrcPath);
	pParam->SetOutputDir(strDesPath);
	pParam->SetTextureCompressType(texCompType);
	pParam->SetVertexCompressType(verCompType);
	pParam->SetIsModel(isModel);
	
	ProcessThread* pThread = new ProcessThread(pParam);
    connect(pThread, SIGNAL(finished()), this, SLOT(handleThreadFinishedEvent()));
    connect(pThread, SIGNAL(finished()), pThread, SLOT(deleteLater()));
	pThread->start();
}

void Dialog3DTilesToS3MB::handleCancelButtonClickedEvent()
{
	this->close();
}

void Dialog3DTilesToS3MB::handleSrcFileButtonClickedEvent()
{
    QFileDialog* pFileSelectDialog = new QFileDialog(this);
    pFileSelectDialog->setWindowTitle(codec->toUnicode("��"));
    pFileSelectDialog->setNameFilter(tr("File(*.json)"));
    m_srcEdit->setText(pFileSelectDialog->getOpenFileName());
    handleTextEditedEvent();
}

void Dialog3DTilesToS3MB::handleDesFileButtonClickedEvent()
{
    QFileDialog* pFileSelectDialog = new QFileDialog(this);
    pFileSelectDialog->setWindowTitle(codec->toUnicode("��"));
    pFileSelectDialog->setFileMode(QFileDialog::Directory);
    m_desEdit->setText(pFileSelectDialog->getExistingDirectory());
    handleTextEditedEvent();
}
