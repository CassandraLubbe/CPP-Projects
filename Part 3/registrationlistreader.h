#ifndef REGISTRATIONLISTREADER_H
#define REGISTRATIONLISTREADER_H

#include <QXmlStreamReader>
#include <QFile>
#include "registrationlist.h"

class RegistrationListReader
{
public:
    RegistrationListReader();
    bool readFromFile(const QString &fileName, RegistrationList &registrationList);

private:
    void readRegistration(const QString &type);
    void readAttendee();

    QXmlStreamReader xmlReader;
    RegistrationList *currentList;
    QString name;
    QString affiliation;
    QString email;
    QString bookingDate;
    QString qualification;
    QString category;
    QString addInfo;

};

#endif // REGISTRATIONLISTREADER_H
