#ifndef REGISTRATIONFACTORY_H
#define REGISTRATIONFACTORY_H

#include "registration.h"
#include "studentregistration.h"
#include "guestregistration.h"

#include <QString>

class RegistrationFactory
{
public:
    static RegistrationFactory& getInstance();  // singleton instance getter
    Registration* createRegistration(const QString& type, Person* person, const QString& addInfo = "");
private:
    RegistrationFactory() = default; // Private constructor for signleton
    RegistrationFactory(const RegistrationFactory&) = delete;
    RegistrationFactory& operator=(const RegistrationFactory &) = delete;
};

#endif // REGISTRATIONFACTORY_H
