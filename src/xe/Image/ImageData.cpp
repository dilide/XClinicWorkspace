#include "ImageData.h"

using namespace xe;

template<typename T>
T Image::ImageData<T>::GetMaxValue()
{
	return m_tMax;
}

template<typename T>
T Image::ImageData<T>::GetMinValue()
{
	return m_tMin;
}