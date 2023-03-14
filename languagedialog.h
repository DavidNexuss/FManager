#ifndef LANGUAGEDIALOG_H
#define LANGUAGEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QComboBox>
#include <QPushButton>

#define LanguageDialog_WIDGET_LIST(o) \
o(QComboBox*,chooseLanguage) \
o(QPushButton*,close)

QT_BEGIN_NAMESPACE
namespace Ui { class LanguageDialog; }
QT_END_NAMESPACE

class LanguageDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LanguageDialog(QWidget *parent = nullptr);

private:

    Ui::LanguageDialog *ui;
    QString selectedLanguage;

    #define declare_widget(classn,varn) classn varn;
    LanguageDialog_WIDGET_LIST(declare_widget)
    #undef declare_widget
public slots:

    void setLanguage(const QString& name);
};

#endif // LANGUAGEDIALOG_H
