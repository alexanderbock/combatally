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

#ifndef __ADDMONSTERDIALOG__
#define __ADDMONSTERDIALOG__

#include <QDialog>

class QString;
class QLineEdit;
class QSpinBox;
class QDialogButtonBox;

/**
 * This widget displays a modal dialog for entering the name, the maximum
 * hitpoints and the count of the monsters which should be added.
 * On closing of the dialog these values are copied into the variables passed in the construtor
 */
class AddMonsterDialog : public QDialog {
Q_OBJECT
public:
    AddMonsterDialog(QString* name, int* maxHP, int* count, QWidget* parent = 0, Qt::WindowFlags f = 0);

protected slots:
    virtual void accept();

protected:
    QString* name_;
    int* maxHP_;
    int* count_;

    QLineEdit* nameEdit_;
    QSpinBox* hpSpinBox_;
    QSpinBox* countSpinBox_;

    QPushButton* okBtn_;
    QPushButton* cancelBtn_;

    QDialogButtonBox* buttonBox_;
};

#endif
