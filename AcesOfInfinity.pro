# we are going to build an app
TEMPLATE=app
CONFIG+=c++11
CONFIG+=debug
# qt 5 wants this may cause errors with 4
isEqual(QT_MAJOR_VERSION, 5) {cache() }
QT += opengl
QT -= corex`
win32 : {
SOURCES += main.cpp \
    Mesh.cpp \
    Ship.cpp \
    GameObject.cpp \
    SceneGenerator.cpp \
    SDLOpenGL.cpp \
    Camera.cpp \
    SDLgui.cpp

HEADERS += \
    Mesh.h \
    SceneGenerator.h \
    NameGenerator.h \
    GameObject.h \
    Ship.h \
    SDLOpenGL.h \
    Camera.h \
    SDLgui.h
}
!win32 : {
SOURCES += $$PWD/main.cpp \
    $$PWD/Mesh.cpp \
    $$PWD/Ship.cpp \
    $$PWD/GameObject.cpp \
    $$PWD/SceneGenerator.cpp \
    $$PWD/SDLOpenGL.cpp \
    $$PWD/Camera.cpp \
    $$PWD/SDLgui.cpp

HEADERS += \
    $$PWD/Mesh.h \
    $$PWD/SceneGenerator.h \
    $$PWD/NameGenerator.h \
    $$PWD/GameObject.h \
    $$PWD/Ship.h \
    $$PWD/SDLOpenGL.h \
    $$PWD/Camera.h \
    $$PWD/SDLgui.h
}
CONFIG-=app_bundle
win32 : {
LIBS+= -LSDL2-2.0.5\lib\x86
LIBS+= -LQt\5.8\mingw53_32\bin
LIBS+= -LQt\Tools\mingw530_32\bin
}

!win32 :{
QMAKE_CXXFLAGS += $$system(sdl2-config --cflags)
LIBS+=$$system(sdl2-config --libs)
LIBS += -L/usr/local/lib
macx:LIBS+= -framework OpenGL
macx:QMAKE_CXXFLAGS+= -arch x86_64
}


win32 : {
DEFINES+=_USE_MATH_DEFINES
INCLUDEPATH += C:\PPP\SDL2-2.0.5\include
INCLUDEPATH += C:\PPP\SDL2_ttf-2.0.14\include
INCLUDEPATH += C:\PPP\glm-0.9.8.4
LIBS += C:\PPP\SDL2-2.0.5\lib\x86\SDL2.lib
LIBS += C:\PPP\SDL2_ttf-2.0.14\lib\x86\SDL2_ttf.lib
LIBS += -lOpenGL32
CONFIG+=console
DLLDESTDIR
}
