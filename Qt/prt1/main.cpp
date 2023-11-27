#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString str = "Carrington we have started moving";
    qDebug() << str ;

    return a.exec();
}
