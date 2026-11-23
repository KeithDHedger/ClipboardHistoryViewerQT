/*
 *
 * ©K. D. Hedger. Fri 11 Sep 11:26:33 BST 2026 keithdhedger@gmail.com

 * This file (main.cpp) is part of ClipboardViewerQT.

 * ClipboardViewerQT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * ClipboardViewerQT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with ClipboardViewerQT.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "globals.h"

int main(int argv, char **args)
{
	QApplication		app(argv, args);
	ClipboardClass	cc;
	int				retval;

	QIcon::setThemeSearchPaths(QStringList()<<QString("%1/icons").arg(DATADIR)<<QString("/usr/share/icons")<<QString("%1/.icons").arg(getenv("HOME")));
	QIcon::setFallbackSearchPaths(QStringList()<<QString("%1/icons").arg(DATADIR)<<QString("/usr/share/icons")<<QString("%1/.icons").arg(getenv("HOME")));
	QIcon::setFallbackThemeName("clipicons");

	app.setApplicationName(PACKAGE_NAME);
	app.setApplicationVersion(PACKAGE_VERSION);

	retval=app.exec();
	prefsClass::cleanTemp(PACKAGE_NAME);

	return(retval);
}