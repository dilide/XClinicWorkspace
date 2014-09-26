#ifndef __IMAGE_DATA_H__
#define __IMAGE_DATA_H__
#include <common.h>
#include "ImageBase.h"

namespace xe
{
	namespace Image
	{


template<typename T>
class XESHARED_EXPORT ImageData : public ImageBase
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
	T GetMaxValue();
	T GetMinValue();


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