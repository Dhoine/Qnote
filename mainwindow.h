#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "textedit.h"
#include <QString>
#include <QVector>
#include <QMenu>
#include <settingsform.h>
#include <reader.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setupMenus();
    virtual ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVector<TextEdit*> documentsList;
    QMenu *fileMenu;
    QMenu *toolsMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *saveAllAct;
    QAction *closeAct;
    QAction *closeAllAct;
    QAction *settingsAct;
    QAction *gitgui;
    QAction *gitkonfile;
    QAction *gitkondir;
    QTimer *typingTimer;
    SettingsForm settings;
    static void gitkonFile(QFileInfo info)
    {
        QDir::setCurrent(info.absoluteDir().path());
        QString test=QString("gitk ")+info.fileName();
        system((QString("gitk ")+info.fileName()).toLatin1());
    }
    static void gitkonDir(QFileInfo info)
    {
        QDir::setCurrent(info.absoluteDir().path());
        system("gitk");
    }

private slots:
    void deleteTab(int);
    void onLineEdited();
    void changeCounter(int,int);
    void newFile();
    void save();
    void saveAs();
    void open();
    void saveAll();
    void close();
    void closeAll();
    void find();
    void openSettings();
    void openGitGui();
    void openGitkOnFile();
    void openGitkOnDir();
};

#endif // MAINWINDOW_H
