#include "menu.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::ofstream;

void Menu::displayMenu() const
{
    system("cls");
    cout << "\n===== Attendance Menu =====\n"
        << "1. Import Course List\n"
        << "2. Load Master List\n"
        << "3. Store Masater List\n"
        << "4. Mark Absences\n"
        << "5. Edit Absences\n"
        << "6. Generate Report\n"
        << "7. Exit\n"
        << "===========================\n"
        << "\nEnter Choice:\n\t-> ";
}
void Menu::displayReportMenu() const
{
    system("cls");
    cout << "\n===== Reprot Menu =====\n"
        << "1. Report all students' most recent absence)\n"
        << "2. Report students by absence threshold\n"
        << "=======================\n"
        << "\nEnter Choice:\n\t-> ";
}
void Menu::run() // main menu loop aka the wrapper
{
    int choice = 0;

    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//flushes out input stream til newline hit

        switch (choice)
        {
        case 1: 
            importCourseList(); 
            break;
        case 2: 
            loadMasterList();  
            break;
        case 3:
            storeMasterList(); 
            break;
        case 4: 
            markAbsences();   
            break;
        case 5: 
            editAbsences();  
            break;
        case 6: 
            generateReport();  
            break;
        case 7: 
            cout << "Closing Program...\n"; 
            break;
        default:
            cout << "INVALID INPUT!! Try again.\n";
            system("pause");
            break;
        }
    } while (choice != 7);
}

void Menu::importCourseList() //option 1: reads classlist.csv, destroys and overwrites master list
{
    ifstream infile("classlist.csv");
    if (!infile)
    {
        cout << "Error: classlist.csv not found.\n";
        system("pause");
        return;
    }

    //destroy existing master list by overwiting with empty list
    masterList = List<Data>();

    string record;
    getline(infile, record);//flush out first line of needless title stuffs
    while (std::getline(infile, record))
    {
        if (!record.empty())
            masterList.insertFront(Data(record));
    }

    infile.close();
    cout << "Course list imported successfully.\n";
    system("pause");
}

void Menu::loadMasterList() //option 2: populates master list from master.csv
{
    ifstream infile("master.csv");
    if (!infile)
    {
        cout << "Error: master.csv not found.\n";
        system("pause");
        return;
    }

    masterList = List<Data>();

    string record;
    while (std::getline(infile, record))
    {
        if (!record.empty())
        {
            masterList.insertFront(Data(record));
        }
    }

    infile.close();
    cout << "Master list loaded successfully.\n";
    system("pause");
}
void Menu::storeMasterList() //option 3: stores master list contents to master.csv
{
    ofstream outfile("master.csv");
    if (!outfile)
    {
        cout << "Error: could not open master.csv for writing.\n";
        system("pause");
        return;
    }

    Node<Data>* pCur = masterList.front();
    while (pCur)
    {
        outfile << pCur->getItem().toCSVString();
        if (pCur->getItem().getAbsenceCount() > 0)
        {
            outfile << ',' << pCur->getItem().absenceStackToCSV() << '\n';
        }
        else
        {
            outfile << '\n';
        }
        
        pCur = pCur->pNext;
    }

    outfile.close();
    cout << "Master list stored successfully.\n";
    system("pause");
}
void Menu::markAbsences() //option 4: displays each student and prompts for absence
{
    if (masterList.isEmpty())
    {
        cout << "Master list is empty.\n";
        system("pause");
        return;
    }

    Node<Data>* pCur = masterList.front();
    string input;//string and not char so the getline() is easy to work with

    while (pCur)
    {
        cout << pCur->getItem().getName() << " -- absent? (y/n): ";
        std::getline(cin, input);

        if (input == "y" || input == "Y")
        {
            pCur->getItem().writeAbsence();
        }

        pCur = pCur->pNext;
    }

    cout << "Absences marked.\n";
    system("pause");
}

Node<Data>* Menu::findStudent(const string& query) const //finds student by name or ID
{
    Node<Data>* pCur = masterList.front();

    while (pCur)
    {
        if (pCur->getItem().getName() == query || pCur->getItem().getID() == query)
        {
            return pCur;
        }
        pCur = pCur->pNext;
    }

    return nullptr;
}

void Menu::editAbsences() //option 5: prompts for student and absence date to edit
{
    string query;
    cout << "Enter student name or ID:\n\t->  ";
    std::getline(cin, query);

    Node<Data>* pNode = findStudent(query);
    if (!pNode)
    {
        cout << "Student not found.\n";
        system("pause");
        return;
    }

    cout << "Student found: " << pNode->getItem().getName() << '\n';
    if (pNode->getItem().getAbsenceCount() > 0)
    {
        cout << "Most recent absence: " << pNode->getItem().getLastAbsenceDate() << '\n';
    }
    else
    {
        cout << "Student has no absences!\n";
        system("pause");
        return;
    }

    string date;
    cout << "Enter absence date to delete (M/D/YYYY): ";
    std::getline(cin, date);

    if (pNode->getItem().deleteAbsence(date))
    {
        cout << "Absence deleted successfully.\n";
        system("pause");
    }
    else
    {
        cout << "Absence date not found.\n";
        system("pause");
    }
}

void Menu::reportAll() //option 6.1: shows most recent absence for all students
{
    if (masterList.isEmpty())
    {
        cout << "Master list is empty.\n";
        system("pause");
        return;
    }

    ofstream outfile("report_all.txt");
    if (!outfile)
    {
        cout << "Error: could not open report_all.txt for writing.\n";
        system("pause");
        return;
    }

    Node<Data>* pCur = masterList.front();

    while (pCur)
    {
        outfile << pCur->getItem().getName();

        if (pCur->getItem().getAbsenceCount() > 0)
        {
            outfile << " -- latest absence: " << pCur->getItem().getLastAbsenceDate();
        }
        else
        {
            outfile << " -- no absences ";
        }

        outfile << '\n';
        pCur = pCur->pNext;
    }

    outfile.close();
    cout << "Report written to report_all.txt\n";
    system("pause");
}

void Menu::reportByThreshold() //option 6.2: shows students with absences >= threshold
{
    int threshold = 0;
    cout << "Enter absence threshold:\n\t->  ";
    cin >> threshold;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    ofstream outfile("report_threshold.txt");
    if (!outfile)
    {
        cout << "Error: could not open report_threshold.txt for writing.\n";
        system("pause");
        return;
    }

    Node<Data>* pCur = masterList.front();
    bool anyFound = false;

    outfile << "Students with [ " << threshold << " ] absences:\n";
    while (pCur)
    {
        if (pCur->getItem().getAbsenceCount() >= threshold)
        {
            outfile << pCur->getItem().getName() << '\n';
            anyFound = true;
        }
        pCur = pCur->pNext;
    }

    outfile.close();

    if (!anyFound)
    {
        cout << "No students found at or above threshold.\n";
        system("pause");
    }
    else
    {
        cout << "Report written to report_threshold.txt\n";
        system("pause");
    }
}

void Menu::generateReport() //option 6: report submenu
{
    int choice = 0;

    displayReportMenu();
    cin >> choice;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice)
    {
    case 1: 
        reportAll();   
        break;
    case 2: 
        reportByThreshold();
        break;
    default: 
        cout << "INVALID CHOICE!!!1 !\n"; 
        system("pause");
        break;
    }
}