#pragma once
/////////////////////////////////////////////////////////////////////
//  DatabaseDAO.h - Mediator                                       //
//  ver 1.0                                                        //
//                                                                 //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell Inspiron, Windows 8.1			           //
//  Application:   NoSql Database - CIS 687 Project 1              //
//  Author:        Sushanth Suresh SUID:864888072			       //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
It acts as a mediator between the test executive and NoSqlDB, Additionally
provides querying functionalities

Both the above clases are Template classes,  that use one or more
unspecified types, defined by arguments in the template declaration.

Public Interface:
=================
DatabaseDAO Class > ---- >

DatabaseDAO()				//Parameterised constructor which populates using a file with specific path
~DatabaseDAO()			    //Destructor of DatabaseDAO instance for XML persistance
createElement()             // Creates an object and calls save function in NoSqlDb to store it
deleteKey()                 //Calls the deletion of keys in the NoSqlDb
show()                      // Displays the elements of the keys provided
editElements()              //Overloaded function Calls the updating function in NoSqlDb
convertTheTimeObject()      //Converts the trime object into string by calling NoSqlDb
validateKeys()              // validates if the keylist is empty or not
convertIntoObj()            //takes file path and sends it to NoSqDb to populate
locate()					// Implements query functionality for the metadata indatabase by doing function overloading
queryForData()              // Queries dunction for data specific 
unionOfKeys()               // Appends the Keylist
NoSqlDb<Data> db            // Private data variable that represents the database
static int countForSaving   // Static data member to persist the database into Xml after 2 addition of entries
Build Process:
==============
Required files
-Convert.h
-NoSqlDb.h
-time.h
Build commands 
- devenv Project1_Sushanth.sln /build debug


Maintenance History:
====================
ver 1.0 : 07 Feb 17
- first release
*/
#include "../Convert/Convert.h"
#include "../NoSqlDb/NoSqlDb.h"
#include <time.h>
#include <regex>

template<typename Data>
class DatabaseDAO {
private:
	NoSqlDb<Data> db;
	static int countForSaving;
public:
	DatabaseDAO(std::string filepath) {
		std::cout << "\n---- <Requirement 5> Demonstration of database can be restored using xml file\n";
		convertIntoObj(filepath, 1);
		
	}
	~DatabaseDAO()
{
		convertIntoXml();
	}
	using Key = std::string;
	using Keys = std::vector<Key>;
	using time_Date = std::time_t;
	
	//Function to create an element
	void createElement(Key key, Key name, Key category, Key description, time_Date timeDate, Keys children, Data data);
	void deleteKey(Key key);
	Key convertTheTimeObject(time_t);
	
	// Function to edit the values
	void editElements(Key key, Data value);
	void editElements(Key key, Data whereParameter, Key newValue);
	void editElements(Key key, Data whereParameter, Key newValue, Key adorremove);
	void editElements(Key key, std::time_t);
	
	//Validating the Keys
	void validateKeys(Keys emp);
	//Persist into Xml
	Key convertIntoXml();

	//Querying funstion using regular expression
	Keys rlocate(Key whereParam, Key pattern = "null", Key start_time = "null", Key end_time = "null", Keys listOf = {});
	Keys rqueryForData(Data pattern, Keys listOf = {});

	//get Object from string
	void convertIntoObj(const Key xmlString,int);
	//Querying funstion normally 
	Keys locate(Key whereParam, Key pattern = "null", Key start_time = "null", Key end_time = "null", Keys listOf = {});
	Element<Data> getValue_Of(Key oneKey);
	Keys queryForData(Data pattern, Keys listOf = {});
	Keys unionOfKeys(Keys one, Keys two);
	//Display
	void show(Keys);


	


};

template <typename Data>
int DatabaseDAO<Data>::countForSaving = 0;

//-----------Displays the elements of the keys provided-------------

template<typename Data>
void DatabaseDAO<Data>::show(Keys listing)
{
	// show children when you've implemented them
	for(Key item : listing) {
		Element<Data> temp = db.value(item);
		std::cout << "\n    " << std::setw(8) << "name" << " : " << temp.name;
		std::cout << "\n    " << std::setw(8) << "category" << " : " << temp.category;
		std::cout << "\n    " << std::setw(8) << "timeDate" << " : " << temp.timeDate;
		std::cout << "\n    " << std::setw(8) << "data" << " : " << temp.data;
		std::cout << "\n    " << std::setw(8) << "Description " << " : " << temp.description;


		Keys child = temp.children;
		if (int(child.size()) <= 0)
		{
			std::cout << "\n      " << std::setw(8) << "Dependent children " << " : " << "Null";

		}
		else
		{
			for (auto display : child)
			{
				std::cout << "\n       " << std::setw(8) << "Dependent children " << " : " << display;

			}
		}

		
	}
}
//-------------Creates an object and calls save function in NoSqlDb to store it and persisting into xml after three records are entered
template<typename Data>
void DatabaseDAO<Data>::createElement(Key key, Key name, Key category, Key description, time_Date timeDate, Keys children, Data data) {
	
	Element<Data> dataObject;
	dataObject.name = name;
	dataObject.category = category;
	dataObject.description = description;
	dataObject.timeDate = timeDate;
	dataObject.children = children;
	dataObject.data = data;
	db.save(key, dataObject);
	if (countForSaving == 1) {
		countForSaving = 0;
		
		std::string demo = convertIntoXml();
		std::cout << "\n----------<Requirement 6>Saving into database after 2 Elements are added--------- ";
		std::cout << demo;
	}
	else
	{
		countForSaving++;
	}
}

//----------Forwrds the deletion of specific key to NoSqlDb-------------
template<typename Data>
void DatabaseDAO<Data>::deleteKey(Key key) {

	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n        Before Deleting an Element the keys present are:";
	Keys storeContents = db.keys();
	for (Key eachElement : storeContents)
	{
		std::cout << "\n           " << eachElement << ":";

	}
	std::cout << "\n\n";
	db.delete_keys(key);

	std::cout << "\n        After Deleting an Element the keys present are:";
	storeContents = db.keys();
	for (Key eachElement : storeContents)
	{
		std::cout << "\n           " << eachElement << ":";

	}
}
//------------Editing elements Data
template<typename Data>
inline void DatabaseDAO<Data>::editElements(Key key, Data value)
{
	db.editData(key, value);

}
//-------------Editing elements metadata
template<typename Data>
inline void DatabaseDAO<Data>::editElements(Key key, Data whereParameter, Key newValue)
{
	db.editData(key, whereParameter, newValue);

}

//--------Edits the dependency of an element
template<typename Data>
inline void DatabaseDAO<Data>::editElements(Key key, Data whereParameter, Key newValue, Key adorremove)
{
	db.editData(key, whereParameter, newValue, adorremove);

}

//-------------------Edits the elements timestamp
template<typename Data>
inline void DatabaseDAO<Data>::editElements(Key key, std::time_t timeStamp)
{
	db.editData(key, timeStamp);

}

//--------------Converts the trime object into string by calling NoSqlDb
template<typename Data>
typename DatabaseDAO<Data>::Key DatabaseDAO<Data>::convertTheTimeObject(time_t timeObjectDaO)
{
	Key timeInString = db.TimeConversion_time(timeObjectDaO);
	return timeInString;
}

//------------validates if the keylist is empty or not-----
template<typename Data>
inline void DatabaseDAO<Data>::validateKeys(Keys emp)
{
	if (emp.size() == 0)
		std::cout << "No Keys present";
	else
		for (auto item : emp)
			std::cout << "-------->" << item<<"\n";
}

//----------------calls NoSqDb to persists into database
template<typename Data>
typename DatabaseDAO<Data>::Key DatabaseDAO<Data>::convertIntoXml()
{
	
	Key stringOfXml = db.toXml();

	return stringOfXml;

}

template<typename Data>
typename DatabaseDAO<Data>::Keys DatabaseDAO<Data>::rlocate(Key whereParam, Key pattern, Key start_time, Key end_time, Keys listOf)
{
	std::regex regularexp(".*" + pattern + ".*");
	Keys instnce;
	Keys requiredString;
	std::string s;
	Element<Data> temp;
	if (whereParam == "key") {
		if (listOf.size() == 0) {
			
			instnce = db.keys();
			for (Key item : instnce)
			{
				s = item;
				if (std::regex_match(s, regularexp))
				{
					requiredString.push_back(item);
				}

			}
	
			return requiredString;
		}
		else {

			for (Key item : listOf)
			{
				
				s = item;
				if (std::regex_match(s, regularexp))
				{
					requiredString.push_back(item);
				}

			}
			
		}
		

		return requiredString;

	}
	else
		if (whereParam == "name") {
			if (listOf.size() == 0) {
				
				instnce = db.keys();
				for (Key item : instnce)
				{
					temp = db.value(item);
					s = temp.name.getValue();
					if (std::regex_match(s, regularexp))
					{
						requiredString.push_back(item);
					}

				}
				return requiredString;

			}
			else {
				for (Key item : listOf)
				{
					temp = db.value(item);
					s = temp.name.getValue();
					if (std::regex_match(s, regularexp))
					{
						requiredString.push_back(item);
					}	
				}
				return requiredString;
			}
			

		}
		else if (whereParam == "category") {
			if (listOf.size() == 0) {
				
				instnce = db.keys();
				for (Key item : instnce)
				{
					temp = db.value(item);
					s = temp.category.getValue();
					if (std::regex_match(s, regularexp)) 
						requiredString.push_back(item);
				}
				return requiredString;
			}
			else {
				for (Key item : listOf)
				{
					temp = db.value(item);
					s = temp.category.getValue();
					if (std::regex_match(s, regularexp))
						requiredString.push_back(item);
				}
				return requiredString;
			}


		}
		else {
			std::cout << "Provide the correct parameter to query";
		}
	return requiredString;	
}

template<typename Data>
typename DatabaseDAO<Data>::Keys DatabaseDAO<Data>::rqueryForData(Data pattern, Keys listOf)
{
	std::vector<std::string> requiredKeys;
	if (listOf.size() == 0) {
		listOf = db.keys();
	}
	Element<Data> temp;
	Key emp;
	for (auto item : listOf) {
		temp = db.value(item);
		emp = Convert<Data>::toString(pattern);
		std::regex regularexp(".*" + pattern + ".*");
		Key dataInString = Convert<Data>::toString(temp.data.getValue());
		if (std::regex_match(dataInString, regularexp))
			requiredKeys.push_back(item);

	}

	return requiredKeys;
	
}

//-----------------takes file path and sends it to NoSqDb to populate
template<typename Data>
void DatabaseDAO<Data>::convertIntoObj(const Key xmlString,int file) {
	
	if (file = 1) {
		std::ifstream in(xmlString);
		if (!in.good())
			throw(std::exception(("can't open source file " + xmlString).c_str()));
		std::ostringstream out;
		out << in.rdbuf();
		std::string forOpening = std::move(out.str());
		db.fromXml(forOpening);
	}
	else if(file = 0)
	{

		db.fromXml(xmlString);
	}
	else
	{
		std::cout << "Invalid Input";
	}
	Keys storeContents = db.keys();
	for (Key eachElement : storeContents)
	{
		std::cout << eachElement << ":";
		std::cout << db.value(eachElement).show();
	}
	std::cout << "\n\n";
	std::cout << "\n********************<End of Demonstration of persistance of database on command *****************\n\n";
}

//-----------Implements query functionality for the metadata indatabase by doing function overloading
template<typename Data>
typename DatabaseDAO<Data>::Keys DatabaseDAO<Data>::locate(Key whereParam, Key pattern,Key start_time,Key end_time, Keys listOf)
{
	Keys instnce;
	Keys requiredString;
	std::string s;
	Element<Data> temp;
	if (whereParam == "key") {
		if (listOf.size() == 0) {
			
			instnce = db.keys();
			for (Key item : instnce)
			{
				
				s = item;
				if ((s.find(pattern)) != std::string::npos)
				{
					requiredString.push_back(item);
				}

			}
			
			return requiredString;
		}
		else {
			
			for (Key item : listOf)
			{
				
				s = item;
				if ((s.find(pattern)) != std::string::npos)
				{
					requiredString.push_back(item);
				}

			}
			
		}
			

		return requiredString;

	}
	else
	if (whereParam == "name") {
		if (listOf.size() == 0) {
			
			instnce = db.keys();
			for (Key item : instnce)
			{
				temp = db.value(item);
				s = temp.name.getValue();
				if ((s.find(pattern)) != std::string::npos)
				{
					requiredString.push_back(item);
				}

			}
			return requiredString;
			
		}
		else {
			for (Key item : listOf)
			{
				temp = db.value(item);
				s = temp.name.getValue();
				if ((s.find(pattern)) != std::string::npos)
				{
					requiredString.push_back(item);
				}
			}
			return requiredString;
		}
			

	}else if (whereParam == "category"){
		if (listOf.size() == 0) {
			
			instnce = db.keys();
			for (Key item : instnce)
			{
				temp = db.value(item);
				s = temp.category.getValue();
				if ((s.find(pattern)) != std::string::npos)
					requiredString.push_back(item);
			}
			return requiredString;
		}
		else {
			for (Key item : listOf)
			{
				temp = db.value(item);
				s = temp.category.getValue();
				if ((s.find(pattern)) != std::string::npos)
					requiredString.push_back(item);
			}
			return requiredString;
		}


	}
	else if (whereParam == "children") {

		 temp = db.value(pattern);
		std::vector<std::string> childList = temp.children.getValue();
		return childList;


		
	}
	else if (whereParam == "timeStamp")
	{
		time_t s_time = db.TimeConversion_string(start_time.c_str());
		double seconds_s = (double)s_time;
		time_t e_time = db.TimeConversion_string(end_time.c_str());

		instnce = db.keys();
		
		for (Key each : instnce) {
			temp = db.value(each);
			time_t objectsTime = temp.timeDate.getValue();
			double seconds_o = (double)objectsTime;
			if (end_time == "null") {
				time_t current_time = time(&current_time);
				double seconds_c = (double)current_time;
				if ((seconds_s<seconds_o) && (seconds_c >= seconds_o)) {
					requiredString.push_back(each);
				}
			}
			else
			{
				double seconds_end = (double)e_time;
				if ((seconds_s < seconds_o) && (seconds_end > seconds_o)) {
					requiredString.push_back(each);
				}
			}

		}
		return requiredString;

	}
	else {
		std::cout << "provide proper parameters";
	}
	return requiredString;
}
//------------Queries dunction for data specific 
template<typename Data>
inline Element<Data> DatabaseDAO<Data>::getValue_Of(Key oneKey)
{
	Element<Data> temp = db.value(oneKey);
	return temp;
}

template<typename Data>
typename DatabaseDAO<Data>::Keys DatabaseDAO<Data>::queryForData(Data pattern, Keys listOf)
{
	std::vector<std::string> requiredKeys;
	if (listOf.size()==0) {
		listOf = db.keys();
	}		
		Element<Data> temp;
		Key emp;
		for (auto item : listOf) {
			temp = db.value(item); 
			emp = Convert<Data>::toString(pattern);
			Key dataInString = Convert<Data>::toString(temp.data.getValue());
			if ((dataInString.find(emp)) != std::string::npos)
				requiredKeys.push_back(item);

		}
	
	return requiredKeys;
}
//----------Appends the Keylist
template<typename Data>
typename DatabaseDAO<Data>::Keys DatabaseDAO<Data>::unionOfKeys(Keys one, Keys two)
{
	bool flag = true;
	Keys Or;
	for (Key each : one)
		Or.push_back(each);
	for (Key each : two) {
		for (auto duplicationCheck : Or)
		{
			if(duplicationCheck == each)
			{
				flag = false;
			}
			
		}
		if (flag == true)
			Or.push_back(each);
		
	}
	return Or;
	
}



