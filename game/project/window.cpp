
#include <QtGui>
#include "glwidget.h"
#include "window.h"

//! [0]
Window::Window()
	: QWidget()
{
	setFixedSize(256,256);
	world=new World(this->window()->size());

	GLWidget *openGL = new GLWidget(world, this);
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(openGL);
	layout->setMargin(0);
	setLayout(layout);

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), openGL, SLOT(animate()));
	timer->start(50);

	setWindowTitle(tr("1BPP Games"));
	//setWindowIcon(QIcon(":/images/icon.png"));
	//showFullScreen();
	QPalette pal = this->palette();
	pal.setColor(this->backgroundRole(),Qt::black);
	this->setPalette(pal);
}
//! [0]
