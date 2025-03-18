#include "registrationapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RegistrationApp w;
    w.show();
    return a.exec();
}
