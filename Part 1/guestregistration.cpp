#include "guestregistration.h"

GuestRegistration::GuestRegistration(Person *a, const QString c)
    : Registration(a), m_Category(c) {}

double GuestRegistration::calculateFee() const
{
    return (Registration::STANDARD_FEE * 0.1);  // calculates free by setting it to 10% of the Standard Fee
}

QString GuestRegistration::toString() const
{
    return QString("Guest %1, Category: %2").arg(Registration::toString(), m_Category);
}

QString GuestRegistration::getCategory() const
{
    return m_Category;
}
