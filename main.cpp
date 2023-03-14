#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include "translator.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Translator::initialize(&a);
    Translator::setLanguage("Catalan");
    MainWindow w;
    w.show();
    return a.exec();
}
