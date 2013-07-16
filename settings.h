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

#include <QSettings>

#ifndef __SETTINGS__
#define __SETTINGS__

class Settings : public QSettings {
public:
    int hpFontSize() { return value("General/HPFontSize", 36).toInt(); }
    void setHPFontSize(int value = 36) { setValue("General/HPFontSize", value); }

    int nameFontSize() { return value("General/NameFontSize", 20).toInt(); }
    void setNameFontSize(int value = 20) { setValue("General/NameFontSize", value); }

    int conditionsMaximum() { return value("Conditions/Maximum", 15).toInt(); }
    void setConditionsMaximum(int value = 15) { setValue("Conditions/Maximum", value); }

    bool conditionsDeleteOnStartup() { return value("Conditions/DeleteOnStartup", true).toBool(); }
    void setConditionsDeleteOnStartup(bool value = true) { setValue("Conditions/DeleteOnStartup", value); }

    int conditionsMostRecently() { return value("Conditions/MostRecently", 0).toInt(); }
    void setConditionsMostRecently(int value = 0) { setValue("Conditions/MostRecently", value); }
};

#endif
