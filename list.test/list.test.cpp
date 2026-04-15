#pragma once

#include <cassert>
#include <iostream>
#include "list.hpp"

using std::cout;
using std::string;

//helper(s)
void pass(const string& testName)
{
    cout << "[PASS] " << testName << '\n';
}

//class data tests
void test_constructor()
{
    //arrange
    string record = "123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior";

    //act
    data d(record);

    //assert
    assert(d.toCSVString() == record);
    pass("data constructor");
}

void test_copyConstructor()
{
    //arrange
    data original("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");
    original.writeAbsence();

    //act
    data copy(original);

    //assert
    assert(copy.toCSVString() == original.toCSVString());
    assert(copy.getAbsenceCount() == original.getAbsenceCount());
    assert(copy.getLastAbsenceDate() == original.getLastAbsenceDate());
    pass("data copy constructor");
}

void test_toCSVString()
{
    //arrange
    string record = "123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior";
    data d(record);

    //act
    string output = d.toCSVString();

    //assert
    assert(output == record);
    pass("data.toCSVString()");
}

void test_getName()
{
    //arrange
    data d("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");

    //act
    string result = d.getName();

    //assert
    assert(result == "Ben Schreiber");
    pass("data.getName()");
}

void test_writeAbsence()
{
    //arrange
    data d("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");
    assert(d.getAbsenceCount() == 0);

    //act
    d.writeAbsence();
    d.writeAbsence();

    //assert
    assert(d.getAbsenceCount() == 2);
    pass("data.writeAbsence()");
}

void test_getLastAbsenceDate()
{
    //arrange
    data d("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");
    d.writeAbsence();

    //act
    string date = d.getLastAbsenceDate();

    //assert
    assert(!date.empty());
    pass("data.getLastAbsenceDate()");
}

void test_deleteAbsence_isFound()
{
    //arrange
    data d("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");
    d.writeAbsence();
    string date = d.getLastAbsenceDate();

    //act
    bool result = d.deleteAbsence(date);

    //assert
    assert(result == true);
    assert(d.getAbsenceCount() == 0);
    pass("data.deleteAbsence");
}

void test_deleteAbsence_notFound()
{
    //arrange
    data d("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");
    d.writeAbsence();

    //act
    bool result = d.deleteAbsence("7/10/2006");//my birthday :DDDD

    //assert
    assert(result == false);
    assert(d.getAbsenceCount() == 1);
    pass("data.deleteAbsence(()");
}

void test_deleteAbsence_orderPreserved()
{
    //arranve
    data d("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");
    d.writeAbsence();
    string date1 = d.getLastAbsenceDate();
    d.writeAbsence();
    string date2 = d.getLastAbsenceDate();

    //act
    d.deleteAbsence(date1);

    //assert
    assert(d.getLastAbsenceDate() == date2);
    assert(d.getAbsenceCount() == 1);
    pass("data.deleteAbsence()");
}

int main(void)
{
    test_constructor();
    test_copyConstructor();
    test_toCSVString();
    test_getName();
    test_writeAbsence();
    test_getLastAbsenceDate();
    test_deleteAbsence_isFound();
    test_deleteAbsence_notFound();
    test_deleteAbsence_orderPreserved();

    cout << "\nAll tests passed!!!!\n" << std::endl;
    return 0;
}