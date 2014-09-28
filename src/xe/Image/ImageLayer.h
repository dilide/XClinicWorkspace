#ifndef __IMAGE_LAYER_H__
#define __IMAGE_LAYER_H__
#include <common.h>

namespace xe
{
	namespace Image
	{

template<typename T>
class ImageLayer
{
public:
	ImageLayer()
		: m_iWidth(0)
		, m_iHeight(0)
		, m_pDataT(NULL)
	{
	}

	ImageLayer(int iW,int iH)
		: m_iWidth(iW)
		, m_iHeight(iH)
		, m_pDataT(NULL)
	{
		Allocate();
	}
	~ImageLayer()
	{
		Release();
	}

public:
	bool Allocate()
	{
		if (m_pDataT)
		{
			assert("not null pointer.");
			return false;
		}
		if (m_iWidth>0 && m_iHeight>0)
		{
			m_pDataT = new T[m_iWidth*m_iHeight];
			return true;
		}

		return false;
	}
	void Release()
	{
		if (m_pDataT)
		{
			delete m_pDataT;
			m_pDataT = NULL;
		}
	}

	bool Resize(int iW, int iH)
	{
		if (iW != m_iWidth || iH != m_iHeight)
		{
			m_iWidth = iW;
			m_iHeight = iH;
			Release();
			Allocate();
		}
		else
		{
			if (m_pDataT == NULL)
			{
				Allocate();
			}
		}

		return true;
	}


	int GetWidth()const{ return m_iWidth; }
	int GetHeight()const{ return m_iHeight; }
	int GetSize()const{ return m_iWidth*m_iHeight; }
	T* GetDataPtr(){ return m_pDataT; }

private:
	T* m_pDataT;
	int m_iWidth;
	int m_iHeight;
};

	}
}

#endif //__IMAGE_LAYER_H__