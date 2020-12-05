#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    QString fileSpec = QStringLiteral(":/Translations/tetris.qm");
    translator.load(fileSpec, ".");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();
    return a.exec();
}
