#include "studentregistration.h"

StudentRegistration::StudentRegistration(Person *a, QString q)
    : Registration(a), m_Qualification(q) {}

double StudentRegistration::calculateFee() const
{
    return Registration::STANDARD_FEE / 2;  // calculates fee according to half of the STANDARD_FEE
}

QString StudentRegistration::toString() const
{
    return QString("Student %1, Qualification: %2").arg(Registration::toString(), m_Qualification);
}

QString StudentRegistration::getQualification() const
{
    return m_Qualification;
}
