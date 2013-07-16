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

#include "addconditiondialog.h"
#include "addmonsterdialog.h"
#include "mainwindow.h"
#include "monsterwidget.h"
#include "monster.h"
#include "version.h"

#include <QtGui>
#include <QtNetwork>

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags f)
    : QWidget(parent,f)
{
#ifndef __APPLE__
    // On a Mac it looks bad with an icon, on Windows it looks bad without
    setWindowIcon(QIcon(":/images/swords.png"));
#endif

    setAcceptDrops(true);

    mainLayout_ = new QVBoxLayout(this);

    placeholderIcon_ = new QLabel();
    placeholderIcon_->setPixmap(QPixmap(":/images/swords.png"));
    mainLayout_->addWidget(placeholderIcon_);

    createActions();
    createMenu();
    createShortcuts();

    aboutWidget_ = new AboutWidget();

    // Reset the recently used conditions if it is wanted
    if (settings_.conditionsDeleteOnStartup()) {
        int maximumRecent = settings_.value("Conditions/Maximum", 15).toInt();
        for (int iter = 0; iter < maximumRecent; ++iter)
            settings_.setValue("Conditions/Number" + QString::number(iter), "");
        settings_.setConditionsMostRecently(0);
    }
}

MainWindow::~MainWindow() {
    removeAll();
    delete aboutWidget_;
}

void MainWindow::createMonster() {
    QString name;
    int maxHP;
    int count;
    AddMonsterDialog widget(&name, &maxHP, &count);

    if (widget.exec() == QDialog::Accepted) {
        for (int i = 1; i <= count; ++i) {
            MonsterWidget* wnd;
            if (i == 1)
                wnd = new MonsterWidget(new Monster(name, maxHP), this);
            else
                wnd = new MonsterWidget(new Monster(name + " " + QString::number(i), maxHP), this);
            widgetList_.push_back(wnd);
            mainLayout_->addWidget(wnd);
            wnd->show();
        }

        placeholderIcon_->hide();
        setMinimumSize(0,0);
        adjustSize();
    }
}

void MainWindow::removeMonster() {
    int ret = QMessageBox::question(0, "Remove monster", "Are you sure to remove the monster?",
                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    if (ret == QMessageBox::Yes) {
        // We want to remove the parent of the button which send this signal
        QPushButton* btn = dynamic_cast<QPushButton*>(QObject::sender());
        MonsterWidget* wnd = dynamic_cast<MonsterWidget*>(btn->parentWidget());
        
        mainLayout_->removeWidget(wnd);
        widgetList_.removeOne(wnd);
        wnd->disconnectButton();
        wnd->setVisible(false);
        
        if (widgetList_.empty())
            placeholderIcon_->show();

        setMinimumSize(0,0);
        adjustSize();
    }
}

void MainWindow::removeAll() {
    foreach (MonsterWidget* wdt, widgetList_) {
        mainLayout_->removeWidget(wdt);
        wdt->disconnectButton();
        wdt->hide();
        delete wdt;
    }
    
    widgetList_.clear();

    placeholderIcon_->show();
    setMinimumSize(0,0);
    adjustSize();
}

void MainWindow::load() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Monster File", "", "CombatAlly files (*.ca)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        load(file);        
    }
}

void MainWindow::load(QFile& file, bool removeBeforeLoading) {
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        if (removeBeforeLoading)
            removeAll();

        while (!file.atEnd()) {
            QString line = QString(file.readLine());
            QStringList list = line.split('\t');

            if (list.size() != 2) {
                QMessageBox msgBox(QMessageBox::Warning, "File error", "The format of the file is wrong. \n\
The name and the hitpoints have to be seperated by a tab in the file");
                msgBox.exec();
            }

            MonsterWidget* wnd = new MonsterWidget(new Monster(list.at(0), list.at(1).toInt()), this);
            widgetList_.push_back(wnd);
            mainLayout_->addWidget(wnd);
            wnd->show();
        }

        placeholderIcon_->hide();
        setMinimumSize(0,0);
        adjustSize();
    }
}

void MainWindow::save() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Monster File", "", "CombatAlly files (*.ca)");
    if (fileName != "") {
        QFile file(fileName);

        if (file.open(QFile::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            foreach (MonsterWidget* wdt, widgetList_)
                out << wdt->monster()->name() << "\t" << wdt->monster()->maxHP() << "\n";

            file.close();
        }
    }
}

void MainWindow::createActions() {
    addAct_ = new QAction("Add...", this);
    addAct_->setShortcut(Qt::CTRL + Qt::Key_N);
    addAct_->setStatusTip("Add a new monster");
    connect(addAct_, SIGNAL(triggered()), this, SLOT(createMonster()));

    loadAct_ = new QAction("Open...", this);
    loadAct_->setShortcut(Qt::CTRL + Qt::Key_O);
    loadAct_->setStatusTip("Load monsters from a file");
    connect(loadAct_, SIGNAL(triggered()), this, SLOT(load()));

    saveAct_ = new QAction("Save as...", this);
    saveAct_->setShortcut(Qt::CTRL + Qt::Key_S);
    saveAct_->setStatusTip("Save the current monsters into a file");
    connect(saveAct_, SIGNAL(triggered()), this, SLOT(save()));

    quitAct_ = new QAction("Quit", this);
    quitAct_->setShortcut(Qt::CTRL + Qt::Key_Q);
    quitAct_->setMenuRole(QAction::QuitRole);
    connect(quitAct_, SIGNAL(triggered()), this, SLOT(close()));

    removeAllAct_ = new QAction("Remove all", this);
    removeAllAct_->setShortcut(Qt::CTRL + Qt::Key_R);
    connect(removeAllAct_, SIGNAL(triggered()), this, SLOT(removeAll()));

    aboutAct_ = new QAction("About", this);
    aboutAct_->setMenuRole(QAction::AboutRole);
    connect(aboutAct_, SIGNAL(triggered()), this, SLOT(displayAbout()));

    preferencesAct_ = new QAction("Preferences", this);
    preferencesAct_->setShortcut(Qt::CTRL + Qt::Key_Comma);
    preferencesAct_->setStatusTip("Display the preferences");
    connect(preferencesAct_, SIGNAL(triggered()), this, SLOT(displayPreferences()));

    updateAct_ = new QAction("Check for updates...", this);
    updateAct_->setStatusTip("Check, if there are updates available");
    connect(updateAct_, SIGNAL(triggered()), this, SLOT(startUpdateTest()));
}

void MainWindow::createMenu() {
    menu_ = new QMenuBar();

    QMenu* file = menu_->addMenu("File");
    file->addAction(loadAct_);
    file->addAction(saveAct_);
    file->addAction(quitAct_);

    QMenu* monster = menu_->addMenu("Monster");
    monster->addAction(addAct_);
    monster->addAction(removeAllAct_);

    QMenu* help = menu_->addMenu("Help");
    help->addAction(preferencesAct_);
    help->addAction(updateAct_);
    help->addAction(aboutAct_);

#ifndef __APPLE__
    // On a Mac, the menubar isn't glued to a specific window but the app itself (in this case anyway)
    mainLayout_->setMenuBar(menu_);
#endif
}

void MainWindow::createShortcuts() {
    firstShortcut_ = new QShortcut(QKeySequence("CTRL+1"), this);
    connect(firstShortcut_, SIGNAL(activated()), this, SLOT(addConditionFromShortcut()));
    secondShortcut_ = new QShortcut(QKeySequence("CTRL+2"), this);
    connect(secondShortcut_, SIGNAL(activated()), this, SLOT(addConditionFromShortcut()));
    thirdShortcut_ = new QShortcut(QKeySequence("CTRL+3"), this);
    connect(thirdShortcut_, SIGNAL(activated()), this, SLOT(addConditionFromShortcut()));
    fourthShortcut_ = new QShortcut(QKeySequence("CTRL+4"), this);
    connect(fourthShortcut_, SIGNAL(activated()), this, SLOT(addConditionFromShortcut()));
    fifthShortcut_ = new QShortcut(QKeySequence("CTRL+5"), this);
    connect(fifthShortcut_, SIGNAL(activated()), this, SLOT(addConditionFromShortcut()));
    sixthShortcut_ = new QShortcut(QKeySequence("CTRL+6"), this);
    connect(sixthShortcut_, SIGNAL(activated()), this, SLOT(addConditionFromShortcut()));
    seventhShortcut_ = new QShortcut(QKeySequence("CTRL+7"), this);
    connect(seventhShortcut_, SIGNAL(activated()), this, SLOT(addConditionFromShortcut()));
    eighthShortcut_ = new QShortcut(QKeySequence("CTRL+8"), this);
    connect(eighthShortcut_, SIGNAL(activated()), this, SLOT(addConditionFromShortcut()));
    ninethShortcut_ = new QShortcut(QKeySequence("CTRL+9"), this);
    connect(ninethShortcut_, SIGNAL(activated()), this, SLOT(addConditionFromShortcut()));
    tenthShortcut_ = new QShortcut(QKeySequence("CTRL+0"), this);
    connect(tenthShortcut_, SIGNAL(activated()), this, SLOT(addConditionFromShortcut()));
}

void MainWindow::addConditionFromShortcut() {
    QShortcut* shortcut = dynamic_cast<QShortcut*>(QObject::sender());
    int index = -1;

    if (shortcut == firstShortcut_)
        index = 0;
    else if (shortcut == secondShortcut_)
        index = 1;
    else if (shortcut == thirdShortcut_)
        index = 2;
    else if (shortcut == fourthShortcut_)
        index = 3;
    else if (shortcut == fifthShortcut_)
        index = 4;
    else if (shortcut == sixthShortcut_)
        index = 5;
    else if (shortcut == seventhShortcut_)
        index = 6;
    else if (shortcut == eighthShortcut_)
        index = 7;
    else if (shortcut == ninethShortcut_)
        index = 8;
    else if (shortcut == tenthShortcut_)
        index = 9;

    if ((index != -1) && (index < widgetList_.count()))
        widgetList_.at(index)->addCondition();
}

void MainWindow::closeEvent(QCloseEvent*) {
    // Close the other windows of the application, because the app will run as long
    // as any window without a parent is opened
    aboutWidget_->close();
}

void MainWindow::startUpdateTest() {
    http_ = new QHttp("combatally.svn.sourceforge.net", 80, this);
    connect(http_, SIGNAL(done(bool)), this, SLOT(displayUpdate()));
    http_->get("/svnroot/combatally/VERSION");
}

void MainWindow::displayUpdate() {
    QMessageBox msg;
    msg.setWindowTitle("Software Update");
    msg.setWindowIcon(QIcon(":/images/swords.png"));

    if (http_->error() == QHttp::HostNotFound) {
        msg.setIcon(QMessageBox::Critical);
        msg.setText("Host not found");
        msg.setInformativeText("The connection to SourceForge could not be established. Please check your internet connect or try to reach \
                               \"combatally.svn.sourceforge.net/viewvc/combatally/VERSION\" in your web browser");
    }
    else {
        msg.setIcon(QMessageBox::Information);

        QString buffer = http_->readAll();

        if (buffer != QString(VERSION)) {
            msg.setText("New version of CombatAlly is available");
            msg.setInformativeText("Visit <html><body><a href=\"http://sourceforge.net/projects/combatally\">\
                                    http://sourceforge.net/projects/combatally</a></body></html> for updates");
        }
        else
            msg.setText("Your software is up to date");
    }
    msg.exec();
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();

}

void MainWindow::dropEvent(QDropEvent* event) {
    QList<QUrl> data = event->mimeData()->urls();

    for (int iter = 0 ; iter < data.count(); ++iter) {
        QFile file(data.at(iter).toLocalFile());
        load(file, false);        
    }
}
