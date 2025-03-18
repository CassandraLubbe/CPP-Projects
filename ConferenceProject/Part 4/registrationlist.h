#ifndef REGISTRATIONLIST_H
#define REGISTRATIONLIST_H

#include <QString>
#include <QList>
#include "registration.h"

class RegistrationList
{
public:
    RegistrationList();
    ~RegistrationList();

    void addRegistration(Registration* r);
    bool isRegistered(const QString n) const;
    double totalFee(const QString t) const;
    int totalRegistrations(const QString a) const;

    // This function checks whether the name is different when the email is the same
    bool sameEmailDifferentName(const QString& email, const QString& name) const;
    bool deleteRegistration(const QString& name, const QString& email);

    // Allows for the retrieval of registrations
    QList<Registration*> getRegistrations() const;

private:
    QList<Registration*> m_AttendeeList;
};

#endif // REGISTRATIONLIST_H
