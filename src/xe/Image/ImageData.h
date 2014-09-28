#ifndef __IMAGE_DATA_H__
#define __IMAGE_DATA_H__
#include <common.h>
#include "../Math/Math.h"
#include "ImageBase.h"
#include "ImageLayer.h"
namespace xe
{
	namespace Image
	{


template<typename T>
class ImageData : public ImageBase
{
public:
	ImageData(int x, int y, int z)
		: ImageBase(x*y*z*sizeof(T))
		, m_iX(x)
		, m_iY(y)
		, m_iZ(z)
	{
		Allocate();
		m_pDataT = reinterpret_cast<T*>(m_pData);
	}
	~ImageData()
	{
		Release();
	}

public:
	virtual void UpdateData()
	{
		Math::Math<T>::GetMinAndMax(m_pDataT,m_iX*m_iY*m_iZ,m_tMin,m_tMax);
	}

public:
	T GetMaxValue()const{ return m_tMax; }
	T GetMinValue()const{ return m_tMin; }

	int GetX()const{ return m_iX; }
	int GetY()const{ return m_iY; }
	int GetZ()const{ return m_iZ; }

	T GetMaxT()const{ return m_tMax; }
	T GetMinT()const{ return m_tMin; }


	bool GetImageLayer(int iLayer, ImageLayer<T>* pImageLayer)
	{
		pImageLayer->Resize(m_iX, m_iY);

		T* pData = pImageLayer->GetDataPtr();
		if (pData && m_pDataT)
		{
			memcpy(pData, m_pDataT + (iLayer*m_iX*m_iY), m_iX*m_iY*sizeof(T));
			return true;
		}

		return false;
	}

	bool GetImageLayer(int iLayer, ImageLayer<unsigned char>* pImageLayer)
	{
		pImageLayer->Resize(m_iX, m_iY);

		unsigned char* pDataDest = pImageLayer->GetDataPtr();
		T* pDataSrc = m_pDataT + iLayer*m_iX*m_iY;
		float fPer = (m_tMax - m_tMin) / 256;

		if (pDataDest && pDataSrc)
		{
#pragma omp parallel for
			for (int i = 0; i < m_iX*m_iY; ++i)
			{
				pDataDest[i] = (pDataSrc[i] - m_tMin) / fPer;
			}

			return true;
		}

		return false;
	}

private:
	T* m_pDataT;
	int m_iX;
	int m_iY;
	int m_iZ;

	T m_tMax;
	T m_tMin;
};


	}
}

#endif //__IMAGE_DATA_H__