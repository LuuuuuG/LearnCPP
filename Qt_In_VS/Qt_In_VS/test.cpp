#include "test.h"
#include <QPainter>

Test::Test(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Test::~Test()
{

}

void Test::paintEvent(QPaintEvent *) {
	// �����ϵĵ�
	static QList<QPointF> points = QList<QPointF>() << QPointF(0, 0) << QPointF(100, 100) << QPointF(200, -100)
		<< QPointF(300, 100) << QPointF(330, -80) << QPointF(350, -70);
	QPainterPath path(points[0]);
	//����
	for (int i = 0; i < points.size() - 1; ++i) {
		// ���Ƶ�� x ����Ϊ sp �� ep �� x ����͵�һ��
		// ��һ�����Ƶ� c1 �� y ����Ϊ��ʼ�� sp �� y ����
		// �ڶ������Ƶ� c2 �� y ����Ϊ������ ep �� y ����
		QPointF sp = points[i];
		QPointF ep = points[i + 1];
		QPointF c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
		QPointF c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
		path.cubicTo(c1, c2, ep);
	}
	QPainter painter(this);
	//������Ⱦ��ʾΪ�������
	painter.setRenderHint(QPainter::Antialiasing, true);
	//���û�����ɫ�Ϳ��
	painter.setPen(QPen(Qt::black, 2));
	//������ϵת��Ϊʸ��
	painter.translate(40, 130);
	//����path
	painter.drawPath(path);
	// ���������ϵĵ�
	painter.setBrush(Qt::gray);
	//���������ϵĵ�
	for (int i = 0; i < points.size(); ++i) {
		painter.drawEllipse(points[i], 4, 4);
	}
}