#include "settingsform.h"
#include "ui_settingsform.h"
#include <QColor>
#include <QColorDialog>
#include <QPalette>
#include <QMessageBox>

SettingsForm::SettingsForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
    SettingsStorage *reader=&SettingsStorage::Instance();
    reader->readXml();
    ui->fontComboBox->setCurrentFont(QFont(reader->getFont()));
    ui->spinBox->setValue(reader->getFontSize().toInt());
    ui->comboBox->setCurrentIndex(reader->getLineWrapMode().toInt());
    ui->comboBox_3->setCurrentIndex(reader->getLineNumeration().toInt());
    ui->comboBox_2->setCurrentText(reader->getLang());
    background=QColor(reader->getBackgroundColor());
    controlflow=QColor(reader->getControlflowColor());
    keywords=QColor(reader->getKeywordsColor());
    types=QColor(reader->getTypesColor());
    preprocessor=QColor(reader->getPreprocessorColor());
    normal_text=QColor(reader->getNormalTextColor());
    comments=QColor(reader->getCommentsColor());
    functions=QColor(reader->getFunctionColor());
    search_background=QColor(reader->getSearchBackgroundColor());
    search_text=QColor(reader->getSearchTextColor());
    quotes=QColor(reader->getQuotesColor());
    classes=QColor(reader->getClassesColor());
    QFont font=QFont(reader->getFont());
    QPalette palette;
        palette.setColor(QPalette::Base,background);
        if(background.isValid())
        {
            ui->textBrowser->setPalette(palette);
            palette.setColor(QPalette::Text,normal_text);
            ui->textBrowser_2->setPalette(palette);
            palette.setColor(QPalette::Text,controlflow);
            ui->textBrowser_3->setPalette(palette);
            palette.setColor(QPalette::Text,keywords);
            ui->textBrowser_4->setPalette(palette);
            palette.setColor(QPalette::Text,types);
            ui->textBrowser_5->setPalette(palette);
            palette.setColor(QPalette::Text,preprocessor);
            ui->textBrowser_6->setPalette(palette);
            palette.setColor(QPalette::Text,comments);
            ui->textBrowser_7->setPalette(palette);
            palette.setColor(QPalette::Text,functions);
            ui->textBrowser_8->setPalette(palette);
            palette.setColor(QPalette::Text,quotes);
            ui->textBrowser_11->setPalette(palette);
            palette.setColor(QPalette::Text,classes);
            ui->textBrowser_12->setPalette(palette);
            palette.setColor(QPalette::Base,search_background);
            palette.setColor(QPalette::Text,search_text);
            ui->textBrowser_9->setPalette(palette);
            ui->textBrowser_10->setPalette(palette);
        }
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::on_pushButton_clicked()
{
    const QColor color = QColorDialog::getColor(Qt::green, this, "Select Color");
    QPalette palette;
        palette.setColor(QPalette::Base,color);
        if(color.isValid())
        {
            ui->textBrowser->setPalette(palette);
            palette.setColor(QPalette::Text,normal_text);
            ui->textBrowser_2->setPalette(palette);
            palette.setColor(QPalette::Text,controlflow);
            ui->textBrowser_3->setPalette(palette);
            palette.setColor(QPalette::Text,keywords);
            ui->textBrowser_4->setPalette(palette);
            palette.setColor(QPalette::Text,types);
            ui->textBrowser_5->setPalette(palette);
            palette.setColor(QPalette::Text,preprocessor);
            ui->textBrowser_6->setPalette(palette);
            palette.setColor(QPalette::Text,comments);
            ui->textBrowser_7->setPalette(palette);
            palette.setColor(QPalette::Text,functions);
            ui->textBrowser_8->setPalette(palette);
            palette.setColor(QPalette::Text,quotes);
            ui->textBrowser_11->setPalette(palette);
            palette.setColor(QPalette::Text,classes);
            ui->textBrowser_12->setPalette(palette);
        }
        background=color;
}

void SettingsForm::on_pushButton_3_clicked()
{
    QColor color = QColorDialog::getColor(controlflow, this, "Select Color");
    QPalette pal;
    if (color.isValid()) controlflow=color;
    pal.setColor(QPalette::Base,background);
    pal.setColor(QPalette::Text, controlflow);
    ui->textBrowser_3->setPalette(pal);
}

void SettingsForm::on_pushButton_5_clicked()
{
    QColor color = QColorDialog::getColor(types, this, "Select Color");
    if (color.isValid()) types=color;
    QPalette pal;
    pal.setColor(QPalette::Base,background);
    pal.setColor(QPalette::Text, types);
    ui->textBrowser_5->setPalette(pal);
}

void SettingsForm::on_pushButton_7_clicked()
{
    QColor color = QColorDialog::getColor(comments, this, "Select Color");
    if (color.isValid()) background=color;
    QPalette pal;
    pal.setColor(QPalette::Base,background);
    pal.setColor(QPalette::Text, comments);
    ui->textBrowser_7->setPalette(pal);
}

void SettingsForm::on_pushButton_2_clicked()
{
    QColor color = QColorDialog::getColor(normal_text, this, "Select Color");
    if (color.isValid()) normal_text=color;
    QPalette pal;
    pal.setColor(QPalette::Base,background);
    pal.setColor(QPalette::Text, normal_text);
    ui->textBrowser_2->setPalette(pal);
}

void SettingsForm::on_pushButton_4_clicked()
{
    QColor color = QColorDialog::getColor(keywords, this, "Select Color");
    if (color.isValid()) keywords=color;
    QPalette pal;
    pal.setColor(QPalette::Base,background);
    pal.setColor(QPalette::Text, keywords);
    ui->textBrowser_4->setPalette(pal);
}

void SettingsForm::on_pushButton_6_clicked()
{
    QColor color = QColorDialog::getColor(preprocessor, this, "Select Color");
    if (color.isValid()) preprocessor=color;
    QPalette pal;
    pal.setColor(QPalette::Base,background);
    pal.setColor(QPalette::Text, preprocessor);
    ui->textBrowser_6->setPalette(pal);
}

void SettingsForm::on_pushButton_8_clicked()
{
    QColor color = QColorDialog::getColor(functions, this, "Select Color");
    if (color.isValid()) functions=color;
    QPalette pal;
    pal.setColor(QPalette::Base,background);
    pal.setColor(QPalette::Text, functions);
    ui->textBrowser_8->setPalette(pal);
}

void SettingsForm::on_pushButton_12_clicked()
{
    QString MESSAGE("You need to restart the app to apply settings.");
    QMessageBox::information(this, tr("Apply settings"), MESSAGE);
    SettingsStorage *reader=&SettingsStorage::Instance();
    reader->setFont(ui->fontComboBox->currentFont().family());
    reader->setFontSize(QString::number(ui->spinBox->value()));
    reader->setLineWrapMode(QString::number(ui->comboBox->currentIndex()));
    reader->setLineNumeration(QString::number(ui->comboBox_3->currentIndex()));
    reader->setLang(ui->comboBox_2->currentText());
    reader->setBackgroundColor(background.name());
    reader->setControlflowColor(controlflow.name());
    reader->setKeywordsColor(keywords.name());
    reader->setTypesColor(types.name());
    reader->setPreprocessorColor(preprocessor.name());
    reader->setNormalTextColor(normal_text.name());
    reader->setCommentsColor(comments.name());
    reader->setFunctionColor(functions.name());
    reader->setSearchBackgroundColor(search_background.name());
    reader->setSearchTextColor(search_text.name());
    reader->setQuotesColor(quotes.name());
    reader->setClassesColor(classes.name());
    reader->saveSettings();
}

void SettingsForm::on_pushButton_11_clicked()
{
    QColor color = QColorDialog::getColor(quotes, this, "Select Color");
    if (color.isValid()) quotes=color;
    QPalette pal;
    pal.setColor(QPalette::Base,background);
    pal.setColor(QPalette::Text, quotes);
    ui->textBrowser_11->setPalette(pal);
}

void SettingsForm::on_pushButton_9_clicked()
{
    QColor color = QColorDialog::getColor(search_background, this, "Select Color");
    if (color.isValid()) search_background=color;
    QPalette pal;
    pal.setColor(QPalette::Base,search_background);
    pal.setColor(QPalette::Text, search_text);
    ui->textBrowser_9->setPalette(pal);
    ui->textBrowser_10->setPalette(pal);
}

void SettingsForm::on_pushButton_10_clicked()
{
    QColor color = QColorDialog::getColor(search_text, this, "Select Color");
    if (color.isValid()) search_text=color;
    QPalette pal;
    pal.setColor(QPalette::Base,search_background);
    pal.setColor(QPalette::Text, search_text);
    ui->textBrowser_10->setPalette(pal);
    ui->textBrowser_9->setPalette(pal);
}

void SettingsForm::on_pushButton_14_clicked()
{
    QColor color = QColorDialog::getColor(classes, this, "Select Color");
    if (color.isValid()) classes=color;
    QPalette pal;
    pal.setColor(QPalette::Base,background);
    pal.setColor(QPalette::Text, classes);
    ui->textBrowser_12->setPalette(pal);
}

void SettingsForm::on_pushButton_13_clicked()
{
    this->close();
}

void SettingsForm::on_fontComboBox_currentFontChanged(const QFont &f)
{
    QFont font=f;
    font.setPointSize(ui->spinBox->value());
    ui->textBrowser_2->setFont(font);
    ui->textBrowser_2->setText("Example");
    font.setWeight(QFont::Bold);
    ui->textBrowser_3->setFont(font);
    ui->textBrowser_3->setText("Example");
    ui->textBrowser_4->setFont(font);
    ui->textBrowser_4->setText("Example");
    ui->textBrowser_5->setFont(font);
    ui->textBrowser_5->setText("Example");
    ui->textBrowser_6->setFont(font);
    ui->textBrowser_6->setText("Example");
    font.setWeight(QFont::Normal);
    ui->textBrowser_7->setFont(font);
    ui->textBrowser_7->setText("Example");
    ui->textBrowser_8->setFont(font);
    ui->textBrowser_8->setText("Example");
    ui->textBrowser_9->setFont(font);
    ui->textBrowser_9->setText("Example");
    ui->textBrowser_10->setFont(font);
    ui->textBrowser_10->setText("Example");
    ui->textBrowser_11->setFont(font);
    ui->textBrowser_11->setText("Example");
    font.setWeight(QFont::Bold);
    ui->textBrowser_12->setFont(font);
    ui->textBrowser_12->setText("Example");
}

void SettingsForm::on_spinBox_valueChanged(int arg1)
{
    QFont font=ui->fontComboBox->currentFont();
    font.setPointSize(arg1);
    ui->textBrowser_2->setFont(font);
    ui->textBrowser_2->setText("Example");
    font.setWeight(QFont::Bold);
    ui->textBrowser_3->setFont(font);
    ui->textBrowser_3->setText("Example");
    ui->textBrowser_4->setFont(font);
    ui->textBrowser_4->setText("Example");
    ui->textBrowser_5->setFont(font);
    ui->textBrowser_5->setText("Example");
    ui->textBrowser_6->setFont(font);
    ui->textBrowser_6->setText("Example");
    font.setWeight(QFont::Normal);
    ui->textBrowser_7->setFont(font);
    ui->textBrowser_7->setText("Example");
    ui->textBrowser_8->setFont(font);
    ui->textBrowser_8->setText("Example");
    ui->textBrowser_9->setFont(font);
    ui->textBrowser_9->setText("Example");
    ui->textBrowser_10->setFont(font);
    ui->textBrowser_10->setText("Example");
    ui->textBrowser_11->setFont(font);
    ui->textBrowser_11->setText("Example");
    font.setWeight(QFont::Bold);
    ui->textBrowser_12->setFont(font);
    ui->textBrowser_12->setText("Example");
    ui->textBrowser_12->setText("Example");
}
