#include "registrationapp.h"
#include <QFont>

RegistrationApp::RegistrationApp(QWidget *parent)
    : QWidget(parent)
{
    // Set window title and size
    setWindowTitle("Conference Registration");
    resize(900, 500);

    // Set a main widget to maintain the other widgets
    mainWidget = new QWidget(this);

    // Font for title label
    QFont fontTitle;
    fontTitle.setFamily("Copperplate");
    fontTitle.setPointSize(18);
    fontTitle.setBold(true);
    fontTitle.setItalic(false);

    // Font for button type labels
    QFont font;
    font.setFamily("Futura");
    font.setPointSize(14);
    font.setBold(false);
    font.setBold(false);

    // Initialize and set title label to wlecome user
    titleLabel = new QLabel("Welcome to 2024 Conference Registrations", this);
    titleLabel->setFont(fontTitle);
    titleLabel->setAlignment(Qt::AlignCenter);

    // set the main layout for the widget, add title label to it.
    layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(titleLabel);

    // Initialize the buttons
    standardButton = new QPushButton("Add Standard Registration", this);
    studentButton = new QPushButton("Add Student Registration", this);
    guestButton = new QPushButton("Add Guest Registration", this);
    queryButton = new QPushButton("Query Table", this);
    deleteButton = new QPushButton("Delete a Registration", this);
    xmlButton = new QPushButton("Save to XML File", this);
    readButton = new QPushButton("Read XML File", this);

    // Initialize the table widget that will be displaying the data from RegistrationList
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(7);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Email" << "Affiliation" << "Fee" << "Type" << "Qualification" << "Category");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setSortingEnabled(true);

    // create a horizontal line to divide the title label from the buttons
    QFrame *lineH = new QFrame(this);
    lineH->setFrameShape(QFrame::HLine);
    lineH->setFrameShadow(QFrame::Sunken);
    layoutMain->addWidget(lineH);

    // Initialize the layouts to maintain the different types of buttons
    layoutInput = new QVBoxLayout(this);    // all buttons to do with adding a registration
    layoutInput->setAlignment(Qt::AlignCenter);
    layoutButtons = new QHBoxLayout(this);  // main layout for the input and query buttons
    layoutQuery = new QVBoxLayout(this);    // all buttons related to querying or performing action on data in table
    layoutQuery->setAlignment(Qt::AlignCenter);

    // Initialize the labels that identify the types of buttons to users
    registrationLabel = new QLabel("Select Type of Registration", this);
    registrationLabel->setAlignment(Qt::AlignCenter);
    registrationLabel->setFont(font);
    queryLabel = new QLabel("Perform a Query on Registrations", this);
    queryLabel->setAlignment(Qt::AlignCenter);
    queryLabel->setFont(font);

    // add the registration buttons and label to the input layout
    layoutInput->addWidget(registrationLabel);
    layoutInput->addWidget(standardButton);
    layoutInput->addWidget(studentButton);
    layoutInput->addWidget(guestButton);

    // add the query button and label to the query layout
    layoutQuery->addWidget(queryLabel);
    layoutQuery->addWidget(queryButton);
    layoutQuery->addWidget(deleteButton);
    layoutQuery->addWidget(xmlButton);
    layoutQuery->addWidget(readButton);

    // create a vertical line to serve as a divide between the two types of buttons
    QFrame *lineV = new QFrame(this);
    lineV->setFrameShape(QFrame::VLine);
    lineV->setFrameShadow(QFrame::Sunken);

    // add the button layouts with the dividing line to the layout
    layoutButtons->addLayout(layoutInput);
    layoutButtons->addWidget(lineV);
    layoutButtons->addLayout(layoutQuery);

    // Create a vertical line to serve as a divide between input and query data and the table widget
    QFrame *lineH2 = new QFrame(this);
    lineH2->setFrameShape(QFrame::HLine);
    lineH2->setFrameShadow(QFrame::Sunken);

    // add layouts and dividing line to the main layout, includes table widget
    layoutMain->addLayout(layoutButtons);
    layoutMain->addWidget(lineH2);
    layoutMain->addWidget(tableWidget);

    // Connect each button to their respective functions
    connect(standardButton, &QPushButton::clicked, this, &RegistrationApp::addStandardRegistration);
    connect(studentButton, &QPushButton::clicked, this, &RegistrationApp::addStudentRegistration);
    connect(guestButton, &QPushButton::clicked, this, &RegistrationApp::addGuestRegistration);
    connect(queryButton, &QPushButton::clicked, this, &RegistrationApp::queryRegistrations);
    connect(deleteButton, &QPushButton::clicked, this, &RegistrationApp::deleteRegistration);
    connect(xmlButton, &QPushButton::clicked, this, &RegistrationApp::writeToXMLfile);
    connect(readButton, &QPushButton::clicked, this, &RegistrationApp::readXMLfile);
}

void RegistrationApp::addStandardRegistration() // creates and instance of Registration class
{
    // Gets user input by providing the information windows individually, to prevent complications with data entry
    QString name = QInputDialog::getText(this, "Standard Registration", "Name: ");
    QString affiliation = QInputDialog::getText(this, "Standard Registration", "Affiliation:");
    QString email = QInputDialog::getText(this, "Standard Registration", "Email:");

    if (!name.isEmpty() && !affiliation.isEmpty() && !email.isEmpty())  // Checks to ensure all data fields have been entered for a complete registration
    {
        if (!registrationList.sameEmailDifferentName(email, name))  // ensures that the same name isn't registered to the same email
        {
            QMessageBox::warning(this, "Error", "Email already registered with same name.");
            return;
        }
        else
        {
            Person* person = new Person(name, affiliation, email);
            addRegistration(new Registration(person));
            updateRegistrationTable();
        }
    }
}

void RegistrationApp::addStudentRegistration()  // Creates an instance of StudentRegistration
{
    // Gets user input by providing the information windows individually, to prevent complications with data entry
    QString name = QInputDialog::getText(this, "Student Registration", "Name:");
    QString affiliation = QInputDialog::getText(this, "Student Registration", "Affiliation:");
    QString email = QInputDialog::getText(this, "Student Registration", "Email:");
    QString qualification = QInputDialog::getText(this, "Student Registration", "Qualification:");

    if (!name.isEmpty() && !affiliation.isEmpty() && !email.isEmpty() && !qualification.isEmpty())  // Ensures data fields aren't empty
    {
        if(!registrationList.sameEmailDifferentName(email, name))   // checks to ensure that no registration can have the same name and email
        {
            QMessageBox::warning(this, "Error", "Email already registrered with same name.");
            return;
        }
        else
        {
            Person* person = new Person(name, affiliation, email);
            addRegistration(new StudentRegistration(person, qualification));
            updateRegistrationTable();
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "All fields must be filled.");
    }
}

void RegistrationApp::addGuestRegistration()    // Creates a GuestRegistration instance
{
    // Gets user input by provoiding the information in individual windows, prevents complications with data entry
    QString name = QInputDialog::getText(this, "Guest Registration", "Name:");
    QString affiliation = QInputDialog::getText(this, "Guest Registration", "Affiliation:");
    QString email = QInputDialog::getText(this, "Guest Registration", "Email:");
    QString category = QInputDialog::getText(this, "Guest Registration", "Category:");

    if (!name.isEmpty() && !affiliation.isEmpty() && !email.isEmpty() && !category.isEmpty())
    {
        if (!registrationList.sameEmailDifferentName(email, name))  // Ensures that no registration is the same, by ensuring the name is different to the email
        {
            QMessageBox::warning(this, "Error", "Email already registered with the same name.");
            return;
        }
        else
        {
            Person* person = new Person(name, affiliation, email);
            addRegistration(new GuestRegistration(person, category));
            updateRegistrationTable();
        }
    }
}

void RegistrationApp::queryRegistrations()  // function to query the tablewidget with the data of RegistrationList
{
    // Lists the three types of options available to the user when querying the table
    QStringList queryOptions;
    queryOptions << "Check if person is registered"
                 << "Total attendees from an institution"
                 << "Total registration fees by type";

    bool ok = false;
    // Prompts the user to select one of the three options
    QString selectedQuery = QInputDialog::getItem(this, "Query Table", "Select a query:", queryOptions, 0, false, &ok);

    if (ok && !selectedQuery.isEmpty()) // ensures that a selection has been made
    {
        if (selectedQuery == "Check if person is registered")
        {
            // takes user input to search for a registered person
            QString name = QInputDialog::getText(this, "Check if person is regsitered", "Enter name for search:", QLineEdit::Normal, QString(), &ok);

            if (ok && !name.isEmpty()) // ensures that the data field has been filled with data and isn't empty
            {
                bool isRegistered = registrationList.isRegistered(name);    // checks whether the person is registered
                QMessageBox::information(this, "Query Result", QString("Person: %1, Registered: %2").arg(name, isRegistered ? "Yes" : "No"));

            }
        }
        else if (selectedQuery == "Total attendees from an institution")
        {
            ok = true;

            // Takes user input for the institution to be searched
            QString institution = QInputDialog::getText(this, "Total Attendees from an institution", "Enter institution for search:", QLineEdit::Normal, QString(), &ok);

            if (ok)
            {
                if (!institution.isEmpty()) // if field isn't empty then the search is performed
                {
                    int total = registrationList.totalRegistrations(institution);
                    QMessageBox::information(this, "Query Result", QString("Total attendees from %1: %2").arg(institution).arg(total));

                }
                else    // if data field empty, user prompted to enter an institution
                {
                    QMessageBox::warning(this, "Error", "Please enter an institutions to search");
                }
            }
            else
            {
                QMessageBox::warning(this, "Error", "Operation cancelled or an error occured.");
            }

        }
        else if (selectedQuery == "Total registration fees by type")
        {
            // Creates a list of the type of fee total options available to the user
            QStringList types;
            types << "Registration"
                  << "Student Registration"
                  << "Guest Registration"
                  << "All";

            // Provides user with a combo box to choose from
            QString type = QInputDialog::getItem(this, "Total registration fees by type", "Select the type:", types, 0, false, &ok);

            if (ok && !type.isEmpty())
            {
                double totalFee = registrationList.totalFee(type);  // provides a total fee calculation according to the type selected by user

                QMessageBox::information(this, "Query Result", QString("Total registration fees for %1 is: %2").arg(type).arg(totalFee));
            }
        }
    }

}

void RegistrationApp::addRegistration(Registration *registration)   // adds every registration to the registrationList
{
    registrationList.addRegistration(registration);
}

void RegistrationApp::updateRegistrationTable() // updates the table widget with the new data
{
    // clear table contents for reading in data
    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    const QList<Registration*>& registrations = registrationList.getRegistrations();

    for (int i = 0; i < registrations.size(); i++)
    {
        Registration* reg = registrations[i];
        Person* person = reg->getAttendee();
        double fee = reg->calculateFee();
        QString type = reg->metaObject()->className();  // use of metaObject to read the type of registration
        QString qualification;
        QString category;

        // dynamic casts allows for a safe converting of pointers for reading the correct data
        if (const StudentRegistration* studentReg = dynamic_cast<const StudentRegistration*>(reg))
        {
            qualification = studentReg->getQualification();
        }

        // dynamic casts allow for a safe conversting of pointers for reading the correct data
        if (const GuestRegistration* guestReg = dynamic_cast<const GuestRegistration*>(reg))
        {
            category = guestReg->getCategory();
        }

        // reads the registration data of each registration in the registraionList into the table for viewing and querying
        tableWidget->insertRow(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(person->getName()));
        tableWidget->setItem(i, 1, new QTableWidgetItem(person->getEmail()));
        tableWidget->setItem(i, 2, new QTableWidgetItem(person->getAffiliation()));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(fee, 'f', 2)));
        tableWidget->setItem(i, 4, new QTableWidgetItem(type));
        tableWidget->setItem(i, 5, new QTableWidgetItem(qualification));
        tableWidget->setItem(i, 6, new QTableWidgetItem(category));
    }

}

void RegistrationApp::deleteRegistration()  // deletes a registration
{
    // Takes user input for the registration to be deleted
    QString name = QInputDialog::getText(this, "Delete Registration", "Enter name:");

    // Finds all items in the table that match the given user input
    QList<QTableWidgetItem*> items = tableWidget->findItems(name, Qt::MatchContains);

    // if no registration is found matching the name
    if (items.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Name does not match data.");
        return;
    }

    // Takes user input for the email to ensure the correct registration it being deleted
    QString email = QInputDialog::getText(this, "Delete Registration", "Confirm email address of registration to be deleted:");

    // Locates the email that matches the user input
    QList<QTableWidgetItem*> itemsTwo = tableWidget->findItems(email, Qt::MatchExactly);

    // if no email that matches is found
    if (itemsTwo.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Email does not match data.");
        return;
    }

    // Instance of registration to be able to work with the data
    const QList<Registration*>& registrations = registrationList.getRegistrations();

    // Initialize the two items that we've located in the table to variables
    QTableWidgetItem* item = items.first();
    QTableWidgetItem* itemTwo = itemsTwo.first();

    // Set the row numbers of items found
    int row = item->row();
    int rowTwo = itemTwo->row();

    if (row != rowTwo)  // removes the possibility of deleting the wrong registration if the data isn't within the same row
    {
        QMessageBox::warning(this, "Error", "Name and email do not match data.");
    }

    // Stores the name of the table items located at the correct row location
    QString regName = tableWidget->item(row, 0)->text();
    QString regEmail = tableWidget->item(row, 1)->text();

    // Removes the registrations from the RegistrationList data
    registrationList.deleteRegistration(regName, regEmail);

    // Removes it from the table
    tableWidget->removeRow(row);

    // Provides user feedback regarding success of deletion
    QMessageBox::information(this, "Delete Registration", "Registration has been successfully deleted.");
}


void RegistrationApp::writeToXMLfile()
{
    // Let user select where to save the file, and what the file name would be
    QString filePath = QFileDialog::getSaveFileName(this, "Save XML file", "", "XML files(*.xml);;All files(*.*");

    if(!filePath.isEmpty()) // if filepath isn't empty, proceed
    {
        RegistrationListWriter writer(registrationList);    // initilaizes writer for XML file
        writer.writeToXml(filePath);    // write to given file

        QMessageBox::information(this, "Save to XML", "Registration list saved successfully");  // provide successful user feedback
    }
}

void RegistrationApp::readXMLfile()
{
    // Let user select the file to be read
    QString fileName = QFileDialog::getOpenFileName(this, "Open XML File", "", "XML Files (*.xml)");

    if (!fileName.isEmpty())    // if file has been selected, proceed
    {
        RegistrationListReader reader;  // initilaize reader for file

        if (reader.readFromFile(fileName, registrationList))    // if reader was able to enter file without error provide user feedback
        {
            QMessageBox::information(this, "Success", "Registrations loaded successfully.");
            updateRegistrationTable();
        }
        else    // if error occured, provide user feedback
        {
            QMessageBox::warning(this, "Error", "Failed to load registrations form file.");
        }
    }
}
