#include <Windows.h>
//#include <gl\glut.h>
//#include <gl\GL.h>
#include <fstream>
#include <iostream>
#include "MainWindow.h"
#include <QApplication>
#include <Dicom\DicomReader.h>


int* g_pImageData = NULL;

/*
void drawString(const char* str)
{
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // 如果是第一次调用，执行初始化
		// 为每一个ASCII字符产生一个显示列表
		isFirstCall = 0;

		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);

		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}

	// 调用每个字符对应的显示列表，绘制每个字符
	int t = strlen(str);
	for (int j=0; j<t; ++j)
	{
		glCallList(lists + str[j]);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(0.0f, 0.0f);
	drawString("Hello, World!");
	drawString("Hello, 123!");

	glutSwapBuffers();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
*/


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));

	QDir dir("E:\\Document\\AMI.DATA\\Body_OSEM\\CT\\");
	QFileInfoList listFiles = dir.entryInfoList(QStringList() << "*.dcm");

	std::list<std::string> listDcms;
	for (int i = 0; i < listFiles.size(); ++i)
	{
		listDcms.push_back(listFiles[i].absoluteFilePath().toStdString());
	}

	xe::Dicom::DicomReader* m_pDcmReader = new xe::Dicom::DicomReader();
	if (m_pDcmReader->OpenDicoms(listDcms))
	{

	}

	return -1;
	//读取数据
	QFile file("D:\\1.dat");
	file.open(QFile::ReadOnly);
	QByteArray all = file.readAll();
	char* pData = all.data();

	//获取最大值和最小值
	g_pImageData = (int*)(pData);

	//生成所有的图像

	//显示图像
	CMainWindow w;
//	RImageData<int>* pImage = new RImageData<int>(g_pImageData, PIXEL_SIZE, PIXEL_SIZE, VOX_LAYER);
//	w.SetImageData(pImage);
	w.show();

	app.exec();


	//清理内存

	return 1;
}