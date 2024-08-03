#include <QApplication>
#include "registrationapp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RegistrationApp window;
    window.show();

    return a.exec();
}
