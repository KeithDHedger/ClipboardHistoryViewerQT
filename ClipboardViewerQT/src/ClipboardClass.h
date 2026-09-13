/*
 *
 * ©K. D. Hedger. Fri 11 Sep 11:38:51 BST 2026 keithdhedger@gmail.com

 * This file (ClipboardClass.h) is part of ClipboardViewerQT.

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

#ifndef _CLIPBOARDCLASS_
#define _CLIPBOARDCLASS_

#include "globals.h"


class ClipboardClass
{
	public:
		ClipboardClass();
		~ClipboardClass();

	private:
		QMainWindow		*mainWindow=NULL;
		QTextEdit		*te=NULL;
		QClipboard		*mainClip=NULL;
		QComboBox		*clips=NULL;
		int				imageCnt=1;
		int				clipcnt=0;
		Display			*display=NULL;

		void				buildMainGui(void);
		void				setWindowProps(Display *dsp,Window window,const char* grp,const char *type_name,int what);
		bool				tryForImage(QUrl path);
		QString			truncateString(const QString &input);

};

#endif
