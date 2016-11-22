#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "textedit.h"
#include <QString>
#include <QVector>
#include <QMenu>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setupMenus();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVector<TextEdit*> documentsList;
    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAllAct;
    QAction *closeAct;
    QAction *closeAllAct;
private slots:
    void deleteTab(int);
public slots:
    void changeCounter(int,int);
    void newFile();
    void save();
    void open();
    void saveAll();
    void close();
    void closeAll();
};

#endif // MAINWINDOW_H
