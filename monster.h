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

#ifndef __MONSTER__
#define __MONSTER__

#include <QString>

/**
 * This class represents a single monster used by the GUI. It has a list of the conditions
 * it currently has and manages them (i.e. deletes them when the monster is deleted).
 * \sa Condition
 */
class Monster {
public:
    /**
     * Straightforward ctor.
     * \param name The name of the monster
     * \param maxHP The maximum hitpoints of the monster
     */
    Monster(QString name, int maxHP);

    QString name();
    void setName(QString name);

    int maxHP();
    void setMaxHP(int maxHP);

    int hp();
    void setHP(int hp);

    /**
     * Relative setter for the current hitpoints. The value will be added to the
     * current hitpoints.
     * \param deltaHP The change for the current hitpoints
     */
    void changeHP(int deltaHP);
    
    void setHPToMaximum();

    bool isBloodied();
    bool isDead();
    
    bool isAboveMaxHP();

protected:
    QString name_;

    int maxHP_;
    int hp_;
};

#endif