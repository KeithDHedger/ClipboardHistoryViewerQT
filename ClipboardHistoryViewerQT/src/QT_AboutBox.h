
#include "globals.h"
#include "credits.h"

#ifndef _QT_ABOUTBOX_
#define _QT_ABOUTBOX_

class AboutBoxClass : public QObject
{
	public:
		AboutBoxClass(QWidget *window,QString pixpath=NULL);
		~AboutBoxClass();

		QString		licence;
		QString		credits;

		void			runAbout(void);
		void			setHomepage(QString hpaddr,QString hpstr);
		void			setBodyText(QString bodystr);
		void			showAboutQtButton(void);
		void			showLicenceButton(void);
		void			showCreditsButton(void);
		void			showHelpButton(QString htmlpath);
		static void	showHelp(QString htmlpath);

	private:
		QDialog		*aboutDialog;
		QDialog		*licenceDialog;
		QDialog		*creditsDialog;
		QLabel		*hpLabel;
		QLabel		*bodyLabel;
		QLabel		*appNameLabel;
		QPushButton	*aboutQtButton;
		QPushButton	*licenseButton;
		QPushButton	*creditsButton;
		QPushButton	*helpButton;
		QString		helpHtml;


		void			setAppName(void);
		void			showLicence(void);
		void			showCredits(void);
		void			killLicenceBox(void);
		void			killAboutBox(void);
		void			killCreditsBox(void);
	//	void			killHelpBox(void);

};

#endif
