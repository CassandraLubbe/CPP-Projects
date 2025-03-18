#ifndef GUESTREGISTRATION_H
#define GUESTREGISTRATION_H

#include "registration.h"

class GuestRegistration : public Registration
{
    Q_OBJECT
public:
    GuestRegistration(Person* a, const QString c);
    double calculateFee() const override;
    QString toString() const override;

    QString getCategory() const;

private:
    QString m_Category;
};

#endif // GUESTREGISTRATION_H
