#include "registrationfactory.h"

RegistrationFactory &RegistrationFactory::getInstance()
{
    static RegistrationFactory instance;
    return instance;
}

Registration *RegistrationFactory::createRegistration(const QString &type, Person *person, const QString &addInfo)
{
    // Compares data being read to ensure that the correct registrations are established from the file
    if (type == "Registration")
    {
        return new Registration(person);    // if the data matches Registration than an instance of Registration is created
    }
    else if (type == "StudentRegistration")
    {
        return new StudentRegistration(person, addInfo);    // if the data matches StudentRegistration than an instance of StudentRegistration is created
    }
    else if (type == "GuestRegistration")
    {
        return new GuestRegistration(person, addInfo);  // if data matches GuestRegistration than an instance of GuestRegistration is created
    }
    else
    {
        return nullptr; // if it doesn't match either, return nothing
        // even if file is empty, it will be read
    }
}


