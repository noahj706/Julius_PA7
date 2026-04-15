#include "list.hpp"

using std::ostringstream;
using std::getline;
using std::istringstream;

data::data(const string& record)//constructor, record format: "recordNumber,ID,name,email,units,program,level"
{
	istringstream instream(record);
	
	getline(instream, recordNumber, ',');
	getline(instream, ID, ',');
	getline(instream, name, '"');
	getline(instream, name, '"');
	getline(instream, email, ',');
	getline(instream, email, ',');
	getline(instream, units, ',');
	getline(instream, program, ',');
	getline(instream, level, ',');
}
data::data(const data& other)//copy constructor
{
	//record copy
	recordNumber = other.recordNumber;
	ID = other.ID;
	name = other.name;
	email = other.email;
	units = other.units;
	program = other.program;
	level = other.level;
	//absence info copy
	absenceCount = other.absenceCount;
	//absenceStack deep copy
	stack<string> temp = other.absenceStack;
	while (!temp.empty()) 
	{
		absenceStack.push(temp.top());
		temp.pop();
	}
}
void data::writeAbsence()//ups absenceCount and reports today's date to absenceStack
{
	++absenceCount;

	//gets today's date, pushes to absenceStack as string, data format: "M/D/YYYY"
	time_t t = time(0);
	struct tm* now = localtime(&t);

	ostringstream outstream;
	outstream << (now->tm_mon + 1) << '/'
		<< (now->tm_mday) << '/'
		<< (now->tm_year + 1900);

	absenceStack.push(outstream.str());
}
string data::toCSVString() const//takes all record info and returns as a .csv ready string NOTE: doesn't include absence tracking
{
	ostringstream outstream;
	outstream << recordNumber << ','
		<< ID << ','
		<< '"' << name << '"' <<','
		<< email << ','
		<< units << ','
		<< program << ','
		<< level;

	return outstream.str();
}
string data::getName() const//returns name as a "firstName lastName" string 
{
	ostringstream outstream;
	istringstream instream(name);
	string lastName, firstName;

	getline(instream, lastName, ',');
	getline(instream, firstName, ',');

	outstream << firstName << ' ' << lastName;

	return outstream.str();
}
int data::getAbsenceCount() const
{
	return absenceCount;
}
string data::getLastAbsenceDate() const
{
	return absenceStack.top();
}
bool data::deleteAbsence(const string& target)//removes an absence, returns false if passed absence date not found
{
	stack<string> temp;
	bool targetFound = false;


	//parses absenceStack, discards node that matches target string
	while (!absenceStack.empty() && !targetFound)
	{
		if (absenceStack.top() == target)
		{
			absenceStack.pop();
			targetFound = true;
			--absenceCount;
		}
		else
		{
			temp.push(absenceStack.top());
			absenceStack.pop();
		}
	}
	//puts absenceStack back togethor in proper order
	while (!temp.empty())
	{
		absenceStack.push(temp.top());
		temp.pop();
	}
	
	return targetFound;
}
