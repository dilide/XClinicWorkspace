
#include "MainWindow.h"
#include <QPainter>
#include <QWheelEvent>

CMainWindow::CMainWindow()
	: m_pImage(NULL)
{
	//���ô���Ϊ�̶�ͼ���ı���С
	setFixedSize(144*4,144*4);
}

CMainWindow::~CMainWindow()
{

}

void CMainWindow::paintEvent(QPaintEvent* e)
{
	//����ͼ��
	QPainter p(this);

	if(m_pImage)
	{
		//��ͼ��Ŵ�4������
		p.drawImage(QRect(0,0,144*4,144*4),*m_pImage);
	}
}

void CMainWindow::wheelEvent(QWheelEvent* e)
{
	//ͨ�������м����ĵ�ǰ��ʾ��ͼ��
	if(m_listImages.size()<1)
	{
		return;
	}
	static int m_iCurrentIndex = 0;

	m_iCurrentIndex += (e->delta()/120);
	while(m_iCurrentIndex<0)
	{
		m_iCurrentIndex+=m_listImages.size();
	}

	m_iCurrentIndex = m_iCurrentIndex%m_listImages.size();
	m_pImage = m_listImages[m_iCurrentIndex];
	update();
}

