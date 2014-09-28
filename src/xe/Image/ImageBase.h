#ifndef __IMAGE_BASE_H__
#define __IMAGE_BASE_H__
#include <common.h>

namespace xe
{
	namespace Image
	{

class XESHARED_EXPORT ImageBase
{
public:
	ImageBase(int size);
	~ImageBase();

public:
	bool Allocate();
	void Release();

	char* GetDataPtr(){ return m_pData; }

	virtual void UpdateData() = 0;

protected:
	char* m_pData;
	int m_iSize;
};


	}
}

#endif //__IMAGE_BASE_H__