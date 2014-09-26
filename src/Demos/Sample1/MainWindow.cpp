
#include "MainWindow.h"
#include <QPainter>
#include <QWheelEvent>
#include <iostream>

#pragma comment(lib, "netapi32.lib")
#pragma comment(lib, "wsock32.lib")

CMainWindow::CMainWindow()
	: m_pImage(NULL)
	, m_iLayer(0)
	, m_iImageSize(512)
{
	//设置窗口为固定图像四倍大小
	setFixedSize(m_iImageSize, m_iImageSize);


	//创建颜色表
	for (int i = 0; i<256; ++i)
	{
		m_clrTable.push_back(qRgb(i, i, i));
	}

	m_pImg = new QImage(m_iImageSize, m_iImageSize, QImage::Format_Indexed8);
	m_pImg->setColorTable(m_clrTable);
}

CMainWindow::~CMainWindow()
{
	delete m_pImage;
}

void CMainWindow::paintEvent(QPaintEvent* e)
{
	//绘制图像
	QPainter p(this);


	float fPer = (m_pImage->m_fMax - m_pImage->m_fMin) / 256;

	QTime t1 = QTime::currentTime();

#pragma omp parallel for
	for (int x = 0; x < m_pImage->iZ; ++x)
	{
		for (int y = 0; y < m_pImage->iY;++y)
		{
			int iM = m_pImage->m_pImageData[x*m_pImage->iX*m_pImage->iY + y*m_pImage->iX + m_iLayer];
			for (int z = 0; z < 50; ++z)
			{
				if (z > m_pImage->iZ)
					break;

				int v = m_pImage->m_pImageData[x*m_pImage->iX*m_pImage->iY + y*m_pImage->iX + m_iLayer + z];
				if (v > iM)
					iM = v;
			}

			uchar v1 = (iM - m_pImage->m_fMin) / fPer;
			m_pImg->setPixel(x, y, v1);
		}
	}

	std::cout << t1.msecsTo(QTime::currentTime()) << std::endl;


	{
		//将图像放大4倍绘制
		p.drawImage(QRect(0, 0, m_iImageSize, m_iImageSize), *m_pImg);
	}
}

void CMainWindow::wheelEvent(QWheelEvent* e)
{
	//通过滚动中键更改当前显示的图像

	m_iLayer += (e->delta()/120);
	while (m_iLayer<0)
	{
		m_iLayer += m_pImage->iZ;
	}

	m_iLayer = m_iLayer%m_pImage->iZ;
	update();
}

