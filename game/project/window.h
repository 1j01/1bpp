
#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

#include "world.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QWidget;
QT_END_NAMESPACE

//! [0]
class Window : public QWidget
{
	Q_OBJECT

public:
	Window();

private:
	World* world;
};
//! [0]

#endif
