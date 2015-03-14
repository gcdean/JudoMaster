#-------------------------------------------------
#
# Project created by QtCreator 2014-11-22T23:41:33
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JudoMaster
TEMPLATE = app

QMAKE_CXXFLAGS += -Wunused-parameter
QMAKE_CXXFLAGS += -std=c++11
#QMAKE_CXXFLAGS += -Wc++11-extensions

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
    JMUtil.cpp \
    BracketEditor.cpp \
    BaseController.cpp \
    JMDataObj.cpp \
    BracketController.cpp \
    BracketManager.cpp \
    BracketTableModel.cpp \
    CompetitorItemDelegate.cpp \
    commands/BaseCommand.cpp \
    commands/PrintBracketsCommand.cpp \
    actions/PrintBracketsAction.cpp \
    CompetitorFilterWidget.cpp \
    CompetitorFilter.cpp \
    commands/PrintRegistrationCommand.cpp \
    BracketCompetitorTableModel.cpp \
    commands/MergeClubsCommand.cpp

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
    JMUtil.h \
    BracketEditor.h \
    BaseController.h \
    JMDataObj.h \
    BracketController.h \
    BracketManager.h \
    BracketTableModel.h \
    CompetitorItemDelegate.h \
    commands/BaseCommand.h \
    commands/PrintBrancketsCommand.h \
    actions/PrintBracketsAction.h \
    CompetitorFilterWidget.h \
    CompetitorFilter.h \
    commands/PrintRegistrationCommand.h \
    BracketCompetitorTableModel.h \
    commands/MergeClubsCommand.h

FORMS    += JudoMasterMainWindow.ui \
    ClubsEditor.ui \
    ClubEditor.ui \
    CompetitorList.ui \
    BracketEditor.ui \
    BracketManager.ui \
    CompetitorFilterWidget.ui \
    CompetitorFilterWidget.ui

RESOURCES += \
    Resources.qrc

OTHER_FILES +=
