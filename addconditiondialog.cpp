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

#include <QtGui>

AddConditionDialog::AddConditionDialog(QString* line, QWidget* parent, Qt::WindowFlags f)
    : QDialog(parent,f)
    , line_(line)
{
    layout_ = new QGridLayout(this);
    layout_->setColumnStretch(0, 10);
    layout_->setColumnStretch(1, 10);
    setWindowIcon(QIcon(":/images/swords.png"));
    createWidgets();
    createConnections();
    layout_->setSizeConstraint(QLayout::SetFixedSize);
}

void AddConditionDialog::createWidgets() {    
    ongoingBox_ = new QGroupBox("Ongoing");
        QVBoxLayout* ongoingBoxLayout = new QVBoxLayout;
        ongoing5_ = new QRadioButton("&Ongoing 5");
        ongoingBoxLayout->addWidget(ongoing5_);
        ongoing10_ = new QRadioButton("Ongoing 10");
        ongoingBoxLayout->addWidget(ongoing10_);
        ongoing15_ = new QRadioButton("Ongoing 15");
        ongoingBoxLayout->addWidget(ongoing15_);
        ongoing20_ = new QRadioButton("Ongoing 20");
        ongoingBoxLayout->addWidget(ongoing20_);
        ongoingX_ = new QRadioButton("other value");
        ongoingBoxLayout->addWidget(ongoingX_);
        ongoingXEdit_ = new QLineEdit();
        ongoingBoxLayout->addWidget(ongoingXEdit_);
    ongoingBox_->setLayout(ongoingBoxLayout);
    layout_->addWidget(ongoingBox_, 0, 0);

    conditionBox_ = new QGroupBox("Conditions");
        QVBoxLayout* conditionBoxLayout = new QVBoxLayout;
        blinded_ = new QCheckBox("Blinded");
        conditionBoxLayout->addWidget(blinded_);
        dazed_ = new QCheckBox("&Dazed");
        conditionBoxLayout->addWidget(dazed_);
        deafened_ = new QCheckBox("Deafened");
        conditionBoxLayout->addWidget(deafened_);
        dominated_ = new QCheckBox("Dominated");
        conditionBoxLayout->addWidget(dominated_);
        helpless_ = new QCheckBox("Helpless");
        conditionBoxLayout->addWidget(helpless_);
        immobilized_ = new QCheckBox("Immobilized");
        conditionBoxLayout->addWidget(immobilized_);
        petrified_ = new QCheckBox("Petrified");
        conditionBoxLayout->addWidget(petrified_);
        restrained_ = new QCheckBox("Restrained");
        conditionBoxLayout->addWidget(restrained_);
        slowed_ = new QCheckBox("Slowed");
        conditionBoxLayout->addWidget(slowed_);
        stunned_ = new QCheckBox("Stunned");
        conditionBoxLayout->addWidget(stunned_);
        unconcious_ = new QCheckBox("Unconcious");
        conditionBoxLayout->addWidget(unconcious_);
        weakened_ = new QCheckBox("&Weakened");
        conditionBoxLayout->addWidget(weakened_);
    conditionBox_->setLayout(conditionBoxLayout);
    layout_->addWidget(conditionBox_, 1, 0, 3, 1);

    damageBox_ = new QGroupBox("Damage types");
        QVBoxLayout* damageBoxLayout = new QVBoxLayout;
        acid_ = new QCheckBox("Acid");
        damageBoxLayout->addWidget(acid_);
        cold_ = new QCheckBox("Cold");
        damageBoxLayout->addWidget(cold_);
        fire_ = new QCheckBox("Fire");
        damageBoxLayout->addWidget(fire_);
        lightning_ = new QCheckBox("Lightning");
        damageBoxLayout->addWidget(lightning_);
        necrotic_ = new QCheckBox("Necrotic");
        damageBoxLayout->addWidget(necrotic_);
        poison_ = new QCheckBox("Poison");
        damageBoxLayout->addWidget(poison_);
        psychic_ = new QCheckBox("Psychic");
        damageBoxLayout->addWidget(psychic_);
        radiant_ = new QCheckBox("Radiant");
        damageBoxLayout->addWidget(radiant_);
        thunder_ = new QCheckBox("Thunder");
        damageBoxLayout->addWidget(thunder_);
    damageBox_->setLayout(damageBoxLayout);
    layout_->addWidget(damageBox_, 0, 1, 1, 2);

    endingBox_ = new QGroupBox("End triggers");
        QVBoxLayout* endingBoxLayout = new QVBoxLayout;
        eot_ = new QRadioButton("&End of turn:");
        endingBoxLayout->addWidget(eot_);
        eotEdit_ = new QLineEdit();
        eotEdit_->setMinimumSize(0, 22);
        endingBoxLayout->addWidget(eotEdit_);
        bot_ = new QRadioButton("&Begin of Turn:");
        endingBoxLayout->addWidget(bot_);
        botEdit_ = new QLineEdit();
        botEdit_->setMinimumSize(0, 22);
        endingBoxLayout->addWidget(botEdit_);
        endingBoxLayout->addSpacing(100);
        saveends_ = new QRadioButton("&Save Ends");
        endingBoxLayout->addWidget(saveends_);
        QHBoxLayout* penaltyLayout = new QHBoxLayout;
        penaltyLabel_ = new QLabel("Penalty:");
        penaltyLayout->addWidget(penaltyLabel_);
        penaltySpin_ = new QSpinBox;
        penaltySpin_->setMinimumSize(0, 22);
        penaltyLayout->addWidget(penaltySpin_);
        endingBoxLayout->addLayout(penaltyLayout);
    endingBox_->setLayout(endingBoxLayout);
    layout_->addWidget(endingBox_, 1, 1, 1 ,2);

    otherLabel_ = new QLabel("Other Condition:");
    layout_->addWidget(otherLabel_, 2, 1);
    otherEdit_ = new QLineEdit;
    layout_->addWidget(otherEdit_, 2, 2);

    // Only display this groupbox if the maximum number is greater zero
    if (settings_.conditionsMaximum() > 0) {
        recentlyButtons_ = new QGroupBox("Recently used conditions");
        QVBoxLayout* recentlyLayout = new QVBoxLayout(recentlyButtons_);
        int maximumRecent = settings_.conditionsMaximum();
        for (int iter = 0; iter < maximumRecent; ++iter) {
            QString buttonText = settings_.value("Conditions/Number"+QString::number(iter)).toString();
            QPushButton* button = new QPushButton(buttonText);
            recentlyLayout->addWidget(button);

            if (buttonText != QString(""))
                connect(button, SIGNAL(clicked()), this, SLOT(acceptedFromRecentButton()));
        }
        layout_->addWidget(recentlyButtons_, 0, 3, 4, 1);
    }

    actionPoint_ = new QPushButton("&Actionpoint");
    connect(actionPoint_, SIGNAL(clicked()), this, SLOT(acceptedFromActionPointButton()));

    buttonBox_ = new QDialogButtonBox();
    buttonBox_->setOrientation(Qt::Horizontal);
    buttonBox_->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    buttonBox_->addButton(actionPoint_, QDialogButtonBox::ActionRole);
    layout_->addWidget(buttonBox_, 4, 2, 1, 2);    
}

void AddConditionDialog::createConnections() {
    connect(ongoingXEdit_, SIGNAL(textEdited(QString)), ongoingX_, SLOT(click()));
    connect(eotEdit_, SIGNAL(textEdited(QString)), eot_, SLOT(click()));
    connect(botEdit_, SIGNAL(textEdited(QString)), bot_, SLOT(click()));
    connect(penaltySpin_, SIGNAL(valueChanged(int)), saveends_, SLOT(click()));
    connect(buttonBox_, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox_, SIGNAL(rejected()), this, SLOT(reject()));

    // One additional connect in 'createWidgets'
}

void AddConditionDialog::accept() {
    QString* result = generateStringOutput();
    *line_ = *result;

    // Save the currently added button to the recently used if we use any and only if something is entered in the "other" field
    if ((settings_.conditionsMaximum() != 0) && (otherEdit_->text() != "")) {
        int mostRecentlyAdded = settings_.conditionsMostRecently();
        settings_.setValue("Conditions/Number" + QString::number(mostRecentlyAdded), *result);
        int maximumRecent = settings_.conditionsMaximum();
        settings_.setConditionsMostRecently((mostRecentlyAdded+1)%maximumRecent);
    }
    delete result;
    QDialog::accept();
}

void AddConditionDialog::acceptedFromRecentButton() {
    QPushButton* btn = static_cast<QPushButton*>(QObject::sender());
    *line_ = btn->text();
    QDialog::accept();
}

void AddConditionDialog::acceptedFromActionPointButton() {
    *line_ = "action point";
    QDialog::accept();
}

QString AddConditionDialog::generateConditionText(QAbstractButton* btn, QString condition, bool* firstEntry) {
    QString result = "";
    if (btn->isChecked()) {
        if (! *firstEntry )
            result.append("and ");

        result.append(condition + " ");
        *firstEntry = false;
    }
    return result;
}

QString* AddConditionDialog::generateStringOutput() {
    QString* result = new QString;

    // Ongoing damage
    if (ongoing5_->isChecked())
        result->append("Ongoing 5");
    else if (ongoing10_->isChecked())
        result->append("Ongoing 10");
    else if (ongoing15_->isChecked())
        result->append("Ongoing 15");
    else if (ongoing20_->isChecked())
        result->append("Ongoing 20");
    else if (ongoingX_->isChecked())
        result->append("Ongoing " + ongoingXEdit_->text());

    if (result != QString(""))
        result->append(" ");

    bool firstEntry = true;
    // Damage type
    result->append(generateConditionText(acid_, "acid", &firstEntry));
    result->append(generateConditionText(cold_, "cold", &firstEntry));
    result->append(generateConditionText(fire_, "fire", &firstEntry));
    result->append(generateConditionText(lightning_, "lightning", &firstEntry));
    result->append(generateConditionText(necrotic_, "necrotic", &firstEntry));
    result->append(generateConditionText(poison_, "poison", &firstEntry));
    result->append(generateConditionText(psychic_, "psychic", &firstEntry));
    result->append(generateConditionText(radiant_, "radiant", &firstEntry));
    result->append(generateConditionText(thunder_, "thunder", &firstEntry));

    // Classic conditions
    result->append(generateConditionText(blinded_, "blinded", &firstEntry));
    result->append(generateConditionText(dazed_, "dazed", &firstEntry));
    result->append(generateConditionText(deafened_, "deafened", &firstEntry));
    result->append(generateConditionText(dominated_, "dominated", &firstEntry));
    result->append(generateConditionText(helpless_, "helpless", &firstEntry));
    result->append(generateConditionText(immobilized_, "immobilized", &firstEntry));
    result->append(generateConditionText(petrified_, "petrified", &firstEntry));
    result->append(generateConditionText(restrained_, "restrained", &firstEntry));
    result->append(generateConditionText(slowed_, "slowed", &firstEntry));
    result->append(generateConditionText(stunned_, "stunned", &firstEntry));
    result->append(generateConditionText(unconcious_, "unconcious", &firstEntry));
    result->append(generateConditionText(weakened_, "weakened", &firstEntry));

    // End triggers
    if (eot_->isChecked())
        result->append("(End of Turn: " + eotEdit_->text() + ")");

    if (saveends_->isChecked()) {
        if (penaltySpin_->value()== 0)
            result->append("(save ends)");
        else
            result->append("(save ends -" + QString::number(penaltySpin_->value()) + " penalty)");
    }

    if (bot_->isChecked()) 
        result->append("(Begin of Turn: " + botEdit_->text() + ")");

    if (otherEdit_->text() != "") {
        if (result != QString(""))
            result->append("  ");

        result->append(otherEdit_->text());
    }

    return result;
}
