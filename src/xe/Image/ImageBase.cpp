#include "ImageBase.h"

using namespace xe;

Image::ImageBase::ImageBase(int size)
	:m_iSize(size)
	, m_pData(NULL)
{
}


Image::ImageBase::~ImageBase()
{
}


bool Image::ImageBase::Allocate()
{
	m_pData = new char[m_iSize];
	if (!m_pData)
		return false;

	return true;
}

void Image::ImageBase::Release()
{
	if (m_pData)
	{
		delete m_pData;
		m_pData = NULL;
	}
}