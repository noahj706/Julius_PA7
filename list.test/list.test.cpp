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
    Data d(record);

    //assert
    assert(d.toCSVString() == record);
    pass("data constructor");
}

void test_copyConstructor()
{
    //arrange
    Data original("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");
    original.writeAbsence();

    //act
    Data copy(original);

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
    Data d(record);

    //act
    string output = d.toCSVString();

    //assert
    assert(output == record);
    pass("data.toCSVString()");
}

void test_getName()
{
    //arrange
    Data d("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");

    //act
    string result = d.getName();

    //assert
    assert(result == "Ben Schreiber");
    pass("data.getName()");
}

void test_writeAbsence()
{
    //arrange
    Data d("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");
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
    Data d("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");
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
    Data d("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");
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
    Data d("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");
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
    Data d("123,123456789,\"Schreiber,Ben\",bennard@hotmail.com,30,CS,Senior");
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
//class node tests
void test_node_constructor()
{
    //arrange
    int value = 67;

    //act
    Node<int> n(value);

    //assert
    assert(n.getItem() == 67);
    assert(n.pNext == nullptr);
    pass("node constructor");
}

void test_node_copyConstructor()
{
    //arrange
    Node<int> original(67);

    //act
    Node<int> copy(original);

    //assert
    assert(copy.getItem() == original.getItem());
    assert(copy.pNext == original.pNext);
    pass("node copy constructor");
}

void test_node_assignmentOperator()
{
    //arrange
    Node<int> original(67);
    Node<int> assigned(0);

    //act
    assigned = original;

    //assert
    assert(assigned.getItem() == original.getItem());
    assert(assigned.pNext == original.pNext);
    pass("node.operator=()");
}

void test_node_hasNext_true()
{
    //arrange
    Node<int> a(1);
    Node<int> b(2);

    //act
    a.pNext = &b;

    //assert
    assert(a.hasNext() == true);
    pass("node.hasNext() true");
}

void test_node_hasNext_false()
{
    //arrange
    Node<int> n(1);

    //actl; there's nothin to rly act here, pNext is already a nullptr

    //assert
    assert(n.hasNext() == false);
    pass("node.hasNext() false");
}

void test_node_getItem()
{
    //arrange
    string word = "hello";

    //act
    Node<string> n(word);

    //assert
    assert(n.getItem() == "hello");
    pass("node.getItem()");
}

//List tests
void test_list_constructor()
{
    //arrange — act
    List<int> list;

    //assert
    assert(list.isEmpty() == true);
    assert(list.front() == nullptr);
    pass("list constructor");
}

void test_list_isEmpty_true()
{
    //arrange — act
    List<int> list;

    //assert
    assert(list.isEmpty() == true);
    pass("list.isEmpty() true");
}

void test_list_isEmpty_false()
{
    //arrange
    List<int> list;

    //act
    list.insertFront(1);

    //assert
    assert(list.isEmpty() == false);
    pass("list.isEmpty() false");
}

void test_list_insertFront()
{
    //arrange
    List<int> list;

    //act
    list.insertFront(1);
    list.insertFront(2);
    list.insertFront(3);

    //assert
    assert(list.front()->getItem() == 3);
    assert(list.front()->pNext->getItem() == 2);
    assert(list.front()->pNext->pNext->getItem() == 1);
    pass("list.insertFront()");
}

void test_list_insertBack()
{
    //arrange
    List<int> list;

    //act
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);

    //assert
    assert(list.front()->getItem() == 1);
    assert(list.front()->pNext->getItem() == 2);
    assert(list.front()->pNext->pNext->getItem() == 3);
    pass("list.insertBack()");
}

void test_list_copyConstructor()
{
    //arrange
    List<int> original;
    original.insertBack(1);
    original.insertBack(2);
    original.insertBack(3);

    //act
    List<int> copy(original);

    //assert
    assert(copy.front()->getItem() == 1);
    assert(copy.front()->pNext->getItem() == 2);
    assert(copy.front()->pNext->pNext->getItem() == 3);
    copy.insertFront(67);//modify copy to verify independence from original
    assert(original.front()->getItem() == 1);
    pass("list copy constructor");
}

void test_list_front()
{
    //arrange
    List<int> list;
    list.insertFront(67);

    //act
    Node<int>* front = list.front();

    //assert
    assert(front != nullptr);
    assert(front->getItem() == 67);
    pass("list.front()");
}

void test_list_front_empty()
{
    //arrange — act
    List<int> list;

    //assert
    assert(list.front() == nullptr);
    pass("list.front() empty");
}

int main(void)
{
    //data tests
    test_constructor();
    test_copyConstructor();
    test_toCSVString();
    test_getName();
    test_writeAbsence();
    test_getLastAbsenceDate();
    test_deleteAbsence_isFound();
    test_deleteAbsence_notFound();
    test_deleteAbsence_orderPreserved();
    //node tests
    test_node_constructor();
    test_node_copyConstructor();
    test_node_assignmentOperator();
    test_node_hasNext_true();
    test_node_hasNext_false();
    test_node_getItem();
    //list tests
    test_list_constructor();
    test_list_isEmpty_true();
    test_list_isEmpty_false();
    test_list_insertFront();
    test_list_insertBack();
    test_list_copyConstructor();
    test_list_front();
    test_list_front_empty();

    cout << "\nAll tests passed!!!!\n" << std::endl;
    return 0;
}