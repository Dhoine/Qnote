#ifndef READER_H
#define READER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QFile>
#include <QString>
#include <QDir>

class Reader
{
    QStringList lists[4];
    void readElements(QXmlStreamReader&,int);
    void readXml();
    Reader();
public:
    QStringList* getlists();
    static Reader& Instance()
    {
        static Reader s;
        s.readXml();
        return s;
    }
};

#endif // READER_H
