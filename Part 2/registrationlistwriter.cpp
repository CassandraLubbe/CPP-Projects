#include "registrationlistwriter.h"

#include "studentregistration.h"
#include "guestregistration.h"

#include <QtXml>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QDebug>


RegistrationListWriter::RegistrationListWriter(const RegistrationList &registrationList)
    : registrationList(registrationList) {}

void RegistrationListWriter::writeToXml(const QString &filePath)
{
    // Initialize a QDomDocument for the data to be read to
    QDomDocument doc;
    QDomElement root = doc.createElement("registrationlist");   // initialize the root for the document
    doc.appendChild(root);  // append root to document

    const QList<Registration*>& registration = registrationList.getRegistrations(); // read registrations into a readable list

    for (const Registration* reg : registration)    // cycle through registrations
    {
        QDomElement registrationElement = doc.createElement("registrations");
        registrationElement.setAttribute("type", reg->metaObject()->className());

        //Attendee Data Section
        QDomElement attendeeElement = doc.createElement("attendee");

        //name data
        QDomElement nameElement = doc.createElement("name");
        nameElement.appendChild(doc.createTextNode(reg->getAttendee()->getName()));
        attendeeElement.appendChild(nameElement);

        //affiliation data
        QDomElement affiliationElement = doc.createElement("affiliation");
        affiliationElement.appendChild(doc.createTextNode(reg->getAttendee()->getAffiliation()));
        attendeeElement.appendChild(affiliationElement);

        //email data
        QDomElement emailElement = doc.createElement("email");
        emailElement.appendChild(doc.createTextNode(reg->getAttendee()->getEmail()));
        attendeeElement.appendChild(emailElement);

        registrationElement.appendChild(attendeeElement);

        //Booking Date Data
        QDomElement bookingElement = doc.createElement("bookingdate");
        bookingElement.appendChild(doc.createTextNode(reg->getBookingDate().toString(Qt::ISODate)));
        registrationElement.appendChild(bookingElement);

        //Registration Fee Data

        //fee data
        QDomElement feeElement = doc.createElement("registrationfee");
        feeElement.appendChild(doc.createTextNode(QString::number(reg->calculateFee())));
        registrationElement.appendChild(feeElement);

        if (const StudentRegistration* studentReg = dynamic_cast<const StudentRegistration*>(reg))  // safely convert pointers to matching registration
        {
            QDomElement qualificationElement = doc.createElement("qualification");
            qualificationElement.appendChild(doc.createTextNode(studentReg->getQualification()));
            registrationElement.appendChild(qualificationElement);
        }

        if (const GuestRegistration* guestReg = dynamic_cast<const GuestRegistration*>(reg))    // safely convert pointers to matching registration
        {
            QDomElement categoryElement = doc.createElement("category");
            categoryElement.appendChild(doc.createTextNode(guestReg->getCategory()));
            registrationElement.appendChild(categoryElement);
        }

        root.appendChild(registrationElement);  // Add all the above details to the root, to bring the data to a close in XML file

    }

    QFile file(filePath);   // State when the file did not open and was not able to write
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "File failed to open.";
        return;
    }

    QTextStream out(&file);
    out << doc.toString();
    file.close();   // ensure file closes once done
}
