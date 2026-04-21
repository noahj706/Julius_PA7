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
class Data
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
	Data() = default;//default constructor, will immilpicitly call default string constructors
	Data(const string& record);//constructor record format: "recordNumber,ID,name,email,units,program,level"
	Data(const Data& other);//copy constructor
	~Data() = default;//destructor
	Data& operator=(const Data& other);//assignment overload

	void writeAbsence();//ups absenceCount and reports today's date to absenceStack

	string toCSVString() const;//takes all record info and returns as a .csv ready string NOTE: doesn't include absence tracking
	string absenceStackToCSV() const;//returns a string with absenceStack info for master.csv saving
	string getName() const;//returns name as a "firstName lastName" string
	string getID() const;//returns student ID for searching reasons
	int getAbsenceCount() const;
	string getLastAbsenceDate() const;

	bool deleteAbsence(const string& target);//removes an absence, returns false if passed absence date not found
};

template <class T>
class Node
{
	T item;

public:
	Node* pNext;//public because no guarding rly needed

	Node(const T& newItem)//constructor
	{
		item = newItem;
		pNext = nullptr;
	}
	Node(const Node& other)//copy constructor
	{
		item = other.item;
		pNext = other.pNext;
	}
	~Node() = default;//destructor
	Node<T>& operator= (const Node& other)//copy assignment operator
	{
		item = other.item;
		pNext = other.pNext;
		return *this;
	}
	bool hasNext() const//false if pNext == nullptr
	{
		return pNext;
	}
	T& getItem()
	{
		return item;
	}
};

template <class T>
class List
{
	Node<T>* pHead;

public:
	void deleteFront()// desctructor helper, assumes not empty
	{
		Node<T>* pCur = pHead;
		pHead = pCur->pNext;
		delete pCur;
	}
	bool isEmpty() const
	{
		return !pHead;
	}
	void insertBack(const T& newItem)//newNode at back of list, copy constructor helper
	{
		Node<T>* newNode = new Node<T>(newItem);

		if (isEmpty())//insert as head if empty list
		{
			pHead = newNode;
		}
		else//go to back of list and THEN insert
		{
			Node<T>* pCur = pHead;

			while (pCur->pNext)
			{
				pCur = pCur->pNext;
			}

			pCur->pNext = newNode;
		}
	}
	List()//contructor
	{
		pHead = nullptr;
	}
	List(const List& other)//copy constructor
	{
		this->pHead = nullptr;

		Node<T>* otherCur = other.pHead;

		for (; otherCur; otherCur = otherCur->pNext)
		{
			insertBack(otherCur->getItem());
		}
	}
	~List()//destructor
	{
		while (!isEmpty())
		{
			deleteFront();
		}
	}
	void insertFront(const T& newItem)//newNode at front of list
	{
		Node<T>* newNode = new Node<T>(newItem);

		newNode->pNext = pHead;
		pHead = newNode;
	}
	Node<T>* front() const
	{
		return pHead;
	}
};
