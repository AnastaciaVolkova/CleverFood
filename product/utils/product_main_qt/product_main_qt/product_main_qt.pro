QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../application/qt/main.cpp \
    ../../../application/qt/qtview.cpp \
    ../../../src/context.cpp \
    ../../../src/nutrition.cpp \
    ../../../src/product.cpp \
    ../../../src/product_ctrl.cpp \
    ../../../src/product_mdl.cpp \
    ../../../src/state.cpp \
    ../../../src/storage_text.cpp

HEADERS += \
    ../../../application/qt/qtview.h \
    ../../../include/context.hpp \
    ../../../include/nutrition.hpp \
    ../../../include/product.hpp \
    ../../../include/product_ctrl.hpp \
    ../../../include/product_ctrl_im.hpp \
    ../../../include/product_ctrl_iv.hpp \
    ../../../include/product_mdl.hpp \
    ../../../include/product_view_i.hpp \
    ../../../include/state.hpp \
    ../../../include/storage_i.hpp \
    ../../../include/storage_text.hpp
    
INCLUDEPATH += \
    ../../../include
    
FORMS += \
    ../../../application/qt/qtview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
