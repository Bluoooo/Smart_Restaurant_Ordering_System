QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Dish.cpp \
    DishesMapOperator.cpp \
    OrderOperator.cpp \
    bank.cpp \
    card.cpp \
    checkout_window.cpp \
    checkoutoperator.cpp \
    main.cpp \
    mainwindow.cpp\
    order_window.cpp \
    rating_window.cpp \
    secondwindow.cpp \
    ui0.cpp \
    waitTime.cpp \
    waiter.cpp \
    waiter_window.cpp


HEADERS += \
    Dish.h \
    DishesMapOperator.h \
    OrderOperator.h \
    bank.h \
    card.h \
    checkout_window.h \
    checkoutoperator.h \
    mainwindow.h \
    order_window.h \
    rating_window.h \
    secondwindow.h \
    waitTime.h \
    waiter.h \
    waiter_window.h

FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT+=sql

DISTFILES += \
    card_information \
    dishes_data





