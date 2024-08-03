#include "registration.h"

const double Registration::STANDARD_FEE = 120.00;   // global variable fee
// Note! Changing this value will inherently change the fees calculated by GuestRegistration and StudentRegistration

Registration::Registration(Person *a)
    : m_Attendee(a), m_BookingDate(QDate::currentDate()) {}

Registration::~Registration()
{
    delete m_Attendee;
}

Person* Registration::getAttendee() const
{
    return m_Attendee;
}

QDate Registration::getBookingDate() const
{
    return m_BookingDate;
}

double Registration::calculateFee() const
{
    return STANDARD_FEE;
}

QString Registration::toString() const
{
    return QString("Attendee: %1, Booking Date: %2, Fee: %3").arg(m_Attendee->toString()).arg(m_BookingDate.toString()).arg(calculateFee());
}

void Registration::deleteData()
{
    if (m_Attendee) // if attendee exists
    {
        delete m_Attendee;  // delete attendee
        m_Attendee = nullptr;   // return pointer
    }
}
