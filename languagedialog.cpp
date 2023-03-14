#include "languagedialog.h"
#include "ui_languageDialog.h"
#include "translator.h"
LanguageDialog::LanguageDialog(QWidget *parent) : QDialog(parent),ui(new Ui::LanguageDialog)
{
    ui->setupUi(this);
    //Initializes widgets
    #define find_children(classn,varn) { varn = findChild<classn>(#varn); assert(varn); }
    LanguageDialog_WIDGET_LIST(find_children)
    #undef find_children
}

void LanguageDialog::setLanguage(const QString& name) {
    selectedLanguage = name;
    Translator::setLanguage(selectedLanguage);
}
