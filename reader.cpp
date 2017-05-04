#include "reader.h"

Reader::Reader()
{
}

void Reader::readXml()
{
    QXmlStreamReader xmlReader;
    SettingsStorage *reader=&SettingsStorage::Instance();
    QFile input(reader->getLang()+".xml");
    if (!lists[0].isEmpty())
    {
        lists[0].clear();
        lists[1].clear();
        lists[2].clear();
        lists[3].clear();
    }
    if (!input.open(QFile::ReadOnly)) return;
    xmlReader.setDevice(&input);
    xmlReader.readNextStartElement();
    while(!xmlReader.atEnd())
    {
        if(xmlReader.name()=="highlighting") xmlReader.readNextStartElement();
        else if (xmlReader.name()=="controlflow")
        {
            readElements(xmlReader,0);
        }
        else if (xmlReader.name()=="keywords")
        {
            readElements(xmlReader,1);
        }
        else if (xmlReader.name()=="types")
        {
            readElements(xmlReader,2);
        }
        else if (xmlReader.name()=="preprocessor")
        {
            readElements(xmlReader,3);
        }
        else xmlReader.readNext();
    }
    input.close();
}

void Reader::readElements(QXmlStreamReader &xmlReader, int i)
{
    while (!xmlReader.atEnd())
    {
    if (xmlReader.isEndElement())
    {
        xmlReader.readNextStartElement();
        break;
    }
    if(xmlReader.name()=="item")
    {
        lists[i].append(xmlReader.readElementText());
        xmlReader.readNext();
    }
    else xmlReader.readNext();
    }
}

QStringList* Reader::getlists()
{
    return lists;
}
