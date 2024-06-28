#include "mainscence.h"

#include <QApplication>
#include"dataconfig.h"
#include<QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScence w;
    w.show();

    return a.exec();
}

