#include "highlighter.h"

void Highlighter::setWord(QString& s)
{
    word=s;
    if (word=="") word="dfgsdfhsdhsdhsdhsdhsdhdshsdfhsd";
    searchRule.pattern=QRegExp(word,Qt::CaseInsensitive);
    rehighlight();
}

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    SettingsStorage *reader=&SettingsStorage::Instance();
    searchFormat.setBackground(QColor(reader->getSearchBackgroundColor()));
    searchFormat.setForeground(QColor(reader->getSearchTextColor()));
    searchRule.format=searchFormat;
    searchRule.pattern=QRegExp("sdgfsdgsdfhsdfhaehaerhaefhsfdhsdhsd");
    HighlightingRule rule;
    Reader *xmlReader=&Reader::Instance();
    xmlReader->readXml();
    lists=xmlReader->getlists();
    controlFormat.setForeground(QColor(reader->getControlflowColor()));
    controlFormat.setFontWeight(QFont::Bold);
    foreach (const QString &pattern, lists[0]) {
        rule.pattern = QRegExp("\\b"+pattern+"\\b");
        rule.format = controlFormat;
        highlightingRules.append(rule);
    }

    keywordFormat.setForeground(QColor(reader->getKeywordsColor()));
    keywordFormat.setFontWeight(QFont::Bold);
    foreach (const QString &pattern, lists[1]) {
        rule.pattern = QRegExp("\\b"+pattern+"\\b");
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    typesFormat.setForeground(QColor(reader->getTypesColor()));
    typesFormat.setFontWeight(QFont::Bold);
    foreach (const QString &pattern, lists[2]) {
        rule.pattern = QRegExp("\\b"+pattern+"\\b");
        rule.format = typesFormat;
        highlightingRules.append(rule);
    }

    preprocessorFormat.setForeground(QColor(reader->getPreprocessorColor()));
    preprocessorFormat.setFontWeight(QFont::Bold);
    foreach (const QString &pattern, lists[3]) {
        if (!(reader->getLang()=="Java"))
        {
            rule.pattern = QRegExp("\\b*#"+pattern);
        } else
        {
            rule.pattern= QRegExp("\\b"+pattern+"\\b");
        }
        rule.format = preprocessorFormat;
        highlightingRules.append(rule);
    }


    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(QColor(reader->getClassesColor()));
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(QColor(reader->getCommentsColor()));
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(QColor(reader->getCommentsColor()));

    quotationFormat.setForeground(QColor(reader->getQuotesColor()));
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(QColor(reader->getFunctionColor()));
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }

    QRegExp expression(searchRule.pattern);
    int index = expression.indexIn(text);
    while (index >= 0) {
        int length = expression.matchedLength();
        setFormat(index, length, searchRule.format);
        index = expression.indexIn(text, index + length);
    }
}

Highlighter::~Highlighter()
{
}
