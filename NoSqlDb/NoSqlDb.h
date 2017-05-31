#pragma once
/////////////////////////////////////////////////////////////////////
//  NoSqlDb.h - Key-value pair in Database                         //
//  ver 1.0                                                        //
//                                                                 //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Lenovo , Windows 8.1      			           //
//  Application:   NoSql Database - CIS 687 Project 1              //
//  Author:        Sushanth Suresh SUID:987471535			       //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
It defines two classes No SQL database class and an Element class
*No SQL Database works as a container class implementing an unordereded
map on Heap memory with an instance of Element class as the value with
a unique Key.
* No SQL class defines operations such as editiing, deleting, 
persisting of values into an XML file and extracting the values from 
XML.
These two classes use Template functionalities

Public Interface:
=================

TimeConversion_string ()  // Member function that takes time format into string
TimeConversion_time()     //Member function that takes string format into time
getChildren()             // Member function that gives the the dependent keys
editData()                // Overloaded member function that edit values
delete_keys();            // Member function that deletes the keys and dependencies
toXml()                   //Member function that persists the values into an XML
fromXml()                 //Member function that getting the values from the XML file
Keys()                    // Member function that gives the keys in the Database
save()                    //Member function saves elememt in the database
value()                   //Member function Gets the value

Element Class contains

name, category, description		// Member variables of type Property
childrenKeys					//Member variable Vector of strings holding dependent Keys
timeDate						//Member variable which holds the time of creation
data 							//Member variable templatised on Data to hold the value

Build Process:
==============
Required files
- Cppproperties.h, Convert.h,
- XmlDocument.h, XmlElement.h,
- StrHelper.h
- time.h


Build commands (either one)

- devenv Project1_Sushanth.sln


Maintenance History:
====================
ver 1.0 : 07 Feb 17
- first release
*/

#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include "../CppProperties/CppProperties.h"
#include "../XMLnew/XmlDocument/XmlDocument.h"
#include "../XMLnew/XmlElement/XmlElement.h"
#include "../StrHelper.h"
#include "../Convert/Convert.h"
#include <time.h>
#include <fstream>

/////////////////////////////////////////////////////////////////////
// Element class represents a data record in our NoSql database
// - in our NoSql database that is just the value in a key/value pair
// - it needs to store child data, something for you to implement
//
template<typename Data>
class Element
{
public:
	
  using Name = std::string;
  using Category = std::string;
  using TimeDate = std::time_t;
  using Childrens = std::vector<std::string>;
  using Description = std::string;


  Property<Name> name;            // metadata
  Property<Category> category;    // metadata
  Property<TimeDate> timeDate;    // metadata
  Property<Childrens> children;    //metadata
  Property<Description> description; //metadata
  Property<Data> data;            // data
  
  
  std::string show();
};


template<typename Data>
std::string Element<Data>::show()
{
  // show children when you've implemented them

  std::ostringstream out;
  out.setf(std::ios::adjustfield, std::ios::left);
  //std::cout << typeof(out);
  out << "\n    " << std::setw(8) << "name"     << " : " << name;
  out << "\n    " << std::setw(8) << "category" << " : " << category;
  out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
  out << "\n    " << std::setw(8) << "data"     << " : " << data;
  out << "\n    " << std::setw(8) << "Description " << " : " << description;
  
  
  Childrens child = children;
  if (int(child.size()) <= 0)
  {
	  out << "\n      " << std::setw(8) << "Dependent children " << " : " << "Null";

  }
  else
  {
	  for (auto display : child)
	  {
		  out << "\n       " << std::setw(8) << "Dependent children " << " : " << display ;

	  }
  }
  
  out << "\n";
  return out.str();
}


/////////////////////////////////////////////////////////////////////
// NoSqlDb class is a key/value pair in-memory database
// - stores and retrieves elements
// - you will need to add query 
//   That should probably be another class that uses NoSqlDb
//
using namespace XmlProcessing;
using SPtr = std::shared_ptr<AbstractXmlElement>;
template<typename Data>
class NoSqlDb
{
public:
  using Key = std::string;
  using ToBeModified = std::string;
  using Keys = std::vector<Key>;
  using xml = std::string;
  using listOf = std::vector<xml>;

  //TimeConvesion functions
  time_t TimeConversion_string(const char* timeDatestring);
  Key TimeConversion_time(time_t timeObject);
  //Qury functions
  std::vector<std::string> getChildren(Key key);

  void editData(Key, std::string, std::string);
  void editData(Key key, Data data);
  void editData(Key key, const std::string e, std::string dat, std::string op);
  void editData(Key key, std::time_t);
  // deleting functions
  bool delete_keys(Key);
  void deleteinchildren(Key key);
  //Persisting to xml
  std::string toXml();

  //Creating Objects from a file
  void fromXml(const xml xmlString);
  Keys keys();
  bool save(Key key, Element<Data> elem);
  Element<Data> value(Key key);
  size_t count();
private:
  using Item = std::pair<Key, Element<Data>>;
  std::unordered_map<Key,Element<Data>> store; 
};
//----------takes string as input and creates a element object and populates the database---------------
template<typename Data>
void NoSqlDb<Data>::fromXml(const xml xmlString)
{
	Element<Data> valueObject;
	std::string Key_value;
	try
	{
		XmlDocument doc(xmlString, XmlDocument::str);
		std::vector<SPtr> desc = doc.descendents("record").select();
		int count = desc.size();
		int i = 0;
		while (i != count) {

			//key
			Key_value = desc[i]->children()[0]->children()[0]->value();
			Key_value = trim(Key_value);
			//name
			std::string name_value = desc[i]->children()[1]->children()[0]->value();
			name_value = trim(name_value);
			valueObject.name = name_value;
			//Description
			std::string description_value = desc[i]->children()[2]->children()[0]->value();
			description_value = trim(description_value);
			valueObject.description = description_value;
			//Category
			std::string c_value = (desc[i]->children()[3]->children()[0]->value());
			c_value = trim(c_value);
			valueObject.category = c_value;
			//timeDate
			std::time_t t_value = TimeConversion_string(desc[i]->children()[4]->children()[0]->value().c_str());
			//t_value = trim(t_value);
			valueObject.timeDate = t_value;
			//ActualData
			std::string data_value = desc[i]->children()[5]->children()[0]->value();
			data_value = trim(data_value);
			valueObject.data = Convert<Data>::fromString(data_value);
			//children

			std::vector<std::string> childList;
			std::vector<SPtr> childrens = desc[i]->children()[6]->children();
			for (SPtr child : childrens)
			{
				std::string listc = trim(child->children()[0]->value());
				childList.push_back(listc);

			}
			valueObject.children = childList;
			store[Key_value] = valueObject;
			i++;
		}

	}
	catch (const std::exception& e)
	{
		std::cout << "exception:"<<e.what();
	}
	
}
//---------------Puts the values of the database into the XML-----------------------------
template<typename Data>
std::string NoSqlDb<Data>::toXml()
{
	xml theDocument;
	XmlDocument doc;
	try
	{

	

	listOf chil;
	listOf allKeys = keys();
	SPtr pRoot = makeTaggedElement("Database");
	doc.docElement() = pRoot;
	for (xml each : allKeys) {
		Element<Data> x = value(each);
		SPtr dElement = makeTaggedElement("record");
		pRoot->addChild(dElement);

		//Keys
		SPtr pKeyElement = makeTaggedElement("keyofValues");
		dElement->addChild(pKeyElement);
		SPtr pKeyText = makeTextElement(x.name);
		pKeyElement->addChild(pKeyText);

		//Name
		SPtr pNameElement = makeTaggedElement("name");
		dElement->addChild(pNameElement);
		SPtr pNameText = makeTextElement(x.name);
		pNameElement->addChild(pNameText);

		//description
		SPtr pDescriptionElement = makeTaggedElement("description");
		dElement->addChild(pDescriptionElement);
		SPtr pdescriptionText = makeTextElement(x.description);
		pDescriptionElement->addChild(pdescriptionText);

		//category
		SPtr pCategoryElement = makeTaggedElement("category");
		dElement->addChild(pCategoryElement);
		SPtr pCategoryText = makeTextElement(x.description);
		pCategoryElement->addChild(pCategoryText);

		//timeDate
		SPtr pTimeElement = makeTaggedElement("timeDate");
		dElement->addChild(pTimeElement);
		std::string timeConvertedtostring = TimeConversion_time(x.timeDate);
		SPtr pTimeText = makeTextElement(timeConvertedtostring);
		pTimeElement->addChild(pTimeText);

		//Actual Data
		SPtr pDataElement = makeTaggedElement("ActualData");
		dElement->addChild(pDataElement);
		std::string pPitext = Convert<Data>::toString(x.data);
		SPtr pTextdata = makeTextElement(pPitext);
		pDataElement->addChild(pTextdata);

		//children
		chil = getChildren(x.name);
		int count = chil.size();
		int i = 0;
		SPtr pChildElement = makeTaggedElement("children");
		dElement->addChild(pChildElement);
		while (i != count) {
			xml child = chil[i];
			SPtr pchildtag = makeTaggedElement("child");
			pChildElement->addChild(pchildtag);
			SPtr pchildText = makeTextElement(child);
			pchildtag->addChild(pchildText);
			i++;
		}
	}
	std::cout << "\n\nPersisting the database into writedatabase.xml file present in the location ../xmlfiles/writedatabase.xml\n";
		theDocument = doc.toString();
		std::ofstream input_file("../xmlfiles/writedatabase.xml");
		input_file << theDocument;
		input_file.close();
		
	}
	catch (const std::exception& e)
	{
		std::cout << "exception:" << e.what();
	}
	
	return theDocument;
}

//----------------------------- Editing name, category, description, timedate of the element----------
template<typename Data>
void NoSqlDb<Data>::editData(Key key,std::string e, std::string dat) {
	bool flag = false;

	Element<Data> elem = value(key);
	if (e == "name") {
		elem.name = dat;
		flag = true;
	}
	else if (e == "category") {
		elem.category = dat;
		flag = true;
	}
	else if (e == "description") {
		elem.description = dat;
		flag = true;
	}
	else
	{
		std::cout << "provide parameter";
	}

	if (flag) {
		
		store[key] = elem;
		
	}
	else {
		std::cout << "provide parameter";
	}
	
}

//---------------------- Editing the childrens----------------------------------------------
template<typename Data>
void NoSqlDb<Data>::editData(Key key, const std::string e, std::string dat, std::string op) {
	if (e == "children") {
		Element<Data> elem = value(key);
		std::vector<std::string> childList = getChildren(key);
		std::vector<std::string>::iterator it;
		if ((it = std::find(childList.begin(), childList.end(), dat)) != childList.end()) {
			if (op == "add") {
				std::cout << "Child already present";
				
			}
			else if (op == "remove") {
				childList.erase(it);
				elem.children = childList;
				
				store[key] = elem;
			
			}

		}
		else
		{
			if (op == "add") {
				childList.push_back(dat);
				elem.children = childList;
				
				store[key] = elem;
				
			}
			else if (op == "remove") {
				std::cout << "Child already not present";
				
			}
		}
		
	}
	else
	{
		std::cout << "provide parameter as children";
	}
}
//---------------------Editing the time stamp of the element taking its key----------------
template<typename Data>
void NoSqlDb<Data>::editData(Key key, std::time_t timeStamp)
{
	Element<Data> temp = value(key);
	temp.timeDate = timeStamp;
	store[key] = temp;
	
}

//----------------------Editing data of the element taking its key--------
template<typename Data>
void NoSqlDb<Data>::editData(Key key, Data dat) {
	Element<Data> elem;
	if (store.find(key) != store.end()) {
		elem = value(key);
		elem.data = dat;
		
		store[key] = elem;
		
	}
	else {
		std::cout << " No Element by that name";
	}
	

}

//----------------Erase an element taking its Key----------------------
template<typename Data>
bool NoSqlDb<Data>::delete_keys(Key key){
	
	if (store.find(key) != store.end()) {
		
		deleteinchildren(key);
		store.erase(key);
		return true;
	}
	else {
		std::cout << "Key not found";
		return false;
	}
}

//------------------delete the asociated keys in other element---------------
template<typename Data>
void NoSqlDb<Data>::deleteinchildren(Key key) {
	try
	{

	
	Keys allKeys = keys();
	Element<Data> temp;
	std::vector<std::string>::iterator it;
	for (std::string allRecords : allKeys) {
		temp = value(allRecords);		
		std::vector<std::string> childList = temp.children.getValue();
	
		if (childList.size() == 0) {
			continue;
		}else if ((it = std::find(childList.begin(), childList.end(), key)) != childList.end()) {
			childList.erase(it);
			temp.children = childList;
			save(allRecords, temp);
			
		}

	}
	}
	catch (const std::exception& e)
	{
		std::cout << "exception thrown " << e.what();
	}
	
	
}
//-----------Returns all the Keys in the database-----------------
template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
  Keys keys;
  for (Item item : store)
  {
     keys.push_back(item.first);
  }
  return keys;
}
//-----------Adds an Element into the database---------------------
template<typename Data>
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
{
	time_t createdtime = time(&createdtime);
	elem.timeDate = createdtime;
  if(store.find(key) != store.end())
    return false;
  store[key] = elem;
  return true;
}
//--------------------Gets the Element using its associated Key-----------
template<typename Data>
Element<Data> NoSqlDb<Data>::value(Key key)
{
  if (store.find(key) != store.end())
    return store[key];
  return Element<Data>();
}
//------------------Counts the number of keys-----------------------
template<typename Data>
size_t NoSqlDb<Data>::count()
{
  return store.size();
}
//--------------takes time in string and converts into time format----------------
template<typename Data>
time_t NoSqlDb<Data>::TimeConversion_string(const char* timeDatestring)
{
	struct tm timeVariable = { 0 };
	int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;
	sscanf_s(timeDatestring, "%d-%d-%d:-:%d:%d:%d", &year, &month, &day, &hour, &min, &sec);
	timeVariable.tm_year = year - 1900;
	timeVariable.tm_mon = month - 1;
	timeVariable.tm_mday = day;
	timeVariable.tm_hour = hour;
	timeVariable.tm_min = min;
	timeVariable.tm_sec = sec;

	time_t timeObject = mktime(&timeVariable);
	return timeObject;
}
//--------------takes time in time and converts into string format----------------

template<typename Data>
typename NoSqlDb<Data>::Key NoSqlDb<Data>::TimeConversion_time(time_t timeObject)
{
	struct tm  time_struct = {};
	char timeVariable[80];
	localtime_s(&time_struct, &timeObject);
	strftime(timeVariable, sizeof(timeVariable), "%Y-%m-%d:-:%X", &time_struct);
	std::string timeInString(timeVariable);
	return timeInString;
}

// --------------------------get the children list------------------------------------
template<typename Data>
std::vector<std::string> NoSqlDb<Data>::getChildren(Key key)
{
	Element<Data> temp = value(key);
	std::vector<std::string> childList = temp.children;
	return childList;
}