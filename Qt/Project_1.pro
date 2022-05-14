QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    create_blog.cpp \
    main.cpp \
    mainblogwindow.cpp \
    mainwindow.cpp \
    reading_blog.cpp \
    register_dialog.cpp

HEADERS += \
    create_blog.h \
    mainblogwindow.h \
    mainwindow.h \
    reading_blog.h \
    register_dialog.h

FORMS += \
    create_blog.ui \
    mainblogwindow.ui \
    mainwindow.ui \
    reading_blog.ui \
    register_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    icons.qrc
