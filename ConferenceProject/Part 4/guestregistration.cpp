#include "guestregistration.h"

GuestRegistration::GuestRegistration(Person *a, const QString c)
    : Registration(a), m_Category(c) {}

double GuestRegistration::calculateFee() const
{
    return (Registration::STANDARD_FEE * 0.1);  // Calculates the fee according to 10% of STANDARD_FEE
}

QString GuestRegistration::toString() const
{
    return QString("Guest %1, Category: %2").arg(Registration::toString(), m_Category);
}

QString GuestRegistration::getCategory() const
{
    return m_Category;
}

