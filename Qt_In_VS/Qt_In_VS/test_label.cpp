#include "test_Label.h"
#include <QTimer>

TextTicker::TextTicker(QWidget *parent)
: QWidget(parent)
{
	m_curIndex = 0;//当前角码
	QString strText = QStringLiteral("一去二三里，烟村四五家。亭台六七座，八九十枝花。");//显示的文字
	m_label = new QLabel(this);
	//m_label->setMinimumWidth(100);
	//QString strHeightText = "<p style=\"line-height:%1%\">%2<p>";//设置行高
	//strText = strHeightText.arg(300).arg(strText);

	m_label->setWordWrap(true);//自动换行
	//m_label->setText(strText);

	//设置省略号
	QString strElidedText = m_label->fontMetrics().elidedText(strText, Qt::ElideRight, 100, Qt::TextShowMnemonic);
	m_label->setText(strElidedText);

	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &TextTicker::showTicker);
	timer->start(100);//定时器
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