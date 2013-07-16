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

#ifndef __ADDCONDITIONDIALOG__
#define __ADDCONDITIONDIALOG__

#include <QDialog>

#include "settings.h"

class QDialogButtonBox;
class QCheckBox;
class QGroupBox;
class QFrame;
class QLabel;
class QLineEdit;
class QGridLayout;
class QRadioButton;
class QAbstractButton;
class QSpinBox;
class QString;

/**
 * A modal dialog for choosing conditions instead of entering them manually
 */

class AddConditionDialog : public QDialog {
Q_OBJECT
public:
    AddConditionDialog(QString* line, QWidget* parent = 0, Qt::WindowFlags f = 0);

protected slots:
    virtual void accept();
    void acceptedFromRecentButton();
    void acceptedFromActionPointButton();

protected:
    void createWidgets();
    void createConnections();
    QString generateConditionText(QAbstractButton* btn, QString condition, bool* firstEntry);
    QString* generateStringOutput();

    QString* line_;

    QGridLayout* layout_;
    QDialogButtonBox* buttonBox_;
    QPushButton* actionPoint_;

    QGroupBox* recentlyButtons_;

    QGroupBox* ongoingBox_;
    QRadioButton* ongoing5_;
    QRadioButton* ongoing10_;
    QRadioButton* ongoing15_;
    QRadioButton* ongoing20_;
    QRadioButton* ongoingX_;
    QLineEdit* ongoingXEdit_;

    QGroupBox* conditionBox_;
    QCheckBox* blinded_;
    QCheckBox* dazed_;
    QCheckBox* deafened_;
    QCheckBox* dominated_;
    QCheckBox* helpless_;
    QCheckBox* immobilized_;
    QCheckBox* petrified_;
    QCheckBox* restrained_;
    QCheckBox* slowed_;
    QCheckBox* stunned_;
    QCheckBox* unconcious_;
    QCheckBox* weakened_;

    QGroupBox* damageBox_;
    QCheckBox* acid_;
    QCheckBox* cold_;
    QCheckBox* fire_;
    QCheckBox* lightning_;
    QCheckBox* necrotic_;
    QCheckBox* poison_;
    QCheckBox* psychic_;
    QCheckBox* radiant_;
    QCheckBox* thunder_;

    QGroupBox* endingBox_;
    QRadioButton* eot_;
    QLineEdit* eotEdit_;
    QRadioButton* saveends_;
    QRadioButton* bot_;
    QLineEdit* botEdit_;
    QLabel* penaltyLabel_;
    QSpinBox* penaltySpin_;

    QLabel* otherLabel_;
    QLineEdit* otherEdit_;

    Settings settings_;
};

#endif
