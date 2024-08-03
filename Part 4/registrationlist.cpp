#include "registrationlist.h"

RegistrationList::RegistrationList() {}

RegistrationList::~RegistrationList()
{
    qDeleteAll(m_AttendeeList);
}

void RegistrationList::addRegistration(Registration *r)
{
    m_AttendeeList.append(r);   // adds given registration to the registration list
}

bool RegistrationList::isRegistered(const QString n) const
{
    for (Registration* reg : m_AttendeeList)
    {
        QString attendeeName = reg->getAttendee()->getName().toLower(); // convert to lower case
        QString inputName = n.toLower();    // convert to lower case

        if (attendeeName == inputName)  // case-sensitivity comparison
        {
            return true;
        }
    }
    return false;
}

double RegistrationList::totalFee(const QString t) const
{
    double total = 0.00;    // ensures fee is initialized to zero

    for (Registration* reg : m_AttendeeList)
    {
        QString className = reg->metaObject()->className(); // stores class name as a QString variable

        // This if statement matches the selected type "t" with the class name of it's kind. Then calculates a total according to
        // the registration of that class type
        if (t == "All" ||
            (t == "Student Registration" && className == "StudentRegistration") ||
            (t == "Guest Registration" && className == "GuestRegistration") ||
            (t == "Standard Registration" && className == "Registration"))
        {
            total += reg->calculateFee();
        }   // compares the classname to the query selected by user, then calculates according to that data
    }

    return total;
}

int RegistrationList::totalRegistrations(const QString a) const
{
    int count = 0;

    for (Registration* reg : m_AttendeeList)    // cycles through the list of registrations
    {
        if (reg->getAttendee()->getAffiliation().toLower() == a.toLower())  // for every affiliation matched, counter is increased by 1
        {
            count ++;
        }
    }

    return count;
}

bool RegistrationList::sameEmailDifferentName(const QString &email, const QString &name) const
{
    for (Registration* reg : m_AttendeeList)
    {
        QString r_email = reg->getAttendee()->getEmail();
        QString r_name = reg->getAttendee()->getName();

        if (r_email == email)   // if the email entered matches an email already in the registration list
        {
            if (r_name != name) // the name is then compared before allowing the user to be registered or not.
            {
                return true;    // only true when the email matches BUT names are different
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;    // if emails don't match, user is registered
        }
    }

    return true;
}

bool RegistrationList::deleteRegistration(const QString &name, const QString &email)
{
    QMutableListIterator<Registration*> it(m_AttendeeList); // allows for the list to be modified during iteration
    // registrations are loaded into this list and then used to perform actions that modify the list

    while (it.hasNext())    // while there is stil data in the list, continue to read
    {
        Registration* reg = it.next();

        if (reg->getAttendee()->getName() == name && reg->getAttendee()->getEmail() == email)   // if this matches then delete registration
        {
            qDebug() << "Deleting registration for:" << name << "with email address:" << email;
            reg->deleteData();  // delete the data and pointer from original list
            delete reg; // delete the pointer to that data from current copy of list
            it.remove();    // remove iterator pointer
            return true;
        }
    }
    return false;
}

QList<Registration *> RegistrationList::getRegistrations() const
{
    return m_AttendeeList;
}
