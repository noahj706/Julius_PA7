#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <ctime>

using std::string;
using std::stack;

//class for record into and absence tracking
class data
{
	//record info
	string recordNumber;
	string ID;
	string name;
	string email;
	string units;
	string program;
	string level;
	//absence tracking
	int absenceCount = 0;
	stack<string> absenceStack; //stores absence dates (MM/DD/YYYY)

public:
	data(const string& record);//constructor record format: "recordNumber,ID,name,email,units,program,level"
	data(const data& other);//copy constructor
	~data() = default;//destructor

	void writeAbsence();//ups absenceCount and reports today's date to absenceStack

	string toCSVString() const;//takes all record info and returns as a .csv ready string NOTE: doesn't include absence tracking
	string getName() const;//returns name as a "firstName lastName" string
	int getAbsenceCount() const;
	string getLastAbsenceDate() const;

	bool deleteAbsence(const string& target);//removes an absence, returns false if passed absence date not found
};

/*
template <class T>
class Node
{
	T item;

public:
	Node* pNext;//public because no guarding rly needed

	Node(T& newItem);//constructor
	Node(const Node& other);//copy constructor
	~Node();//detructor

	bool hasNext();//false if pNext == nullptr

	T& getItem();
};

template <class T>
class List
{
	Node<T>* pHead;
	void deleteFront();//destroy list helper
	bool isEmpty();

public:
	List();
	List(const List& other);
	~List();

	void insertFront(const T& newItem);
	
	Node<T>* getHead();
};
*/