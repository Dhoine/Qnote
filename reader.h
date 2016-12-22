#ifndef READER_H
#define READER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QFile>
#include <QString>
#include <QDir>

class Reader
{
    QStringList* lists;
    void readElements(QXmlStreamReader&,int);
    void readXml();
public:
    QStringList* getlists();
    Reader();
    ~Reader();
};

#endif // READER_H
