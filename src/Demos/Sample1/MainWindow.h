#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <Dicom\DicomReader.h>



template<typename T>
class RImageData
{
public:
	RImageData(T* pData, int x, int y, int z)
	{
		m_pImageData = pData;
		iX = x;
		iY = y;
		iZ = z;

		getMinAndMax<T>(m_pImageData, iX*iY*iZ, m_fMin, m_fMax);

		//计算转为256灰度图像时的间距
		//double fPer = (m_fMax - m_fMin) / 256;
	}


public:
	T* m_pImageData;
	int iX;
	int iY;
	int iZ;

	T m_fMax;
	T m_fMin;
};


class CMainWindow : public QWidget
{
	Q_OBJECT
public:
	CMainWindow();
	~CMainWindow();

	void SetImageData(xe::Image::ImageBase* p)
	{
		m_pImage = reinterpret_cast<xe::Image::ImageData<short>*>(p);
	}

public:
	virtual void paintEvent(QPaintEvent* e);
	virtual void wheelEvent(QWheelEvent* e);

private:
	xe::Image::ImageData<short>* m_pImage;
	int m_iLayer;
	QVector<QRgb> m_clrTable;

	int m_iImageSize;
};


#endif	//MAIN_WINDOW_H