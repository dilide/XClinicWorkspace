#ifndef __XE_DICOMREADER_H__
#define __XE_DICOMREADER_H__

#include <common.h>
#include "../Image/ImageData.h"


namespace xe
{
	namespace Dicom
	{


class XESHARED_EXPORT DicomReader
{
public:
	DicomReader();
	~DicomReader();

public:
	bool OpenDicoms(const std::list<std::string>& dcms);
	bool Release();


private:
	xe::Image::ImageBase* m_pImageData;
	int m_iRows;			//每张图的行数
	int m_iColumns;			//每张图的列数
	int m_iLayers;			//总层数
	int m_iBits;			//每一点占据的位数
};


	}
}

#endif //__XE_DICOMREADER_H__