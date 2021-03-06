#include "DicomReader.h"
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmdata/dcpath.h>
#include <dcmtk/dcmimgle/dcmimage.h>

#if defined(_MSC_VER)
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Netapi32.lib")
#endif

using namespace xe;

Dicom::DicomReader::DicomReader()
	: m_pImageData(NULL)
	, m_iRows(0)
	, m_iColumns(0)
	, m_iLayers(0)
{

}

Dicom::DicomReader::~DicomReader()
{
	Release();
}

bool Dicom::DicomReader::OpenDicoms(const std::list<std::string>& dcms)
{
	if (m_pImageData)
	{
		//已经打开了数据
		return false;
	}

	std::map<int,DcmFileFormat*> mapDcms;

	int iMaxLayer = -1;
	int iMinLayer = INT_MAX;

	{
		//获取图像数据
		std::list<std::string>::const_iterator iter = dcms.begin();
		while (iter != dcms.end())
		{
			DcmFileFormat* pDcmFile = new DcmFileFormat();
			OFCondition cond = pDcmFile->loadFile(iter->c_str());
			if (cond.bad())
			{
				delete pDcmFile;
				++iter;
				continue;
			}

			DcmDataset* pDataset = pDcmFile->getDataset();

			Uint16 iC = 0, iR = 0, iB = 0;
			pDataset->findAndGetUint16(DCM_Columns, iC);
			pDataset->findAndGetUint16(DCM_Rows, iR);
			pDataset->findAndGetUint16(DCM_BitsAllocated, iB);
			if (mapDcms.size()<1)
			{
				m_iColumns = iC;
				m_iRows = iR;
				m_iBits = iB;
			}

			if (iC != m_iColumns || iR != m_iRows || iB != m_iBits)
			{
				delete pDcmFile;
				++iter;
				continue;
			}

			Sint32 iL = -1;

			pDataset->findAndGetSint32(DCM_InstanceNumber, iL);
			if (iL>-1 && mapDcms.find(iL) == mapDcms.end())
			{
				mapDcms[iL] = pDcmFile;
				if (iL > iMaxLayer)
					iMaxLayer = iL;
				if (iL < iMinLayer)
					iMinLayer = iL;
			}
			else
			{
				delete pDcmFile;
			}

			++iter;
		}

		if (m_iBits != 16)
			return false;
	}


	//总层数
	m_iLayers = iMaxLayer-iMinLayer+1;
	m_pImageData = new Image::ImageData<short>(m_iRows, m_iColumns, m_iLayers);
	Image::ImageData<short>* pImageShort = reinterpret_cast<Image::ImageData<short>*>(m_pImageData);
	char* pDataPtr = m_pImageData->GetDataPtr();

	{
		//设置图像数据
		std::map<int, DcmFileFormat*>::iterator iter = mapDcms.begin();
		while (iter != mapDcms.end())
		{
			DcmFileFormat* pDcmFile = iter->second;
			DcmDataset* pDataSet = pDcmFile->getDataset();
			{
				const Uint16* pSrcData = NULL;
				unsigned long iCount = 0;
				pDataSet->findAndGetUint16Array(DCM_PixelData, pSrcData, &iCount);
				if (iCount == pImageShort->GetX()*pImageShort->GetY())
				{
					memcpy(pDataPtr+(iCount*2*(iter->first-iMinLayer)), pSrcData, iCount * 2);
				}
				else
				{
					assert("Read dicom error!");
				}
			}
			delete pDcmFile;

			++iter;
		}

		mapDcms.clear();
	}

	m_pImageData->UpdateData();

	return true;
}

bool Dicom::DicomReader::Release()
{
	if (m_pImageData)
	{
		delete m_pImageData;
		m_pImageData = NULL;
	}

	m_iRows = 0;
	m_iColumns = 0;
	m_iLayers = 0;
	return true;
}