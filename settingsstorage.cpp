#include "settingsstorage.h"
SettingsStorage::SettingsStorage()
{
}

void SettingsStorage::readXml()
{
    QXmlStreamReader xmlReader;
    QFile input(QDir::currentPath()+"\\settings.xml");
    if (!input.open(QFile::ReadOnly)) return;
    xmlReader.setDevice(&input);
    xmlReader.readNextStartElement();
    xmlReader.readNextStartElement();
    xmlReader.readNextStartElement();
            font.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            font_size.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            line_wrap_mode.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            line_numeration.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            xmlReader.readNextStartElement();
            xmlReader.readNextStartElement();
            lang.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            xmlReader.readNextStartElement();
            background_color.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            controlflow_color.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            keywords_color.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            types_color.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            preprocessor_color.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            normal_text_color.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            comments_color.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            functions_color.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            search_background_color.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            search_text_color.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            quotes_color.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            classes_color.append(xmlReader.readElementText());
            xmlReader.readNextStartElement();
            xmlReader.readNextStartElement();
            xmlReader.readNextStartElement();
            xmlReader.readNextStartElement();
            path.append(xmlReader.readElementText());
    input.close();
}

void SettingsStorage::saveSettings()
{
    QXmlStreamWriter xmlWriter;
    QFile output(QDir::currentPath()+"\\settings.xml");
    if (!output.open(QFile::WriteOnly|QFile::Truncate)) return;
    xmlWriter.setDevice(&output);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("settings");
    xmlWriter.writeStartElement("textfield");
    xmlWriter.writeTextElement("font",font);
    xmlWriter.writeTextElement("font_size",font_size);
    xmlWriter.writeTextElement("line_wrap_mode",line_wrap_mode);
    xmlWriter.writeTextElement("line_numeration",line_numeration);
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("highlighting");
    xmlWriter.writeTextElement("language",lang);
    xmlWriter.writeStartElement("colors");
    xmlWriter.writeTextElement("background_color",background_color);
    xmlWriter.writeTextElement("controlflow_color",controlflow_color);
    xmlWriter.writeTextElement("keywords_color",keywords_color);
    xmlWriter.writeTextElement("types_color",types_color);
    xmlWriter.writeTextElement("preprocessor_color",preprocessor_color);
    xmlWriter.writeTextElement("normal_text_color",normal_text_color);
    xmlWriter.writeTextElement("comments_color",comments_color);
    xmlWriter.writeTextElement("functions_color",functions_color);
    xmlWriter.writeTextElement("search_background_color",search_background_color);
    xmlWriter.writeTextElement("search_text_color",search_text_color);
    xmlWriter.writeTextElement("quotes_color",quotes_color);
    xmlWriter.writeTextElement("classes_color",classes_color);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("git");
    xmlWriter.writeTextElement("PATH",path);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    output.close();
}

QString SettingsStorage::getFont()
{
    return font;
}
void SettingsStorage::setFont(QString str)
{
    font=str;
}
QString SettingsStorage::getFontSize()
{
    return font_size;
}

void SettingsStorage::setFontSize(QString str)
{
    font_size=str;
}
QString SettingsStorage::getLineWrapMode()
{
    return line_wrap_mode;
}

void SettingsStorage::setLineWrapMode(QString str)
{
    line_wrap_mode=str;
}
QString SettingsStorage::getLineNumeration()
{
    return line_numeration;
}

void SettingsStorage::setLineNumeration(QString str)
{
    line_numeration=str;
}
QString SettingsStorage::getLang()
{
    return lang;
}

void SettingsStorage::setLang(QString str)
{
    lang=str;
}
QString SettingsStorage::getBackgroundColor()
{
    return background_color;
}

void SettingsStorage::setBackgroundColor(QString str)
{
    background_color=str;
}
QString SettingsStorage::getControlflowColor()
{
    return controlflow_color;
}

void SettingsStorage::setControlflowColor(QString str)
{
    controlflow_color=str;
}
QString SettingsStorage::getKeywordsColor()
{
    return keywords_color;
}

void SettingsStorage::setKeywordsColor(QString str)
{
    keywords_color=str;
}
QString SettingsStorage::getTypesColor()
{
    return types_color;
}

void SettingsStorage::setTypesColor(QString str)
{
    types_color=str;
}
QString SettingsStorage::getPreprocessorColor()
{
    return preprocessor_color;
}

void SettingsStorage::setPreprocessorColor(QString str)
{
    preprocessor_color=str;
}
QString SettingsStorage::getNormalTextColor()
{
    return normal_text_color;
}

void SettingsStorage::setNormalTextColor(QString str)
{
    normal_text_color=str;
}
QString SettingsStorage::getCommentsColor()
{
    return comments_color;
}

void SettingsStorage::setCommentsColor(QString str)
{
    comments_color=str;
}
QString SettingsStorage::getFunctionColor()
{
    return functions_color;
}

void SettingsStorage::setFunctionColor(QString str)
{
    functions_color=str;
}
QString SettingsStorage::getSearchBackgroundColor()
{
    return search_background_color;
}

void SettingsStorage::setSearchBackgroundColor(QString str)
{
    search_background_color=str;
}
QString SettingsStorage::getSearchTextColor()
{
    return search_text_color;
}

void SettingsStorage::setSearchTextColor(QString str)
{
    search_text_color=str;
}
QString SettingsStorage::getQuotesColor()
{
    return quotes_color;
}

void SettingsStorage::setQuotesColor(QString str)
{
    quotes_color=str;
}
QString SettingsStorage::getPath()
{
    return path;
}

void SettingsStorage::setPath(QString str)
{
    path=str;
}
QString SettingsStorage::getClassesColor()
{
    return classes_color;
}

void SettingsStorage::setClassesColor(QString str)
{
    classes_color=str;
}
