
#ifndef _PREFSCLASS_
#define _PREFSCLASS_

#include "globals.h"

#define RITESTRETCH 2

struct prefsReturnStruct
{
//simple
	QDialog					*theDialog=NULL;
	QHash<int,QLineEdit*>	editBoxes;
	QHash<int,QString>		editBoxesPrefsName;
	int						editBoxCnt=0;
	QHash<int,QComboBox*>	comboBoxes;
	QHash<int,QString>		comboBoxesPrefsName;
	int						comboBoxCnt=0;
	QHash<int,QCheckBox*>	checkBoxes;
	QHash<int,QString>		checkBoxesPrefsName;
	int						checkBoxCnt=0;
	QHash<int,QDoubleSpinBox*>		spinBoxes;
	QHash<int,QString>		spinBoxesPrefsName;
	int						spinBoxCnt=0;

//compound
	QHash<int,QLineEdit*>	colourBoxes;
	QHash<int,QString>		colourBoxesPrefsName;
	int						colourBoxCnt=0;
	QHash<int,QLineEdit*>	fontBoxes;
	QHash<int,QString>		fontBoxesPrefsName;
	int						fontBoxCnt=0;
	QHash<int,QLineEdit*>	fileBoxes;
	QHash<int,QString>		fileBoxesPrefsName;
	int						fileBoxCnt=0;

	bool						valid=false;
};

class prefsClass
{
	public:
		prefsClass(QString pname="");
		~prefsClass();

		prefsReturnStruct	dialogPrefs;
		QHash<int,QVariant>	prefsData;
		QHash<int,QStringList>	prefsStrData;
		QStringList			prefsNames;
		bool					paged=false;
		QString				opSep="\n";
		QDialogButtonBox		*bb;
		QDialogButtonBox::StandardButton	selectedButton;
		QStringList			extraCliArgs;

		bool					doCliArgs(int argc,char **argv,option longoptions[]);
		void					createDialog(QString title,QStringList items,QSize sze=QSize(-1,-1));
		void					runDialog(void);

		void					writePrefs(bool usereal);
		void					writeManualPrefs(void);
		void					writeSinglePref(QString name);
		void					printCurrentPrefs(void);
		void					addPref(QString name,QVariant qvar);
		void					setPrefValue(QString name,QVariant val);
		unsigned long		hashFromKey(QString key);
		QVariant				getPrefValue(QString name);
		QVariant				getSavedPrefValue(QString name);
		QVariant				addPrefSavedValue(QString name,QVariant qvar);
		void					appendStrPref(QString name,QString str);

		static void			cleanTemp(QString str);

	protected:
	private:
		QString				prefsFileName;
		QString				tempPrefsFileName;
		QString				bestFontColour(QString colour);
		QString				fixPrefName(QString name);
};

#endif
