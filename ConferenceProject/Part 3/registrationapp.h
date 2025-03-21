#ifndef REGISTRATIONAPP_H
#define REGISTRATIONAPP_H

#include <QWidget>
#include <QDialog>
#include <QHeaderView>
#include <QApplication>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDomDocument>
#include <QLabel>
#include "registrationlist.h"
#include "studentregistration.h"
#include "guestregistration.h"
#include "registrationlistwriter.h"
#include "registrationlistreader.h"

class RegistrationApp   : public QWidget
{
    Q_OBJECT
public:
    RegistrationApp(QWidget* parent = nullptr);

private slots:
    void addStandardRegistration();
    void addStudentRegistration();
    void addGuestRegistration();
    void queryRegistrations();
    void addRegistration(Registration* registration);
    void updateRegistrationTable();
    void deleteRegistration();
    void writeToXMLfile();
    void readXMLfile();

private:
    RegistrationList registrationList;
    QTableWidget* tableWidget;

    QWidget* mainWidget;
    QWidget* bottomWidget;

    QLabel* titleLabel;
    QLabel* queryLabel;
    QLabel* registrationLabel;

    QVBoxLayout* layoutMain;
    QVBoxLayout* layoutInput;
    QVBoxLayout* layoutQuery;
    QHBoxLayout* layoutButtons;

    QPushButton* standardButton;
    QPushButton* studentButton;
    QPushButton* guestButton;
    QPushButton* queryButton;
    QPushButton* deleteButton;
    QPushButton* xmlButton;
    QPushButton* readButton;

};

#endif // REGISTRATIONAPP_H
