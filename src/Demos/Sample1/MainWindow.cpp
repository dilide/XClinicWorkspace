
#include "MainWindow.h"
#include <QPainter>
#include <QWheelEvent>

CMainWindow::CMainWindow()
	: m_pImage(NULL)
{
	//设置窗口为固定图像四倍大小
	setFixedSize(144*4,144*4);
}

CMainWindow::~CMainWindow()
{

}

void CMainWindow::paintEvent(QPaintEvent* e)
{
	//绘制图像
	QPainter p(this);

	if(m_pImage)
	{
		//将图像放大4倍绘制
		p.drawImage(QRect(0,0,144*4,144*4),*m_pImage);
	}
}

void CMainWindow::wheelEvent(QWheelEvent* e)
{
	//通过滚动中键更改当前显示的图像
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

