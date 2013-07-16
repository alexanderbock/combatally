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

#include "preferencesdialog.h"

#include <QtGui>

PreferencesDialog::PreferencesDialog(QWidget* parent, Qt::WindowFlags f)
    : QDialog(parent,f)
{
#ifndef __APPLE__
    // On a Mac it looks bad with an icon, on Windows it looks bad without
    setWindowIcon(QIcon(":/images/swords.png"));
#endif

    resize(200,100);
    layout_ = new QGridLayout(this);
    layout_->setSizeConstraint(QLayout::SetFixedSize);

    createWidgets();
    createConnections();
}

void PreferencesDialog::createWidgets() {
    // General box
    generalBox_ = new QGroupBox("General settings");
    QVBoxLayout* generalLayout = new QVBoxLayout(generalBox_);

    QHBoxLayout* hpFontLayout = new QHBoxLayout;
    QLabel* hpFontLabel = new QLabel("Font size of Hitpoints");
    hpFontLayout->addWidget(hpFontLabel);
    hpFontSizeSpin_ = new QSpinBox;
    hpFontSizeSpin_->setValue(settings_.hpFontSize());
    hpFontSizeSpin_->setMinimum(0);
    hpFontSizeSpin_->setMaximum(100);
    hpFontLayout->addWidget(hpFontSizeSpin_);
    generalLayout->addLayout(hpFontLayout);

    QHBoxLayout* nameFontLayout = new QHBoxLayout;
    QLabel* nameFontLabel = new QLabel("Font size of monster name");
    nameFontLayout->addWidget(nameFontLabel);
    nameFontSizeSpin_ = new QSpinBox;
    nameFontSizeSpin_->setValue(settings_.nameFontSize());
    nameFontSizeSpin_->setMinimum(0);
    nameFontSizeSpin_->setMaximum(100);
    nameFontLayout->addWidget(nameFontSizeSpin_);
    generalLayout->addLayout(nameFontLayout);
    layout_->addWidget(generalBox_, 0, 0);

    // Conditions box
    conditionsBox_ = new QGroupBox("Condition settings");
    QVBoxLayout* conditionsLayout = new QVBoxLayout(conditionsBox_);

    QHBoxLayout* maximumStoredLayout = new QHBoxLayout;
    QLabel* maximumStoredLabel = new QLabel("Number of recently used conditions in store");
    maximumStoredLayout->addWidget(maximumStoredLabel);
    maximumStoredSpinbox_ = new QSpinBox;
    maximumStoredSpinbox_->setValue(settings_.conditionsMaximum());
    maximumStoredSpinbox_->setMinimum(0);
    maximumStoredSpinbox_->setMaximum(15);
    maximumStoredLayout->addWidget(maximumStoredSpinbox_);
    conditionsLayout->addLayout(maximumStoredLayout);

    deleteRecentConditionsOnStartUpSpinBox_ = new QCheckBox("Delete recently used conditions on startup");
    deleteRecentConditionsOnStartUpSpinBox_->setChecked(settings_.conditionsDeleteOnStartup());
    conditionsLayout->addWidget(deleteRecentConditionsOnStartUpSpinBox_);

    deleteRecentConditions_ = new QPushButton("Delete recently used conditions");
    conditionsLayout->addWidget(deleteRecentConditions_);
    layout_->addWidget(conditionsBox_, 0, 1);

    // Dialogbutton box
    buttonBox_ = new QDialogButtonBox();
    buttonBox_->setOrientation(Qt::Horizontal);
    buttonBox_->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    resetButton_ = new QPushButton("Restore Defaults");
    buttonBox_->addButton(resetButton_, QDialogButtonBox::ResetRole);
    layout_->addWidget(buttonBox_, 1, 1);
}

void PreferencesDialog::createConnections() {
    connect(deleteRecentConditions_, SIGNAL(clicked()), this, SLOT(deleteRecentConditions()));
    connect(buttonBox_, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox_, SIGNAL(rejected()), this, SLOT(reject()));
    connect(resetButton_, SIGNAL(clicked()), this, SLOT(reset()));
}

void PreferencesDialog::accept() {
    // Just write the values in the appropriate settings
    settings_.setNameFontSize(nameFontSizeSpin_->value());
    settings_.setHPFontSize(hpFontSizeSpin_->value());
    settings_.setConditionsMaximum(maximumStoredSpinbox_->value());
    settings_.setConditionsDeleteOnStartup(deleteRecentConditionsOnStartUpSpinBox_->isChecked());
    QDialog::accept();
}

void PreferencesDialog::reset() {
    settings_.setNameFontSize();
    settings_.setHPFontSize();
    settings_.setConditionsMaximum();
    settings_.setConditionsDeleteOnStartup();
    nameFontSizeSpin_->setValue(settings_.nameFontSize());
    hpFontSizeSpin_->setValue(settings_.hpFontSize());
    maximumStoredSpinbox_->setValue(settings_.conditionsMaximum());
    deleteRecentConditions_->setChecked(settings_.conditionsDeleteOnStartup());
}

void PreferencesDialog::deleteRecentConditions() {
    for (int iter = 0; iter < 15; ++iter)
        settings_.setValue("Conditions/Number" + QString::number(iter), "");
    settings_.setConditionsMostRecently(0);
}
