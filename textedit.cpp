#include "textedit.h"
#include <QPainter>
#include <QPaintEvent>
#include <QtWidgets>
#include <QErrorMessage>
#include <QFileDialog>
#include "highlighter.h"
#include "mainwindow.h"

//![constructor]
TextEdit::TextEdit(QWidget *parent):QPlainTextEdit(parent)
{
    this->setLineWrapMode(NoWrap);
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(emitSize()));
    connect(this, SIGNAL(modificationChanged(bool)),this, SLOT(setMod(bool)));

    Highlighter* highlighter = new Highlighter(this->document());
    emit blockCountChanged(0);
}

//![constructor]

//![extraAreaWidth]

int TextEdit::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

//![extraAreaWidth]

//![slotUpdateExtraAreaWidth]

void TextEdit::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

//![slotUpdateExtraAreaWidth]

//![slotUpdateRequest]

void TextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

//![slotUpdateRequest]

//![resizeEvent]

void TextEdit::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

//![resizeEvent]

//![cursorPositionChanged]

void TextEdit::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(180);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

//![cursorPositionChanged]

//![extraAreaPaintEvent_0]

void TextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

//![extraAreaPaintEvent_0]

//![extraAreaPaintEvent_1]
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
//![extraAreaPaintEvent_1]

//![extraAreaPaintEvent_2]
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
//![extraAreaPaintEvent_2]
void TextEdit::emitSize()
{
    emit textChanged(this->document()->characterCount(),this->blockCount());
}

void TextEdit::setMod(bool mod)
{
    isMod=mod;
}

TextEdit::~TextEdit()
{
    if (this->isMod)
    {
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    if (ret==QMessageBox::Save)
        saveFile();
    }
}

QString TextEdit::saveFile()
{
    if (fileName=="null")
        fileName=QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("C/C++ file (*.c *.cpp *.h)"));
    QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out << this->toPlainText();
        file.close();
        this->isMod=false;
        return fileName;
}

QString TextEdit::openFile()
{
            fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
            tr("C/C++ Files (*.c *.cpp *.h)"));

            QFile file(fileName);
            !file.open(QIODevice::ReadOnly);
            QTextStream in(&file);
            this->setPlainText(in.readAll());
            file.close();
            return fileName;
}
