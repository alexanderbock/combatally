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

#include "addmonsterdialog.h"

#include <QtGui>

AddMonsterDialog::AddMonsterDialog(QString* name, int* maxHP, int* count, QWidget* parent, Qt::WindowFlags f) 
    : QDialog(parent,f)
    , name_(name)
    , maxHP_(maxHP)
    , count_(count)
{
    resize(265, 156);
    setWindowIcon(QIcon(":/images/swords.png"));

    QGridLayout* layout = new QGridLayout(this);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    QLabel* nameLabel = new QLabel("Name:");
    layout->addWidget(nameLabel, 0, 0);
    QLabel* hpLabel = new QLabel("MaxHP:");
    layout->addWidget(hpLabel, 1, 0);
    QLabel* countLabel = new QLabel("Count:");
    layout->addWidget(countLabel, 2, 0);

    nameEdit_ = new QLineEdit;
    layout->addWidget(nameEdit_, 0, 1);

    hpSpinBox_ = new QSpinBox;
    hpSpinBox_->setMinimum(1);
    hpSpinBox_->setMaximum(10000);
    layout->addWidget(hpSpinBox_, 1, 1);

    countSpinBox_ = new QSpinBox;
    countSpinBox_->setMinimum(1);
    layout->addWidget(countSpinBox_, 2, 1);

    buttonBox_ = new QDialogButtonBox;
    buttonBox_->setOrientation(Qt::Horizontal);
    buttonBox_->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    connect(buttonBox_, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox_, SIGNAL(rejected()), this, SLOT(reject()));
    layout->addWidget(buttonBox_, 3, 1);
}

void AddMonsterDialog::accept() {
    *name_ = nameEdit_->text();
    *maxHP_ = hpSpinBox_->value();
    *count_ = countSpinBox_->value();

    QDialog::accept();
}
