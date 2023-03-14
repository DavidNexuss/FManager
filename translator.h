#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QApplication>
#include <QTranslator>
namespace Translator
{
    inline QApplication* app;
    inline QTranslator* translator;

    void initialize(QApplication* app);
    void setLanguage(const QString& languageName);
}

#endif // TRANSLATOR_H
