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

#ifndef __MONSTERWIDGET__
#define __MONSTERWIDGET__

#include <QWidget>

#include "settings.h"

class Monster;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class MonsterWidget : public QWidget {
Q_OBJECT
public:
    MonsterWidget(Monster* monster, QWidget* parent = 0, Qt::WindowFlags f = 0);
    ~MonsterWidget();

    void disconnectButton();

    Monster* monster() { return monster_; }

public slots:
    void updateHitpointsWithValueFromDamage();
    void addCondition();
    void removeCondition();

protected:
    Monster* monster_;

    QHBoxLayout* layout_;
    QLabel* monsterName_;
    QLabel* currentHitpointsLabel_;
    QLineEdit* damageEdit_;
    QPushButton* removeMonsterButton_;
    QPushButton* addConditionButton_;

    Settings settings_;
};

#endif
