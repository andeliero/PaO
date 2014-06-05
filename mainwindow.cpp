#include "mainwindow.h"


mainwindow::mainwindow(essemu &sm, QWidget* parent): shop(sm) ,QMainWindow(parent) {
	tbl=0;
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
    DRow->setShortcut(QKeySequence::Delete);
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
    connect(Search,SIGNAL(triggered()),this,SLOT(activeSearch()));
    connect(CloseSearch,SIGNAL(triggered()),this,SLOT(closeSearch()));
}

void mainwindow::newFile(){
    if(shop.isEmpty()) closeFile();
    tbl= new table(this,&shop);
	setCentralWidget(tbl);
	Close->setEnabled(true);
	Save->setEnabled(true);
	SaveAs->setEnabled(true);
    NRow->setEnabled(true);
	DRow->setEnabled(true);
    Search->setEnabled(true);
    connect(NRow,SIGNAL(triggered()),this,SLOT(addElement()));
    connect(DRow,SIGNAL(triggered()),tbl,SLOT(removeRow()));
    connect(tbl,SIGNAL(changed()),this,SLOT(changeState()));
	setWindowTitle("GuitarShop - untitled*");
}

void mainwindow::closeFile(){
    if(shop.isEmpty()) return;
    if(shop.isChanged()){
		QMessageBox msgBox;
        msgBox.setText(tr("The document has been modified."));
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
		if(ret==QMessageBox::Save){
            saveFile();
		}
    }
    NRow->disconnect(this,SLOT(addElement()));
    DRow->disconnect(tbl,SLOT(removeRow()));
    tbl->disconnect(this,SLOT(changeState()));
    shop.deleteAll();
    delete tbl;
    tbl=0;
	NRow->setEnabled(false);
	DRow->setEnabled(false);
	setWindowTitle("GuitarShop");
}

void mainwindow::activeSearch(){
    searchdialog* srchd = new searchdialog(tbl,&shop,this);
	srchd->show();
    CloseSearch->setEnabled(true);
    NRow->setEnabled(false);
    DRow->setEnabled(false);
}

void mainwindow::closeSearch(){
    CloseSearch->setEnabled(false);
    tbl->refresh();
    CloseSearch->setEnabled(false);
    NRow->setEnabled(true);
    DRow->setEnabled(true);
}

void mainwindow::openFile(){
    QString a = QFileDialog::getOpenFileName(this,tr("Apri file..."),QDir::currentPath(),"*.xml");
    if(!a.isEmpty()){
        newFile();
        shop.openXml(a.toStdString());
        SaveAs->setEnabled(true);
        setWindowTitle("GuitarShop - "+QString::fromStdString(shop.getFilename()));
        tbl->refresh();
    }
}

void mainwindow::saveFile(){
    if(QString::fromStdString(shop.getFilename()).isEmpty())
		saveasFile();
	else{
        if(shop.isChanged()){
            shop.saveXml(shop.getFilename());
            setWindowTitle("GuitarShop - "+QString::fromStdString(shop.getFilename()));
        }
	}
}

void mainwindow::changeState(){
    shop.setChanged(true);
    setWindowTitle("GuitarShop -"+QString::fromStdString(shop.getFilename())+"*");
}

void mainwindow::saveasFile(){
	QString a=QFileDialog::getSaveFileName(this,tr("Salva file come..."),QDir::currentPath(),"*.xml");
	if(!a.isEmpty()){
        shop.saveXml(a.toStdString());
        setWindowTitle("GuitarShop - "+QString::fromStdString(shop.getFilename()));
	}
}

void mainwindow::addElement(){
    elementdialog* lmd= new elementdialog(&shop,this);
	lmd->show();
    connect(lmd,SIGNAL(addedelement()),tbl,SLOT(refresh()));
}

void mainwindow::close(){
	closeFile();
	emit QMainWindow::close();
}
