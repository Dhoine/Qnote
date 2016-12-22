#include "textedit.h"


TextEdit::TextEdit(QWidget *parent):QPlainTextEdit(parent)
{
    this->setLineWrapMode(NoWrap);
    this->setUndoRedoEnabled(false);
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(this->document(), SIGNAL(contentsChanged()),this,SLOT(emitSize()));
    connect(this, SIGNAL(modificationChanged(bool)),this, SLOT(setMod(bool)));
    connect(this->document(),SIGNAL(contentsChange(int,int,int)),this,SLOT(updateSearch()));

    highlighter = new Highlighter(this->document());
    updateLineNumberAreaWidth(0);
    prevSearch.clear();
}

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

void TextEdit::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void TextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void TextEdit::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

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

void TextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

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
    if (this->isMod && !(this->document()->characterCount()==1 && (this->fileName=="null"||this->fileName=="")))
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
    delete highlighter;
    delete lineNumberArea;
    emit textChanged(1,0);
}

QString TextEdit::saveFile()
{
    if (fileName=="null"||fileName=="")
        fileName=QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("C/C++ file (*.c *.cpp *.h)"));
    if (fileName=="") return "null";
    QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out << this->toPlainText();
        file.close();
        this->document()->setModified(false);
        return fileName;
}

QString TextEdit::saveFileAs()
{
    QString temp=fileName;
        fileName=QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("C/C++ file (*.c *.cpp *.h)"));
        if (fileName=="") return temp;
    QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out << this->toPlainText();
        file.close();
        this->document()->setModified(false);
        return fileName;
}
QString TextEdit::openFile()
{
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("C/C++ Files (*.c *.cpp *.h)"));

            QFile file(fileName);
            file.open(QIODevice::ReadOnly);
            QTextStream in(&file);
            this->setPlainText(in.readAll());
            file.close();
            return fileName;
}

void TextEdit::findText(QString str)
{
    prevSearch=str;
    bool found=highlightBackground(str);
    if(!found) return;
        found=this->find(str);
        if (!found)
        {
            this->moveCursor(QTextCursor::Start);
            found=find(str);
        }
        else return;
}



bool TextEdit::highlightBackground(QString str)
{
    QTextDocument *document = this->document();
    wasMod=isMod;
    QTextCursor cursor(this->document());
    cursor.beginEditBlock();
    QTextCharFormat format(cursor.charFormat());
    format.setBackground(Qt::white);
    cursor.setPosition(QTextCursor::Start-1);
    cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    cursor.setCharFormat(format);
    if(str=="")
    {
        cursor.endEditBlock();
        return false;
    }
    bool found = false;

        QTextCursor highlightCursor(document);
        cursor=this->textCursor();

        format.setBackground(Qt::green);

        while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
            highlightCursor = document->find(str, highlightCursor);

            if (!highlightCursor.isNull()) {
                found = true;
                highlightCursor.mergeCharFormat(format);
            }
        }
        cursor.endEditBlock();
        emit modificationChanged(wasMod);
    return found;
}

void TextEdit::updateSearch()
{
    if (!prevSearch.isEmpty())
    {
        highlightBackground(prevSearch);
    }
}
