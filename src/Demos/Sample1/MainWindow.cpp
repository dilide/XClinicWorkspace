
#include "MainWindow.h"
#include <QPainter>
#include <QWheelEvent>
#include <iostream>

#pragma comment(lib, "netapi32.lib")
#pragma comment(lib, "wsock32.lib")

CMainWindow::CMainWindow()
	: m_pImage(NULL)
	, m_iLayer(0)
	, m_iImageSize(1024)
{
	//���ô���Ϊ�̶�ͼ���ı���С
	setFixedSize(m_iImageSize, m_iImageSize);


	//������ɫ��
	for (int i = 0; i<256; ++i)
	{
		m_clrTable.push_back(qRgb(i, i, i));
	}
}

CMainWindow::~CMainWindow()
{
	m_pImage = NULL;
}

void CMainWindow::paintEvent(QPaintEvent* e)
{
	//����ͼ��
	QPainter p(this);

	QTime t1 = QTime::currentTime();


	xe::Image::ImageLayer<unsigned char>* pImageLayer = new xe::Image::ImageLayer<unsigned char>();
	m_pImage->GetImageLayer(m_iLayer, pImageLayer);


	QImage img(pImageLayer->GetDataPtr(), pImageLayer->GetWidth(), pImageLayer->GetHeight(), QImage::Format_Indexed8);
	img.setColorTable(m_clrTable);
	{
		//��ͼ��Ŵ�4������
		p.drawImage(QRect(0, 0, m_iImageSize, m_iImageSize), img);
	}

	delete pImageLayer;

	std::cout << t1.msecsTo(QTime::currentTime()) << std::endl;
}

void CMainWindow::wheelEvent(QWheelEvent* e)
{
	//ͨ�������м����ĵ�ǰ��ʾ��ͼ��

	m_iLayer += (e->delta()/120);
	while (m_iLayer<0)
	{
		m_iLayer += m_pImage->GetZ();
	}

	m_iLayer = m_iLayer%m_pImage->GetZ();
	update();
}

