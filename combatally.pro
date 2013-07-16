TEMPLATE	= app
CONFIG		+= qt warn_on
QT += network
TARGET		= CombatAlly
QTDIR_build:REQUIRES="contains(QT_CONFIG, small-config)"

# install
target.path = ./
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS combatally.pro
sources.path = ./
INSTALLS += target sources

RESOURCES = combatally.qrc

RC_FILE = combatally.rc

ICON = images/swords.icns

HEADERS = \
	aboutwidget.h \
    addconditiondialog.h \
	addmonsterdialog.h \
    mainwindow.h \
    monster.h \
    monsterwidget.h \
    preferencesdialog.h \
    settings.h \
    version.h

SOURCES = \
	aboutWidget.cpp \
    addconditiondialog.cpp \
	addmonsterdialog.cpp \
    main.cpp  \
    mainwindow.cpp \ 
    monster.cpp \
    monsterwidget.cpp \
    preferencesdialog.cpp \
   