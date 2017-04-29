#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QMainWindow>
#include <settingsstorage.h>
#include <QColor>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QMainWindow
{
    Q_OBJECT
    QColor background,controlflow,keywords,types,
           preprocessor,normal_text,comments,
           functions,search_background,search_text,quotes,classes;
public:
    explicit SettingsForm(QWidget *parent = 0);
    ~SettingsForm();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_13_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_fontComboBox_currentFontChanged(const QFont &f);

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
