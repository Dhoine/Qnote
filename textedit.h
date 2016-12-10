#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QtWidgets>
#include "highlighter.h"
#include <QPainter>
#include <QPaintEvent>
#include <QFileDialog>
#include <QTextCursor>
QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE
class LineNumberArea;

class TextEdit: public QPlainTextEdit
{
    Q_OBJECT
public:
    TextEdit(QWidget* parent=0);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    QString saveFileAs();
    void findText(QString);
    void clearBackground();
    ~TextEdit();
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void emitSize();
    void setMod(bool);
    void updateSearch();
public slots:
    QString saveFile();
    QString openFile();


signals:
    void textChanged(int,int);

private:
    QWidget *lineNumberArea;
    bool isMod=false;
    QString fileName="null";
    Highlighter* highlighter;
    bool highlightBackground(QString);
    QString prevSearch;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(TextEdit *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    TextEdit *codeEditor;
};

#endif // TEXTEDIT_H
