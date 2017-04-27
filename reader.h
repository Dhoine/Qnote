#ifndef READER_H
#define READER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QFile>
#include <QString>
#include <QDir>
#include "settingsstorage.h"

class Reader
{
    QStringList lists[4];
    void readElements(QXmlStreamReader&,int);
    Reader();
public:
    QStringList* getlists();
    static Reader& Instance()
    {
        static Reader s;;
        return s;
    }
    void readXml();
    Reader(Reader const&) = delete;
    void operator =(Reader const&)=delete;
};

#endif // READER_H
