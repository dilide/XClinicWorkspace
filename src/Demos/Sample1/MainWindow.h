#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <omp.h>

#if defined(ENABLE_OPENMP)
#else
typedef int omp_int_t;
inline omp_int_t omp_get_thread_num() { return 0;}
inline omp_int_t omp_get_max_threads() { return 1;}
#endif

template<typename T>
bool getMinAndMax(T* pData, int count, T& min, T& max)
{
	min = *pData;
	max = *pData;

	int coreNum = omp_get_max_threads();//获得处理器个数
	T* minArray = new T[coreNum];//对应处理器个数，先生成一个数组
	T* maxArray = new T[coreNum];
	for (int i = 0; i < coreNum; ++i)
	{
		minArray[i] = *pData;
		maxArray[i] = *pData;
	}


#pragma omp parallel for
	for (int i = 0; i<count; ++i)
	{
		int k = omp_get_thread_num();
		if (pData[i] > maxArray[k])
		{
			maxArray[k] = pData[i];
		}
		if (pData[i] < minArray[k])
		{
			minArray[k] = pData[i];
		}
	}


	for (int i = 0; i < coreNum; ++i)
	{
		if (max < maxArray[i])
			max = maxArray[i];
		if (min > minArray[i])
			min = minArray[i];
	}

	delete maxArray;
	delete minArray;

	return true;
}



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

	void SetImageData(RImageData<int>* p)
	{
		m_pImage = p;
	}

public:
	virtual void paintEvent(QPaintEvent* e);
	virtual void wheelEvent(QWheelEvent* e);

private:
	RImageData<int>* m_pImage;
	int m_iLayer;
	QVector<QRgb> m_clrTable;
	QImage* m_pImg;

	int m_iImageSize;
};


#endif	//MAIN_WINDOW_H