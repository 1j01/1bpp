QT				   += opengl

HEADERS = \
	glwidget.h \
	window.h \
	world.h \
	obj.h \
	tile.h \
	globaldefines.h \
	connection.h \
	player.h

SOURCES = \
	glwidget.cpp \
	main.cpp \
	window.cpp \
	world.cpp \
	obj.cpp \
	tile.cpp \
	connection.cpp \
	player.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/1bpp/targ
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS 1bpp.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/opengl/1bpp
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)

symbian: warning(This example might not fully work on Symbian platform)
simulator: warning(This example might not fully work on Simulator platform)

OTHER_FILES += \
	grassiness.gml \
    simplex.js

RESOURCES += \
	app.qrc

