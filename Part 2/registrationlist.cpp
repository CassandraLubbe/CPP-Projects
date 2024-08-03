#include "registrationlist.h"

RegistrationList::RegistrationList() {}

RegistrationList::~RegistrationList()
{
    qDeleteAll(m_AttendeeList);
}

void RegistrationList::addRegistration(Registration *r)
{
    m_AttendeeList.append(r);
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
    double total = 0.00;    // esure fee is initialized to zero

    for (Registration* reg : m_AttendeeList)
    {
        QString className = reg->metaObject()->className(); // stores the class name as a QString variable

        // This if statement matches the selected type "t" with the classname of it's kind. Then calculates the total
        // according to the registration that matches the metaObject classname
        if (t == "All" ||
            (t == "Student Registration" && className == "StudentRegistration") ||
            (t == "Guest Registration" && className == "GuestRegistration") ||
            (t == "Standard Registration" && className == "Registration"))
        {
            total += reg->calculateFee();
        }   // compares the classname to the query selected by user, then calculates accordingly
    }

    return total;
}

int RegistrationList::totalRegistrations(const QString a) const
{
    int count = 0;

    for (Registration* reg : m_AttendeeList)    // cycle through the list of registration
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

        if (r_email == email)   // if the email matches one that is already in the registration list
        {
            if (r_name != name) // the name is then compared before allowing the suer to be registered
            {
                return true;    // if it's a different name, user is registered
            }
            else
            {
                return false;   // if the name matchers, user is not registered
            }
        }
        else
        {
            return true;    // if email doesn't match, user is registered
        }
    }

    return true;
}

bool RegistrationList::deleteRegistration(const QString &name, const QString &email)
{
    QMutableListIterator<Registration*> it(m_AttendeeList); // allows for the list to be modified during iterations
    // registrations are loaded into the list and used to perform actions that modify the list

    while (it.hasNext())   // while there is still data in the list, continue to read
    {
        Registration* reg = it.next();

        if (reg->getAttendee()->getName() == name && reg->getAttendee()->getEmail() == email) // it it matches then delete registration
        {
            qDebug() << "Deleting registration for:" << name << "with email address:" << email;
            reg->deleteData();  // delete the data and pointer from the original list
            delete reg; // delete the pointer to the data from current copy of list
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
