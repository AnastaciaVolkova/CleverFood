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
    ./src/product/product.cpp \
    ./src/main.cpp \
    ./src/mainwindow.cpp \
    ./src/product/nutrition.cpp \
    ./src/product/product_ctrl.cpp \
    ./src/product/product_mdl.cpp \
    src/controller.cpp \
    src/model.cpp \
    src/target.cpp \
    src/target_generator.cpp

HEADERS += \
    ./include/mainwindow.h \
    ./include/product/nutrition.hpp \
    ./include/product/product.hpp \
    ./include/product/product_ctrl.hpp \
    ./include/product/product_ctrl_im.hpp \
    ./include/product/product_ctrl_iv.hpp \
    ./include/product/product_mdl.hpp \
    ./include/target.hpp \
    include/controller.hpp \
    include/controller_im.hpp \
    include/controller_iv.hpp \
    include/model.hpp \
    include/target_generator.hpp

FORMS += \
    ./forms/mainwindow.ui

INCLUDEPATH += ./include/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
