
#include <QtGui>
#include "qapplication.h"
#include "glwidget.h"
#include "world.h"

//! [0]
GLWidget::GLWidget(World *world, QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent), world(world)
{
	elapsed = 0;
	setFixedSize(world->getViewRect().size());
	//setMinimumSize(250, 200);
	//setAutoFillBackground(true);
	//setGraphicsEffect(QGraphicsEffect());
	//setPalette(const QPallet &);
	//layout()->setContentsMargins(1,1,1,1);
	//layout()->setSpacing( 0 );
	//layout()->setMargin( 0 );
	setFocus();
	show();
}
//! [0]

//! [1]
void GLWidget::animate()
{
	elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval());
	repaint();
}
//! [1]

//! [2]
void GLWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	world->step();
	world->draw(&painter);
	painter.end();
}
//! [2]
void GLWidget::keyPressEvent( QKeyEvent *k )
{
	switch (k->key() ) {
		case Qt::Key_R :
			// reload
			//delete world;
			world=new World(this->window()->size());
			break;
		case Qt::Key_Escape:
			// quit
            QApplication::exit(1337);
			break;
		case Qt::Key_A:
		case Qt::Key_Left:
			world->keyLeft=true;
			break;
		case Qt::Key_S:
		case Qt::Key_Down:
			world->keyDown=true;
			break;
		case Qt::Key_D:
		case Qt::Key_Right:
			world->keyRight=true;
			break;
		case Qt::Key_W:
		case Qt::Key_Up:
		case Qt::Key_Z:
		case Qt::Key_Space:
			world->keyUp=true;
			break;
		case Qt::Key_M:
			world->keyMap=true;
			break;
	}
}
void GLWidget::keyReleaseEvent( QKeyEvent *k )
{
	switch (k->key() ) {
		case Qt::Key_A:
		case Qt::Key_Left:
			world->keyLeft=false;
			break;
		case Qt::Key_S:
		case Qt::Key_Down:
			world->keyDown=false;
			break;
		case Qt::Key_D:
		case Qt::Key_Right:
			world->keyRight=false;
			break;
		case Qt::Key_W:
		case Qt::Key_Up:
		case Qt::Key_Z:
		case Qt::Key_Space:
			world->keyUp=false;
			break;
		case Qt::Key_M:
			world->keyMap=false;
			break;
	}
}
