#include "registrationlistreader.h"

#include <QMessageBox>
#include "registration.h"
#include "studentregistration.h"
#include "guestregistration.h"
#include "person.h"

#include <QDebug>

RegistrationListReader::RegistrationListReader() {}

bool RegistrationListReader::readFromFile(const QString &fileName, RegistrationList &registrationList)
{
    // Create file instance to be read
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  // check to ensure that the file opened
    {
        QMessageBox::warning(nullptr, "Error", "Failed to open file.");
        return false;
    }

    xmlReader.setDevice(&file); // set the reader to device to read, in this case, file
    currentList = &registrationList;    // create an instance of registrationList

    while (!xmlReader.atEnd() && !xmlReader.hasError()) // if reader not at the end of file and doesn't have an error continue
    {
        xmlReader.readNext();   // start reading

        if (xmlReader.isStartElement()) // read first element
        {
            //qDebug() << "Reading first element";
            if (xmlReader.name() == QString("registrationlist"))    // If text matches, then read next
            {
                xmlReader.readNext();
            }
            else if (xmlReader.name() == QString("registrations"))  // if registration read, then read registration type
            {
                QString type = xmlReader.attributes().value("type").toString();
                //qDebug() << "Reading registrations of type:" << type;
                readRegistration(type);
            }
            else
            {
                xmlReader.skipCurrentElement();
            }
        }
    }

    if (xmlReader.hasError())   // notifies user if there was an error
    {
        QMessageBox::warning(nullptr, "Error", "Failed to parse file.");
        return false;
    }
    file.close();   // ensure file closes once done
    return true;

}


void RegistrationListReader::readRegistration(const QString &type)
{
    Person *person = nullptr;   // sets the pointer to null

    while (!xmlReader.atEnd() && !xmlReader.hasError())
    {
        xmlReader.readNext();

        if (xmlReader.isStartElement())
        {
            if (xmlReader.name() == QString("attendee"))    // if text matches attendee, then attendee is read
            {
                //qDebug() << "Inside attendee element";
                readAttendee();
                person = new Person(name, affiliation, email);  // create new person
            }
            else if (xmlReader.name() == QString("bookingdate"))    // read booking date
            {
                bookingDate = xmlReader.readElementText();
            }
            else if (xmlReader.name() == QString("qualification"))  // read qualification
            {
                qualification = xmlReader.readElementText();
            }
            else if (xmlReader.name() == QString("category"))   // read category
            {
                category = xmlReader.readElementText();
            }
            else
            {
                xmlReader.skipCurrentElement(); // otherwise continue if neither of these
            }
        }
        else if (xmlReader.isEndElement() && xmlReader.name() == QString("registrations"))
        {

            break;
        }
    }

    if (person && !type.isEmpty())
    {
        if (!currentList->isRegistered(name))   // ensure name isn't already registered
        {
            addInfo.clear();    // ensures variable is clear before adding contents
            if (!qualification.isEmpty())
            {
                addInfo = qualification;    // load qualification data into variable
            }
            else if (!category.isEmpty())
            {
                addInfo = category;     // load category data into variable
            }

            // Create a registration instance with the type, person, and additional info for each being read
            Registration *registration = RegistrationFactory::getInstance().createRegistration(type, person, addInfo);

            if (registration)
            {
                currentList->addRegistration(registration);
                //qDebug() << "Added registration for " << person->getName();
            }
            else
            {
                delete person;
            }
        }
        else
        {
            // Lets user know that duplicates were found when loading data into table
            qDebug() << "Duplicate registration found: " << person->getName();
            delete person;
        }
    }
}

void RegistrationListReader::readAttendee()
{
    // ensure that all fields are clear before reading the next attendee's details (accounts for different types of registrations)
    name.clear();
    affiliation.clear();
    email.clear();
    category.clear();
    qualification.clear();

    while (!xmlReader.atEnd() && !xmlReader.hasError())
    {
        xmlReader.readNext();

        if (xmlReader.readNextStartElement())
        {

            if (xmlReader.name() == QString("name"))    // if text matches, read data
            {
                name = xmlReader.readElementText();
                //qDebug() << "Name has been read";
            }
            else if (xmlReader.name() == QString("affiliation"))    // if text matches, read data
            {
                affiliation = xmlReader.readElementText();
                //qDebug() << "Affiliation has been read";
            }
            else if (xmlReader.name() == QString("email"))  // if text matches, read data
            {
                email = xmlReader.readElementText();
                //qDebug() << "Email has been read";
            }
            else
            {
                xmlReader.skipCurrentElement();
            }
        }
        else if (xmlReader.isEndElement() && xmlReader.name() == QString("attendee"))
        {
            break;
        }
    }
}


