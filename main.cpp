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

#include "mainwindow.h"
#include "version.h"
#include <QApplication>
#include <QFile>

#ifdef __APPLE__
// Enable the mnemonics used in the addcondition dialog (only necessary on Mac)
extern void qt_set_sequence_auto_mnemonic(bool b);
#endif

int main(int argc, char** argv) {
#ifdef __APPLE__
    qt_set_sequence_auto_mnemonic(true);
#endif
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("Bock");
    QCoreApplication::setApplicationName("CombatAlly");
    QCoreApplication::setApplicationVersion(VERSION);

    MainWindow wnd;
    for (int i = 1 ; i < argc ; ++i) {
        QFile file(argv[i]);
        wnd.load(file, false);        
    }

    wnd.show();

    return app.exec();
}
