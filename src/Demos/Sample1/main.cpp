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

	if (isFirstCall) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
		// Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
		isFirstCall = 0;

		// ����MAX_CHAR����������ʾ�б���
		lists = glGenLists(MAX_CHAR);

		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}

	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
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
	//��ȡ����
	QFile file("D:\\1.dat");
	file.open(QFile::ReadOnly);
	QByteArray all = file.readAll();
	char* pData = all.data();

	//��ȡ���ֵ����Сֵ
	g_pImageData = (int*)(pData);

	//�������е�ͼ��

	//��ʾͼ��
	CMainWindow w;
//	RImageData<int>* pImage = new RImageData<int>(g_pImageData, PIXEL_SIZE, PIXEL_SIZE, VOX_LAYER);
//	w.SetImageData(pImage);
	w.show();

	app.exec();


	//�����ڴ�

	return 1;
}