#pragma once

#include <string>
#include "list.hpp"

using std::string;

class Menu
{
    List<Data> masterList;

    //menu option helpers
    void importCourseList();  //option 1: reads classlist.csv, overwrites master list
    void loadMasterList();    //option 2: populates master list from master.csv
    void storeMasterList();   //option 3: stores master list to master.csv
    void markAbsences();      //option 4: runs through master list and marks absences
    void editAbsences();      //option 5: edits absences for a specific student
    void generateReport();    //option 6: report submenu

    //report submenu helpers
    void reportAll();                  //option 6.1: shows most recent absence for all students
    void reportByThreshold();          //option 6.2: shows students with absences >= threshold

    //general helpers
    void displayMenu() const;          //prints main menu options
    void displayReportMenu() const;    //prints report submenu options
    Node<Data>* findStudent(const string& query) const; //finds student by name or ID

public:
    Menu() = default;  //constructor
    ~Menu() = default; //destructor

    void run(); //main menu loop

};