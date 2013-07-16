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

#include "monsterwidget.h"
#include "addconditiondialog.h"
#include "monster.h"

#include <QtGui>

MonsterWidget::MonsterWidget(Monster* monster, QWidget* parent, Qt::WindowFlags f)
    : QWidget(parent,f)
    , monster_(monster)
{
    layout_ = new QHBoxLayout(this);

    monsterName_ = new QLabel(monster->name());
    monsterName_ ->setFont(QFont("Helvetica", settings_.nameFontSize()));
    layout_->addWidget(monsterName_);

    // Make the name left-aligned
    layout_->addStretch();

    currentHitpointsLabel_ = new QLabel(QString::number(monster->maxHP()));
    currentHitpointsLabel_->setFont(QFont("Helvetica", settings_.hpFontSize(), QFont::Bold));
    layout_->addWidget(currentHitpointsLabel_);

    damageEdit_ = new QLineEdit;
    damageEdit_->setValidator(new QIntValidator(this));
    damageEdit_->setMinimumSize(40,20);
    damageEdit_->setMaximumSize(40,20);
    connect(damageEdit_, SIGNAL(returnPressed()), this, SLOT(updateHitpointsWithValueFromDamage()));
    layout_->addWidget(damageEdit_);

    removeMonsterButton_ = new QPushButton;
    removeMonsterButton_->setIcon(QIcon(":/images/close.png"));
    connect(removeMonsterButton_, SIGNAL(clicked()), parent, SLOT(removeMonster()));
    layout_->addWidget(removeMonsterButton_);

    addConditionButton_ = new QPushButton;
    addConditionButton_->setIcon(QIcon(":/images/add.png"));
    connect(addConditionButton_, SIGNAL(clicked()), this, SLOT(addCondition()));
    layout_->addWidget(addConditionButton_);
}

MonsterWidget::~MonsterWidget() {
    delete monster_;
}

void MonsterWidget::updateHitpointsWithValueFromDamage() {
    // Update the current hitpoints
    monster_->changeHP(- damageEdit_->text().toInt());

    // Test, if the changed hitpoints are above the maximum and display a dialog, if they are
    if (monster_->isAboveMaxHP()) {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("Monster has more than its full hitpoints");
        msg.setText("Hitpoints are above the maximum hitpoints");
        msg.setInformativeText("With this change, the monster would be above hits maximum hitpoints. \
Do you want to continue or cap the value to the maximum hitpoints?");
        msg.addButton("Use the value", QMessageBox::NoRole);
        msg.addButton("Cap to maximum", QMessageBox::YesRole);
        // QMessageBox::Accepted <=> YesRole was clicked
        if (msg.exec() == QMessageBox::Accepted)
            monster_->setHPToMaximum();
    }

    // Update the label and reset the damage edit field
    currentHitpointsLabel_->setNum(monster_->hp());
    damageEdit_->setText("");

    // Change the color of the hitpoints label to red if bloodied, to green if dead
    // The order is important, because you are also bloodied while dead
    if (monster_->isDead()) {
        QPalette palette;
        palette.setColor(QPalette::WindowText, QColor(0,128,0));
        currentHitpointsLabel_->setPalette(palette);
    } else if (monster_->isBloodied()) {
        QPalette palette;
        palette.setColor(QPalette::WindowText, QColor(255,0,0));
        currentHitpointsLabel_->setPalette(palette);
    } else {
        QPalette palette;
        palette.setColor(QPalette::WindowText, QColor(0,0,0));
        currentHitpointsLabel_->setPalette(palette);
    }
}

void MonsterWidget::addCondition() {
    QString condition;

    AddConditionDialog(&condition).exec();

    if (!condition.isEmpty()) {
        QPushButton* newButton = new QPushButton();

        // if there is save ends in the text, display the buttontext in red
        if (condition.contains("(save ends", Qt::CaseInsensitive)) {
                QPalette palette;
                palette.setColor(QPalette::ButtonText, QColor(255,50,50));
                newButton->setPalette(palette);
        }
        newButton->setText(condition);
        connect(newButton, SIGNAL(clicked()), this, SLOT(removeCondition()));
        layout_->addWidget(newButton);
    }
}

void MonsterWidget::removeCondition() {
    QPushButton* btn = dynamic_cast<QPushButton*>(QObject::sender());
    layout_->removeWidget(btn);
    disconnect(btn, SIGNAL(clicked()), this, SLOT(removeCondition()));
    btn->setVisible(false);

    // Set everything back to the minimal size
    setMinimumSize(0,0);
    adjustSize();
    parentWidget()->setMinimumSize(0,0);
    parentWidget()->adjustSize();
}

void MonsterWidget::disconnectButton() {
    disconnect(removeMonsterButton_, SIGNAL(clicked()), parent(), SLOT(removeMonster()));
}
