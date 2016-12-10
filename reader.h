#ifndef READER_H
#define READER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QFile>
#include <QString>
#include <QDir>

class reader
{
    QStringList* lists;
    void readElements(QXmlStreamReader&,int);
    void readXml();
public:
    QStringList* getlists();
    reader();
};

#endif // READER_H