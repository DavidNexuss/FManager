#include "translator.h"
#include <map>

void Translator::setLanguage(const QString& language)
{
    const static std::map<QString,QString> availableLanguages =
    {
        {"Spanish","spanish"},
        {"Catalan","catalan"}
    };

    const auto it = availableLanguages.find(language);
    if(it != availableLanguages.end()) {
        translator->load(it->second);
    }
    app->removeTranslator(translator);
    app->installTranslator(translator);
}
void Translator::initialize(QApplication *a) {
    app = a;
    translator = new QTranslator();
}
