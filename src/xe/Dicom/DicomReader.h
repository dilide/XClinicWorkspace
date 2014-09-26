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
	int m_iRows;			//ÿ��ͼ������
	int m_iColumns;			//ÿ��ͼ������
	int m_iLayers;			//�ܲ���
	int m_iBits;			//ÿһ��ռ�ݵ�λ��
};


	}
}

#endif //__XE_DICOMREADER_H__