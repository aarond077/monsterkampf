
#include <QApplication>
#include "game.h"
#include <QSoundEffect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game w;
    w.show();
    return a.exec();
}