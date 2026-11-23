/*
 *
 * ©K. D. Hedger. Fri 11 Sep 11:38:51 BST 2026 keithdhedger@gmail.com

 * This file (ClipboardClass.cpp) is part of ClipboardViewerQT.

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

#include "ClipboardClass.h"

ClipboardClass::~ClipboardClass()
{
	QStringList	sl;
	QSettings	settings("KDHedger",PACKAGE_NAME);

	settings.setValue("geometry",mainWindow->saveGeometry());

	if(this->save==true)
		{
			for(int j=0;j<this->clips->count();j++)
				{
					if(this->clips->itemData(j).toString().isEmpty()==false)
						sl<<this->clips->itemData(j).toString();
				}
		}
	settings.setValue("savestrings",sl);

	delete this->mainWindow;
	XCloseDisplay(this->display);
}

QString ClipboardClass::truncateString(const QString &input)
{
	int		frontLength;
	int		backLength;
	QString	front;
	QString	back ;

 	if(input.length() <= MAXCLIPMENULEN)
		return(input);
 
	frontLength=MAXCLIPMENULEN/2;
	backLength=MAXCLIPMENULEN-frontLength-1;

	front=input.left(frontLength);
	back=input.right(backLength);

    return(front+"…"+back);
}

bool ClipboardClass::tryForImage(QUrl path)
{
	QByteArray	imageFormat;
	QImage		image;
	QImageReader	reader;
	QString		finalpath;
	QString		imagename;
	QTextCursor	cursor;
	int			index;

	if(path.isLocalFile()==true)
		finalpath=path.toLocalFile();
	else
		finalpath=path.toString();

	imageFormat=QImageReader::imageFormat(finalpath);
	reader.setFileName(finalpath);
	reader.setAutoDetectImageFormat(true);
	image=reader.read();
	if(image.isNull()==false)
		{
			index=this->clips->findData(image);
			if(index!=-1)
				return(true);

			this->clips->addItem(this->truncateString(path.toString().simplified()),path);
			imagename=QFileInfo(path.toString().simplified()).fileName();
			cursor=this->te->textCursor();

			this->te->clear();
			cursor.insertImage(image);
			this->te->setTextCursor(cursor);
			this->clips->addItem(imagename,image);
			this->clips->setCurrentIndex(this->clips->count()-1);
			return(true);
		}
	return(false);
}

ClipboardClass::ClipboardClass()
{
	prefsClass	newprefs(PACKAGE_NAME);

	this->display=XOpenDisplay(NULL);
	if(this->display==NULL)
		{
			fprintf(stderr,"Can't open display exiting ...");
			exit(1);
		}

	this->sticky=newprefs.getSavedPrefValue("prefs/Sticky").toBool();
	this->ontop=newprefs.getSavedPrefValue("prefs/On Top").toBool();
	this->save=newprefs.getSavedPrefValue("prefs/Save History").toBool();
	this->maxClips=newprefs.getSavedPrefValue("prefs/Max Clips").toInt();

	this->mainClip=qApp->clipboard();
	QObject::connect(this->mainClip,&QClipboard::dataChanged,[this]()
		{
			if(this->mainClip->mimeData()->hasUrls()==true)
				{
					for(const QUrl &url : this->mainClip->mimeData()->urls())
						{
							if(this->tryForImage(url)==false)
								{
									QString uri=url.toString();
									int index;
									index=this->clips->findData(uri);
									if(index==-1)
										{
											this->clips->addItem(this->truncateString(uri.simplified()),uri);
											this->te->setPlainText(uri);
											this->clips->setCurrentIndex(this->clips->count()-1);
										}
								}
						}
					while(this->clips->count()>this->maxClips)
						this->clips->removeItem(0);
					return;			
				}
			else if(this->mainClip->mimeData()->hasText())
				{
					if(this->tryForImage(QUrl(this->mainClip->text()))==true)
						{

							while(this->clips->count()>this->maxClips)
								this->clips->removeItem(0);
							return;
						}
					else
						{
							int index;
							index=this->clips->findData(this->mainClip->text());
							if(index==-1)
								{
									this->clips->addItem(this->truncateString(this->mainClip->text().simplified()),this->mainClip->text());
									this->te->setPlainText(this->mainClip->text());
									this->clips->setCurrentIndex(this->clips->count()-1);
								}
						}
				}
			else if(this->mainClip->mimeData()->hasImage())
				{
					const QImage image=QApplication::clipboard()->image();
					QString imagename=QString("Image-%1").arg(imageCnt++);
					QTextCursor cursor=this->te->textCursor();
					this->te->clear();
					cursor.insertImage(image);
					this->te->setTextCursor(cursor);
					this->clips->addItem(imagename,this->mainClip->image());
					this->clips->setCurrentIndex(this->clips->count()-1);
				}

			while(this->clips->count()>this->maxClips)
				this->clips->removeItem(0);
		});			
	this->buildMainGui();
}

void ClipboardClass::buildMainGui(void)
{
 	QSettings	settings("KDHedger",PACKAGE_NAME);
	QWidget		*centre=NULL;
	QVBoxLayout	*vbox=NULL;
	QHBoxLayout	*hlayout;
	QWidget		*hbox=NULL;
	QPushButton	*about=NULL;
	QPushButton	*sticky=NULL;
	QPushButton	*quit=NULL;
	QPushButton	*clearall=NULL;
	QPushButton	*clear=NULL;
	QPushButton	*prefs=NULL;
	prefsClass	newprefs(PACKAGE_NAME);

//	this->sticky=newprefs.getSavedPrefValue("prefs/Sticky").toBool();
//	this->ontop=newprefs.getSavedPrefValue("prefs/On Top").toBool();
//	this->save=newprefs.getSavedPrefValue("prefs/Save History").toBool();
//	this->maxClips=newprefs.getSavedPrefValue("prefs/prefs/Max Clips").toInt();

	this->mainWindow=new QMainWindow;
	this->mainWindow->setWindowTitle("Clipboard Viewer QT");
	centre=new QWidget(this->mainWindow);
	vbox=new QVBoxLayout(centre);
	vbox->setContentsMargins(0,0,0,0);

	this->te=new QTextEdit(this->mainWindow);
	this->te->setReadOnly(true);
	vbox->addWidget(this->te);

	hbox=new QWidget(this->mainWindow);
	hlayout=new QHBoxLayout(hbox);
	hbox->setLayout(hlayout);

	clear=new QPushButton(QIcon::fromTheme("edit-clear"),"Clear",this->mainWindow);
	clearall=new QPushButton(QIcon::fromTheme("edit-clear"),"Clear All",this->mainWindow);
	clear->setEnabled(false);
	clearall->setEnabled(false);

	this->clips=new QComboBox(this->mainWindow);
	this->clips->setMinimumContentsLength(1);
	if(this->save==true)
		{
			QStringList sl=settings.value("savestrings").toStringList();
			if(sl.size()>0)
				{
					clear->setEnabled(true);
					clearall->setEnabled(true);
				}
			for(const QString &str:sl)
				this->mainClip->setText(str);

			while(this->clips->count()>this->maxClips)
				this->clips->removeItem(0);
		}

	QObject::connect(this->clips,&QComboBox::activated,[this,clear,clearall](int index)
		{
			QImage		image=this->clips->itemData(index).value<QImage>();
			QTextCursor	cursor;
			this->mainClip->blockSignals(true);
				if(image.isNull()==false)
					{
						cursor=this->te->textCursor();
						this->te->clear();
						cursor.insertImage(image);
						this->te->setTextCursor(cursor);
						this->mainClip->setImage(image);
					}
				else
					{
						this->te->setPlainText(this->clips->itemData(index).toString());
						this->mainClip->setText(this->clips->itemData(index).toString());
					}

			if(this->clips->count()==0)
				{
					clear->setEnabled(false);
					clearall->setEnabled(false);
				}
			this->mainClip->blockSignals(false);
		});

	QObject::connect(this->clips,&QComboBox::currentIndexChanged,[this,clear,clearall](int index)
		{
			if(this->clips->count()>0)
				{
					clear->setEnabled(true);
					clearall->setEnabled(true);
				}
		});
	hlayout->addWidget(clips,1);

	setWindowProps(this->display,this->mainWindow->winId(),"_NET_WM_STATE","_NET_WM_STATE_STICKY",PropModeReplace);
	QObject::connect(clear,&QPushButton::clicked,[this](bool checked)
		{
			int hold=this->clips->currentIndex();
			this->clips->removeItem(this->clips->currentIndex());

			if(hold>=this->clips->count())
				emit this->clips->activated(this->clips->count()-1);
			else
				emit this->clips->activated(hold);
		});
	hlayout->addWidget(clear);

	QObject::connect(clearall,&QPushButton::clicked,[this,clear,clearall](bool checked)
		{
			this->clips->clear();
			this->te->clear();
			clear->setEnabled(false);
			clearall->setEnabled(false);
		});
	hlayout->addWidget(clearall);

	prefs=new QPushButton(QIcon::fromTheme("preferences-desktop-theme"),"Prefs",this->mainWindow);
	QObject::connect(prefs,&QPushButton::clicked,[this](bool checked)
		{
			this->doPrefs();
		});
	hlayout->addWidget(prefs);

	about=new QPushButton(QIcon::fromTheme("help-about"),"About",this->mainWindow);
	QObject::connect(about,&QPushButton::clicked,[this]()
		{
			QString			pixpath=QString("%1/pixmaps/ClipboardHistoryViewerQT.png").arg(DATADIR);
			AboutBoxClass	about(nullptr,pixpath);
			QFile			file(QString("%1/docs/gpl-3.0.txt").arg(DATADIR));
			if(file.open(QIODevice::ReadOnly | QIODevice::Text))
				{
					QTextStream in(&file);
					about.licence=in.readAll();
					file.close();
				}
			about.credits=credits;
			about.setHomepage("https://github.com/KeithDHedger/ClipboardHistoryViewerQT","Clipboard History Viewer QT");
			about.setBodyText("Text and image clipboard viewer");
			about.showAboutQtButton();
			about.showLicenceButton();
			about.showCreditsButton();
			about.showHelpButton(QString("%1/docs/help/help.html").arg(DATADIR));
			about.runAbout();
		});
	hlayout->addWidget(about);

	quit=new QPushButton(QIcon::fromTheme("application-exit"),"Quit",this->mainWindow);
	QObject::connect(quit,&QPushButton::clicked,[]()
		{
			qApp->exit();
		});
	hlayout->addWidget(quit);

	vbox->addWidget(hbox);
	this->mainWindow->setCentralWidget(centre);

	this->mainWindow->restoreGeometry(settings.value("geometry").toByteArray());
	this->mainWindow->show();
	this->save=newprefs.getSavedPrefValue("prefs/Save History").toBool();
	this->sticky=newprefs.getSavedPrefValue("prefs/Sticky").toBool();
	this->ontop=newprefs.getSavedPrefValue("prefs/On Top").toBool();
	this->setWindowStates();
}

void ClipboardClass::setWindowProps(Display *dsp,Window window,const char* grp,const char *type_name,int what)
{
	Atom window_type = XInternAtom(dsp,grp,False);
	Atom type = XInternAtom(dsp,type_name,False);

	XChangeProperty(dsp,window,window_type,XA_ATOM,32,what,(unsigned char *)&type,1);
    XFlush(dsp);
}

void ClipboardClass::setWindowStates(void)
{
	setWindowProps(this->display,this->mainWindow->winId(),"_NET_WM_STATE",NULL,PropModeReplace);
	if(this->sticky==true)
		setWindowProps(this->display,this->mainWindow->winId(),"_NET_WM_STATE","_NET_WM_STATE_STICKY",PropModeAppend);
	if(this->ontop==true)
		setWindowProps(this->display,this->mainWindow->winId(),"_NET_WM_STATE","_NET_WM_STATE_ABOVE",PropModeAppend);

}

void ClipboardClass::doPrefs(void)
{
	prefsClass	newprefs;
	QStringList  prefsdata;;
	QSize		sze;
	QStringList	prfs;

	prfs<<"check"<<"prefs/Save History"<<QVariant(this->save).toString()<<"check"<<"prefs/Sticky"<<QVariant(this->sticky).toString()<<"check"<<"prefs/On Top"<<QVariant(this->ontop).toString()<<"spinner"<<"prefs/Max Clips"<<"10"<<"500"<<QVariant(this->maxClips).toString()<<"1";

	newprefs.createDialog(PACKAGE_NAME,prfs);		
	setWindowProps(this->display,newprefs.dialogPrefs.theDialog->winId(),"_NET_WM_STATE","_NET_WM_STATE_ABOVE",PropModeAppend);

	newprefs.runDialog();
	if(newprefs.dialogPrefs.valid==true)
		{
			this->sticky=false;
			this->save=false;
			this->ontop=false;

			if(newprefs.dialogPrefs.checkBoxes.value(SAVE)->isChecked()==true)		
				this->save=true;
			if(newprefs.dialogPrefs.checkBoxes.value(STICKY)->isChecked()==true)		
				this->sticky=true;
			if(newprefs.dialogPrefs.checkBoxes.value(ONTOP)->isChecked()==true)		
				this->ontop=true;
			this->maxClips=qRound(newprefs.dialogPrefs.spinBoxes.value(MAXCLIPS)->value());

			while(this->clips->count()>this->maxClips)
				this->clips->removeItem(0);

			this->setWindowStates();
		}
}
