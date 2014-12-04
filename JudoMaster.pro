#-------------------------------------------------
#
# Project created by QtCreator 2014-11-22T23:41:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JudoMaster
TEMPLATE = app


SOURCES += main.cpp\
        JudoMasterMainWindow.cpp \
    Competitor.cpp \
    Club.cpp \
    Tournament.cpp \
    ClubsEditor.cpp \
    ClubEditor.cpp \
    CompetitorList.cpp \
    ClubController.cpp \
    JudoMasterApplication.cpp \
    ClubListModel.cpp \
    CompetitorTableModel.cpp \
    CompetitorController.cpp \
    Bracket.cpp \
    JMUtil.cpp

HEADERS  += JudoMasterMainWindow.h \
    Competitor.h \
    Club.h \
    Tournament.h \
    ClubsEditor.h \
    ClubEditor.h \
    CompetitorList.h \
    ClubController.h \
    JudoMasterApplication.h \
    ClubListModel.h \
    CompetitorTableModel.h \
    CompetitorController.h \
    Bracket.h \
    JMUtil.h

FORMS    += JudoMasterMainWindow.ui \
    ClubsEditor.ui \
    ClubEditor.ui \
    CompetitorList.ui

RESOURCES += \
    Resources.qrc

OTHER_FILES +=
