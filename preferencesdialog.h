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

#ifndef __PREFERENCESWIDGET__
#define __PREFERENCESWIDGET__

#include <QDialog>

#include "settings.h"

class QCheckBox;
class QDialogButtonBox;
class QGridLayout;
class QGroupBox;
class QPushButton;
class QSpinBox;

/**
 * This widget displays the preferences window for CombatAlly in which a QSettings object is manipulated
 * Currently implemented functions:</br>
 * Should the conditions be entered manually or be chosen from a list?
 */
class PreferencesDialog : public QDialog {
Q_OBJECT
public:
    PreferencesDialog(QWidget* parent = 0, Qt::WindowFlags f = 0);

protected slots:
    virtual void accept();
    void deleteRecentConditions();
    void reset();

protected:
    void createWidgets();
    void createConnections();

    Settings settings_;

    QGridLayout* layout_;
    
    QGroupBox* generalBox_;
    QSpinBox* nameFontSizeSpin_;
    QSpinBox* hpFontSizeSpin_;

    QGroupBox* conditionsBox_;
    QSpinBox* maximumStoredSpinbox_;
    QPushButton* deleteRecentConditions_;
    QCheckBox* deleteRecentConditionsOnStartUpSpinBox_;

    QDialogButtonBox* buttonBox_;
    QPushButton* resetButton_;
};

#endif
