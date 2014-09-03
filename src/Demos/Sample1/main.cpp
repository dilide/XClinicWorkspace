#include <iostream>
#include "MainWindow.h"
#include <QApplication>
#include <QFile>

#define PIXEL_SIZE	144

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
//	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
//	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));



	//读取数据
	QFile file("D:\\1.dat");
	file.open(QFile::ReadOnly);
	QByteArray all = file.readAll();
	char* pData = all.data();


	//创建颜色表
	QVector<QRgb> clrTable;
	for (int i=0;i<256;++i)
	{
		clrTable.push_back(qRgb(i,i,i));
	}

	//获取最大值和最小值
	float* pFloat = (float*)(pData);
	float fMax = *pFloat;
	float fMin = *pFloat;

	int iIndex = 0;
	while (iIndex<PIXEL_SIZE*PIXEL_SIZE*PIXEL_SIZE)
	{
		if(pFloat[iIndex]>fMax)
			fMax = pFloat[iIndex];
		if(pFloat[iIndex]<fMin)
			fMin = pFloat[iIndex];

		++iIndex;
	}

	//计算转为256灰度图像时的间距
	double fPer = (fMax-fMin)/256;

	//生成所有的图像
	QList<QImage*> listImages;
	for(int z=0;z<PIXEL_SIZE;++z)
	{
		QImage* pImage = new QImage(PIXEL_SIZE,PIXEL_SIZE,QImage::Format_Indexed8);
		pImage->setColorTable(clrTable);

		for(int y=0;y<PIXEL_SIZE;++y)
		{
			for(int x=0;x<PIXEL_SIZE;++x)
			{
				float fVal = pFloat[PIXEL_SIZE*PIXEL_SIZE*z+PIXEL_SIZE*y+x];
				int iVal = (fVal-fMin)/fPer;
				if(iVal>255)
					iVal = 255;

				if(iVal<58)
				{
					pImage->setPixel(x,y,0);
				}
				else
				{
					pImage->setPixel(x,y,255);
				}

			}
		}
		listImages.push_back(pImage);
	}

	//显示图像
	CMainWindow w;
	w.SetImages(listImages);
	w.show();

	app.exec();


	//清理内存
	QList<QImage*>::iterator iter = listImages.begin();
	while (iter!=listImages.end())
	{
		delete *iter;
		++iter;
	}
	listImages.clear();

	return 1;
}
