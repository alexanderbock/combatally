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

#include "aboutwidget.h"
#include "version.h"

#include <QtGui>

AboutWidget::AboutWidget(QWidget* parent, Qt::WindowFlags f)
    : QWidget(parent,f)
{
#ifndef __APPLE__
    // On a Mac it looks bad with a icon, on Windows it looks bad without
    setWindowIcon(QIcon(":/images/swords.png"));
#endif

    move(0,20);
    QGridLayout* layout = new QGridLayout(this);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    QLabel* icon = new QLabel();
    icon->setPixmap(QPixmap(":/images/swords.png"));
    layout->addWidget(icon, 0, 1);

    layout->addWidget( new QLabel("Version: " VERSION) , 1, 0, 1, 3);
    layout->addWidget( new QLabel("Developer: Alexander Bock") , 2, 0, 1, 3);
    layout->addWidget( new QLabel("<html><body>Contact: <a href=\"mailto:hijinxs@web.de\"> hijinxs@web.de</a></body></html>") , 3, 0, 1, 3);
    layout->addWidget( new QLabel("Feel free to mail any comments, feature requests or improvements") , 4, 0, 1, 3);
}
