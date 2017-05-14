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
    Camera.cpp

HEADERS += \
    Mesh.h \
    SceneGenerator.h \
    NameGenerator.h \
    GameObject.h \
    Ship.h \
    SDLOpenGL.h \
    Camera.h
}
!win32 : {
SOURCES += $$pwd/main.cpp \
    $$pwd/Mesh.cpp \
    $$pwd/Ship.cpp \
    $$pwd/GameObject.cpp \
    $$pwd/SceneGenerator.cpp \
    $$pwd/SDLOpenGL.cpp \
    $$pwd/Camera.cpp

HEADERS += \
    $$pwd/Mesh.h \
    $$pwd/SceneGenerator.h \
    $$pwd/NameGenerator.h \
    $$pwd/GameObject.h \
    $$pwd/Ship.h \
    $$pwd/SDLOpenGL.h \
    $$pwd/Camera.h
}
CONFIG-=app_bundle
win32 : {
LIBS+= -LSDL2-2.0.5\lib\x86
LIBS+= -LQt\5.8\mingw53_32\bin
LIBS+= -LQt\Tools\mingw530_32\bin
}
macx:QMAKE_CXXFLAGS+= -arch x86_64

!win32 :{
QMAKE_CXXFLAGS += $$system(sdl2-config --cflags)
LIBS+=$$system(sdl2-config --libs)
}

!win32:LIBS += -L/usr/local/lib
macx:LIBS+= -framework OpenGL


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

HEADERS += \
    SDLgui.h

SOURCES += \
    SDLgui.cpp
