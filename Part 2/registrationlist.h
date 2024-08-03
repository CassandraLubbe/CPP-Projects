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

    bool sameEmailDifferentName(const QString& email, const QString& name) const;
    bool deleteRegistration(const QString& name, const QString& email);

    QList<Registration*> getRegistrations() const;

private:
    QList<Registration*> m_AttendeeList;
};

#endif // REGISTRATIONLIST_H
