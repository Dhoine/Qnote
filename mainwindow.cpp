#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupMenus();
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(deleteTab(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deleteTab(int i)
{
    ui->tabWidget->removeTab(i);
    delete documentsList[i];
    documentsList.removeAt(i);
}

void MainWindow::changeCounter(int chars, int lines)
{
    QString ch, li;
    if (chars==2)
        ch=QString::number(chars-1)+" char, ";
    else
        ch=QString::number(chars-1)+" chars, ";
    if (lines==1)
        li=QString::number(lines)+" line";
    else
        li=QString::number(lines)+" lines";

    ui->label->setText(ch+li);
}


void MainWindow::setupMenus()
{
    newAct=new QAction ("New",this);
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the current document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    saveAllAct = new QAction(tr("&Save All"), this);
    saveAllAct->setStatusTip(tr("Save all the documents to disk"));
    connect(saveAllAct, &QAction::triggered, this, &MainWindow::saveAll);

    closeAct=new QAction(tr("&Close"),this);
    closeAct->setStatusTip(tr("Close current document"));
    connect(closeAct,&QAction::triggered ,this,&MainWindow::close);

    closeAllAct=new QAction(tr("&Close all"),this);
    closeAllAct->setStatusTip(tr("Close all documents"));
    connect(closeAllAct,&QAction::triggered,this,&MainWindow::closeAll);

    fileMenu=ui->menuBar->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAllAct);
    fileMenu->addAction(closeAct);
    fileMenu->addAction(closeAllAct);
}

void MainWindow::closeAll()
{
    int temp=ui->tabWidget->count();
    for(int i=0;i<temp;i++)
        close();
}

void MainWindow::close()
{
    deleteTab(ui->tabWidget->currentIndex());
}

void MainWindow::newFile()
{
    TextEdit* text=new TextEdit;
    connect(text,SIGNAL(textChanged(int,int)),this,SLOT(changeCounter(int,int)));
    ui->tabWidget->addTab(text,"New file");
    documentsList.append(text);
}

void MainWindow::save()
{
    if (documentsList.isEmpty()) return;
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),documentsList[ui->tabWidget->currentIndex()]->saveFile());
}

void MainWindow::saveAll()
{
    if (documentsList.isEmpty()) return;
    for (int i=0; i<ui->tabWidget->count();i++)
    ui->tabWidget->setTabText(i,documentsList[i]->saveFile());
}

void MainWindow::open()
{
    TextEdit* text=new TextEdit;
    connect(text,SIGNAL(textChanged(int,int)),this,SLOT(changeCounter(int,int)));
    ui->tabWidget->addTab(text,text->openFile());
    documentsList.append(text);
}
