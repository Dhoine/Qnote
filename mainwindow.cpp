#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <thread>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupMenus();
    typingTimer = new QTimer( this );
    typingTimer->setSingleShot( true );
    connect( typingTimer, &QTimer::timeout, this, &MainWindow::find);
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(onLineEdited()) );
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(deleteTab(int)));
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(find()));
    connect(ui->findButton,SIGNAL(clicked(bool)),this,SLOT(find()));
    connect(ui->newFileLinkButton,SIGNAL(clicked(bool)),this,SLOT(newFile()));
    ui->findButton->setShortcut(QKeySequence::FindNext);
    connect(ui->openFileLinkButton,SIGNAL(clicked(bool)),this,SLOT(open()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete typingTimer;
    delete fileMenu;
    delete newAct;
    delete openAct;
    delete saveAct;
    delete saveAsAct;
    delete saveAllAct;
    delete closeAct;
    delete closeAllAct;
    delete settingsAct;
    delete gitgui;
    delete gitkondir;
    delete gitkonfile;
}

void MainWindow::onLineEdited()
{
    typingTimer->start( 2000 );
}

void MainWindow::find()
{
    typingTimer->stop();
    if (documentsList.isEmpty()) return;
    if(ui->lineEdit->text()=="")
    {
        ui->lineEdit->setFocus();
    }
    documentsList[ui->tabWidget->currentIndex()]->findText(ui->lineEdit->text());
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
    newAct = new QAction ("New",this);
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

    saveAsAct = new QAction (tr("&Save as..."),this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save document as..."));
    connect(saveAsAct,&QAction::triggered,this,&MainWindow::saveAs);

    saveAllAct = new QAction(tr("&Save All"), this);
    saveAllAct->setStatusTip(tr("Save all the documents to disk"));
    connect(saveAllAct, &QAction::triggered, this, &MainWindow::saveAll);

    closeAct=new QAction(tr("&Close"),this);
    closeAct->setShortcut(QKeySequence::Close);
    closeAct->setStatusTip(tr("Close current document"));
    connect(closeAct,&QAction::triggered ,this,&MainWindow::close);

    closeAllAct=new QAction(tr("&Close all"),this);
    closeAllAct->setStatusTip(tr("Close all documents"));
    connect(closeAllAct,&QAction::triggered,this,&MainWindow::closeAll);

    fileMenu=ui->menuBar->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(saveAllAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);
    fileMenu->addAction(closeAllAct);

    toolsMenu=ui->menuBar->addMenu(tr("Tools"));
    settingsAct=new QAction(tr("&Settings"),this);
    settingsAct->setStatusTip(tr("Open settings window"));
    connect(settingsAct,&QAction::triggered,this,&MainWindow::openSettings);
    toolsMenu->addAction(settingsAct);

    gitgui=new QAction(tr("&Git gui"),this);
    gitgui->setStatusTip(tr("Open git grapthical interface on urrent file's directory"));
    connect(gitgui,&QAction::triggered,this,&MainWindow::openGitGui);
    toolsMenu->addAction(gitgui);

    gitkonfile=new QAction(tr("&Gitk on current file"));
    gitkonfile->setStatusTip(tr("Open gitk on current file (it will show error if there are no commits)"));
    connect(gitkonfile,&QAction::triggered,this,&MainWindow::openGitkOnFile);
    toolsMenu->addAction(gitkonfile);

    gitkondir=new QAction(tr("&Gitk on current dir"));
    gitkondir->setStatusTip(tr("Open gitk on current file's directory (it will show error if there are no commits)"));
    connect(gitkondir,&QAction::triggered,this,&MainWindow::openGitkOnDir);
    toolsMenu->addAction(gitkondir);
}

void MainWindow::openSettings()
{
    settings.show();
}

void MainWindow::closeAll()
{
    int temp=ui->tabWidget->count();
    for(int i=0;i<temp;i++)
        close();
}

void MainWindow::close()
{
    if (documentsList.isEmpty()) return;
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

void MainWindow::saveAs()
{
    if (documentsList.isEmpty()) return;
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),documentsList[ui->tabWidget->currentIndex()]->saveFileAs());
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
    QString temp=text->openFile();
    if (temp=="")
    {
        delete text;
        return;
    }
    ui->tabWidget->addTab(text,temp);
    documentsList.append(text);
}
void MainWindow::openGitGui()
{
    if (documentsList.isEmpty()) return;
    QString test=documentsList.at(ui->tabWidget->currentIndex())->getFileName();
    if (test==""||test=="null") return;
    QFileInfo info(test);
    QDir temp=QDir::current();
    QDir::setCurrent(info.absoluteDir().path());
#ifdef __WIN32
    system("git-gui");
#elif __linux
    system("git gui");
#endif
    QDir::setCurrent(temp.absolutePath());
}
void MainWindow::openGitkOnFile()
{
    if (documentsList.isEmpty()) return;
    QString test=documentsList.at(ui->tabWidget->currentIndex())->getFileName();
    if (test==""||test=="null") return;
    QFileInfo info(test);
    QDir temp=QDir::current();
    //system((QString("gitk ")+info.fileName()).toLatin1());
    std::thread gitk(gitkonFile,info);
    gitk.detach();
    QDir::setCurrent(temp.absolutePath());
}

void MainWindow::openGitkOnDir()
{
    if (documentsList.isEmpty()) return;
    QString test=documentsList.at(ui->tabWidget->currentIndex())->getFileName();
    if (test==""||test=="null") return;
    QFileInfo info(test);
    QDir temp=QDir::current();
    std::thread gitk(gitkonDir,info);
    gitk.detach();
    QDir::setCurrent(temp.absolutePath());
}
