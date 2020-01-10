QT += gui
QT += widgets
TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG += qt
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
        controller.cpp \
        gerarchia/abbonamento.cpp \
        gerarchia/entrata.cpp \
        gerarchia/risparmio.cpp \
        gerarchia/transazione.cpp \
        gerarchia/uscita.cpp \
        main.cpp \
        memoria/serializer.cpp \
        model.cpp \
        views/addview.cpp \
        views/mainwindow.cpp \
        views/modview.cpp \
        views/movementlistview.cpp

HEADERS += \
    # container.h \
    controller.h \
    gerarchia/abbonamento.h \
    gerarchia/entrata.h \
    gerarchia/risparmio.h \
    gerarchia/transazione.h \
    gerarchia/uscita.h \
    memoria/container.h \
    memoria/deepptr.h \
    memoria/serializer.h \
    model.h \
    views/addview.h \
    views/mainwindow.h \
    views/modview.h \
    views/movementlistview.h

RESOURCES += \
    resource.qrc
