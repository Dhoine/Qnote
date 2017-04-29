#ifndef SETTINGSSTORAGE_H
#define SETTINGSSTORAGE_H

#include <QObject>
#include <QXmlStreamReader>
#include <QFile>
#include <QString>
#include <QDir>
#include <QXmlStreamWriter>

class SettingsStorage
{
    SettingsStorage();
    QString font,font_size,line_wrap_mode,line_numeration,
             background_color,controlflow_color,keywords_color,
             types_color,preprocessor_color,lang,functions_color,
             search_background_color,comments_color, normal_text_color,
             search_text_color, quotes_color,classes_color;
public:
    static SettingsStorage& Instance()
    {
        static SettingsStorage s;
        return s;
    }
    SettingsStorage(SettingsStorage const&) = delete;
    void operator =(SettingsStorage const&) = delete;
    void saveSettings();
    void readXml();
    QString getFont();
    QString getFontSize();
    QString getLineWrapMode();
    QString getLineNumeration();
    QString getBackgroundColor();
    QString getControlflowColor();
    QString getKeywordsColor();
    QString getTypesColor();
    QString getPreprocessorColor();
    QString getLang();
    QString getFunctionColor();
    QString getSearchBackgroundColor();
    QString getCommentsColor();
    QString getNormalTextColor();
    QString getSearchTextColor();
    QString getQuotesColor();
    QString getClassesColor();

    void setFont(QString);
    void setFontSize(QString);
    void setLineWrapMode(QString);
    void setLineNumeration(QString);
    void setBackgroundColor(QString);
    void setControlflowColor(QString);
    void setKeywordsColor(QString);
    void setTypesColor(QString);
    void setPreprocessorColor(QString);
    void setLang(QString);
    void setFunctionColor(QString);
    void setSearchBackgroundColor(QString);
    void setCommentsColor(QString);
    void setNormalTextColor(QString);
    void setSearchTextColor(QString);
    void setQuotesColor(QString);
    void setClassesColor(QString);
};

#endif // SETTINGSSTORAGE_H
