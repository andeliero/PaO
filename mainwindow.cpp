#include "mainwindow.h"


mainwindow::mainwindow(QWidget* parent): QMainWindow(parent) {
	cnt= new controller();
	cnt->setWindow(this);
	tbl=0;
	file="";
	mod=false;
	setGeometry(150,100,705,400);
	setWindowTitle("GuitarShop");

	Menu= new QMenu("File",this);
	MenuT= new QMenu("Tabella",this);
	MenuS= new QMenu("Ricerca",this);
	menuBar()->addMenu(Menu);
	menuBar()->addMenu(MenuT);
	menuBar()->addMenu(MenuS);
	sttbar= new QStatusBar(this);
	setStatusBar(sttbar);

	//file
	New= new QAction("Nuovo",this);
	New->setShortcuts(QKeySequence::New);
	Close= new QAction("Chiudi",this);
	Close->setEnabled(false);
	Open= new QAction("Apri",this);
	Open->setShortcuts(QKeySequence::Open);
	Save= new QAction("Salva",this);
	Save->setShortcuts(QKeySequence::Save);
	Save->setEnabled(false);
	SaveAs= new QAction("Salva come...",this);
	SaveAs->setShortcuts(QKeySequence::SaveAs);
	SaveAs->setEnabled(false);
	Exit= new QAction("Exit",this);
	Exit->setShortcuts(QKeySequence::Close);
	Menu->addAction(New);
	Menu->addAction(Close);
	Menu->addAction(Open);
	Menu->addAction(Save);
	Menu->addAction(SaveAs);
	Menu->addAction(Exit);
	//tabella
	NRow= new QAction("Inserisci Chitarra",this);
	NRow->setEnabled(false);
	DRow= new QAction("Rimuovi Chitarra",this);
	DRow->setEnabled(false);
	MenuT->addAction(NRow);
	MenuT->addAction(DRow);
	//ricerca
	Search= new QAction("Search",this);
	Search->setEnabled(false);
	CloseSearch= new QAction("Close Search", this);
	CloseSearch->setEnabled(false);
	MenuS->addAction(Search);
	MenuS->addAction(CloseSearch);
	
	
	
	
	connect(New,SIGNAL(triggered()),this,SLOT(newFile()));
	connect(Close,SIGNAL(triggered()),this,SLOT(closeFile()));
	connect(Open,SIGNAL(triggered()),this,SLOT(openFile()));
	connect(Save,SIGNAL(triggered()),this,SLOT(saveFile()));
	connect(SaveAs,SIGNAL(triggered()),this,SLOT(saveasFile()));
	connect(Exit,SIGNAL(triggered()),this,SLOT(close()));
}

void mainwindow::newFile(){
	if(!file.isEmpty()) closeFile();
	mod=true;
	tbl= new table(this,cnt);
	cnt->setTable(tbl);
	setCentralWidget(tbl);
	Close->setEnabled(true);
	Save->setEnabled(true);
	SaveAs->setEnabled(true);
	NRow->setEnabled(true);
	connect(NRow,SIGNAL(triggered()),this,SLOT(addElement()));
	DRow->setEnabled(true);
	connect(DRow,SIGNAL(triggered()),tbl,SLOT(remElement()));
	//connect(tbl,SIGNAL(cellActivated(int,int)),this,SLOT(changeState(int,int)));
	connect(tbl,SIGNAL(changed()),this,SLOT(changeState()));
	Search->setEnabled(true);
	connect(Search,SIGNAL(triggered()),this,SLOT(activeSearch()));
	setWindowTitle("GuitarShop - untitled*");
	cnt->newShop();
}

void mainwindow::closeFile(){
	if(mod){
		QMessageBox msgBox;
        msgBox.setText(tr("The document has been modified."));
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);// | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
		//if(ret==QMessageBox::Cancel) return;
		if(ret==QMessageBox::Save){
			if(!file.isEmpty())
				saveasFile();
			else
				saveFile();
			file="";
		}
	}
	delete tbl;
	file="";
	tbl=0;
	NRow->setEnabled(false);
	DRow->setEnabled(false);
	cnt->closeShop();
	setWindowTitle("GuitarShop");
}

void mainwindow::activeSearch(){
	searchdialog* srchd = new searchdialog(this);
	srchd->show();
}

void mainwindow::openFile(){
	file = QFileDialog::getOpenFileName(this,tr("Choose a GuitarShop DB"),QDir::currentPath(),"*.xml");
	setWindowTitle("GuitarShop - "+file);
	closeFile();
	cnt->openShop(file);
}

void mainwindow::saveFile(){
	if(file.isEmpty())
		saveasFile();
	else{
		if(mod){
			mod=false;
			setWindowTitle("GuitarShop - "+file);
			cout<<"salva"<<endl;
			cnt->saveShop(file);
		}
	}
}

void mainwindow::changeState(){
	if(!mod){
		mod=true;
		if(file.isEmpty())
			setWindowTitle("GuitarShop - untitled*");
		else
			setWindowTitle("GuitarShop -"+file+"*");
	}
}

void mainwindow::saveasFile(){
	QString a=QFileDialog::getOpenFileName(this,tr("Choose a GuitarShop DB"),QDir::currentPath(),"*.xml");
	if(!a.isEmpty()){
		file=a;
		saveFile();
		cout<<"salva come"<<endl;
	}
}

void mainwindow::addElement(){
	elementdialog* lmd= new elementdialog(cnt,this);
	lmd->show();
}