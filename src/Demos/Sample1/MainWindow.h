#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui>

class CMainWindow : public QWidget
{
	Q_OBJECT
public:
	CMainWindow();
	~CMainWindow();

	void SetImages(const QList<QImage*>& imgs)
	{
		m_listImages = imgs;
		if(m_listImages.size()>0)
		{
			m_pImage = m_listImages[0];
		}
	}

public:
	virtual void paintEvent(QPaintEvent* e);
	virtual void wheelEvent(QWheelEvent* e);

private:
	QList<QImage*> m_listImages;
	QImage* m_pImage;
};


#endif	//MAIN_WINDOW_H