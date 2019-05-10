#include "test_Label.h"
#include <QTimer>

TextTicker::TextTicker(QWidget *parent)
: QWidget(parent)
{
	m_curIndex = 0;//��ǰ����
	QString strText = QStringLiteral("һȥ������̴�����ҡ�̨ͤ���������˾�ʮ֦����");//��ʾ������
	m_label = new QLabel(this);
	//m_label->setMinimumWidth(100);
	//QString strHeightText = "<p style=\"line-height:%1%\">%2<p>";//�����и�
	//strText = strHeightText.arg(300).arg(strText);

	m_label->setWordWrap(true);//�Զ�����
	//m_label->setText(strText);

	//����ʡ�Ժ�
	QString strElidedText = m_label->fontMetrics().elidedText(strText, Qt::ElideRight, 100, Qt::TextShowMnemonic);
	m_label->setText(strElidedText);

	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &TextTicker::showTicker);
	timer->start(100);//��ʱ��
}

TextTicker::~TextTicker()
{

}

void TextTicker::showTicker()
{
	int iSize = m_showText.size();
	if (m_curIndex >= iSize)
		m_curIndex = 0;
	//m_label->setText(m_showText.mid(m_curIndex++));
	//m_label->setText(m_showText.right(iSize - m_curIndex--));
}