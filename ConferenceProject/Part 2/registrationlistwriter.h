#ifndef REGISTRATIONLISTWRITER_H
#define REGISTRATIONLISTWRITER_H

#include <QString>
#include "registrationlist.h"

class RegistrationListWriter
{
public:
    RegistrationListWriter(const RegistrationList& registrationList);
    void writeToXml(const QString& filePath);

private:
    const RegistrationList& registrationList;
};

#endif // REGISTRATIONLISTWRITER_H
