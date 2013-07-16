/*************************************************************************\
 |                                                                         |
 |  CombatAlly - A helper for D&D dungeon masters                          |
 |                                                                         |
 |  Copyright (C) 2009   Alexander Bock                                    |
 |                                                                         |
 |  This program is free software: you can redistribute it and/or modify   |
 |  it under the terms of the GNU General Public License as published by   |
 |  the Free Software Foundation, either version 3 of the License, or      |
 |  (at your option) any later version.                                    |
 |                                                                         |
 |  This program is distributed in the hope that it will be useful,        |
 |  but WITHOUT ANY WARRANTY; without even the implied warranty of         |
 |  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          |
 |  GNU General Public License for more details.                           |
 |                                                                         |
 |  You should have received a copy of the GNU General Public License      |
 |  along with this program.  If not, see <http://www.gnu.org/licenses/>.  |
 |                                                                         |
 \*************************************************************************/

#ifndef __MAINWINDOW__
#define __MAINWINDOW__

#include "aboutwidget.h"
#include "preferencesdialog.h"
#include "settings.h"

#include <QVector>
#include <QWidget>

class MonsterWidget;
class QAction;
class QDragEnterEvent;
class QDropEvent;
class QFile;
class QHttp;
class QLabel;
class QLineEdit;
class QMenuBar;
class QShortcut;
class QVBoxLayout;

/**
 * The main window of the app. New monsterwidget's are created, saved, loaded and removed here.
 * \sa MonsterWidget
 */
class MainWindow : public QWidget {
Q_OBJECT
public:
    MainWindow(QWidget* parent = 0, Qt::WindowFlags f = 0);
    ~MainWindow();

    void load(QFile& file, bool removeBeforeLoading = true);

protected slots:
    /**
     * Display a \sa AddMonsterWidget dialog window and add the appropriate monsters
     */
    void createMonster();

    /**
     * Remove the monster from which the "delete"-button was clicked
     */
    void removeMonster();

    /**
     * Display a file dialog and load the monsters from a previously saved .ca file
     */
    void load();

    /**
     * Save the current monsters with their maximum hitpoints to a file determined by a file dialog
     */
    void save();

    /**
     * Remove all currently active monsters
     */
    void removeAll();

    void displayAbout() { aboutWidget_->show(); }
    void displayPreferences() { PreferencesDialog().exec(); }
    void startUpdateTest();
    void displayUpdate();    

    void addConditionFromShortcut();

protected:
    void createActions();
    void createMenu();
    void createShortcuts();

    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

    /**
     * In this method we ensure, that the other windows are closed aswell if the main window is closed
     */
    void closeEvent(QCloseEvent* event);

    QList<MonsterWidget*> widgetList_;

    QAction* addAct_;
    QAction* loadAct_;
    QAction* saveAct_;
    QAction* quitAct_;
    QAction* removeAllAct_;
    QAction* aboutAct_;
    QAction* shortcutAct_;
    QAction* preferencesAct_;
    QAction* updateAct_;

    QShortcut* firstShortcut_;
    QShortcut* secondShortcut_;
    QShortcut* thirdShortcut_;
    QShortcut* fourthShortcut_;
    QShortcut* fifthShortcut_;
    QShortcut* sixthShortcut_;
    QShortcut* seventhShortcut_;
    QShortcut* eighthShortcut_;
    QShortcut* ninethShortcut_;
    QShortcut* tenthShortcut_;

    QHttp* http_;

    QLabel* placeholderIcon_;

    QLineEdit* name_;
    QLineEdit* hp_;

    QMenuBar* menu_;

    QVBoxLayout* layoutForEdits_;
    QVBoxLayout* mainLayout_;

    AboutWidget* aboutWidget_;

    Settings settings_;
};

#endif
