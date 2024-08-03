#ifndef STUDENTREGISTRATION_H
#define STUDENTREGISTRATION_H

#include "registration.h"

class StudentRegistration : public Registration
{
    Q_OBJECT
public:
    StudentRegistration(Person* a, const QString q);
    double calculateFee() const override;
    QString toString() const override;

    QString getQualification() const;

private:
    QString m_Qualification;
};

#endif // STUDENTREGISTRATION_H
