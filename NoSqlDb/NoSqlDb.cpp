/////////////////////////////////////////////////////////////////////
// NoSqlDb.cpp - key/value pair in-memory database                 //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////

#include "NoSqlDb.h"

#include <iostream>

using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

int main()
{

  std::cout << "\n  Demonstrating NoSql Helper Code";
  std::cout << "\n =================================\n";

  std::cout << "\n  Creating and saving NoSqlDb elements with string data";
  std::cout << "\n -------------------------------------------------------\n";

  NoSqlDb<StrData> db;

  Element<StrData> elem1;
 
  elem1.name = "elem1";
  elem1.category = "test";  
  elem1.data = "elem1's StrData";
  elem1.description = " Elemen1 in the test category";

  std::vector<std::string> keysForElem1;
  keysForElem1.push_back("elem2");
  keysForElem1.push_back("elem3");
  elem1.children = keysForElem1;

  db.save(elem1.name, elem1);

  Element<StrData> elem2;
  elem2.name = "elem2";
  elem2.category = "test";
  elem2.data = "elem2's StrData";
  elem2.description = " Element2 in the test category";
  std::vector<std::string> keysForElem2;
  keysForElem2.push_back("elem1");
  elem2.children = keysForElem2;
  db.save(elem2.name, elem2);

  db.editData("elem2", "Childrens", "elem200","add");
  db.editData("elem2", "Childrens", "elem32", "add");
  db.editData("elem2", "Childrens", "elem55", "add");
  
  
  Element<StrData> elem3;
  elem3.name = "elem3";
  elem3.category = "test";
  elem3.data = "elem3's StrData";
  elem3.description = "Element3 in the test category";
  std::vector<std::string> keysForElem3;
  keysForElem3.push_back("elem2");
  elem3.children = keysForElem3;
 
  db.save(elem3.name, elem3);
  std::cout << "\n  Converting to Xml ";
  std::cout << "\n ------------------------------------------\n";
  Key xmlIllus = db.toXml();
  std::cout << " \n In Xml Format \n" << xmlIllus;
  std::cout << "\n \n";



  db.fromXml(xmlIllus);
  std::cout << "\n  Displaying all the records in DB";
  std::cout << "\n ------------------------------------------\n";
  Keys storeContents = db.keys();
	for (Key eachElement : storeContents)
	{
		std::cout << "\n  " << eachElement << ":";
		std::cout << db.value(eachElement).show();
	}
	std::cout << "\n\n";

  std::cout << "\n  Querying elements for getting the children where key=elem3";
  std::cout << "\n ------------------------------------------\n";
  Keys togetchildren = db.getChildren("elem3");
  for (auto child : togetchildren)
	  std::cout << "\n" << child << "\n";

  std::cout << "\n  Editing name";
  std::cout << "\n ------------------------------------------------------------------------------------------------------------------\n";
  db.editData("elem1", "name", "sushanth");
  std::cout << db.value("elem1").show();
  std::cout << "\n  Editing category";
  std::cout << "\n ------------------------------------------------------------------------------------------------------------------\n";
  db.editData("elem1", "category", "sushanth");
  std::cout << db.value("elem1").show();
  std::cout << "\n  Editing children";
  std::cout << "\n ------------------------------------------------------------------------------------------------------------------\n";
  db.editData("elem1", "children", "sushanth","add");
  std::cout << db.value("elem1").show();
  std::cout << "\n  Editing data";
  std::cout << "\n ------------------------------------------------------------------------------------------------------------------\n";
  db.editData("elem1", "name");
  std::cout << db.value("elem1").show();
  std::cout << "\n  Editing timeStamp";
  std::cout << "\n ------------------------------------------------------------------------------------------------------------------\n";
  
  time_t setTime = db.TimeConversion_string("2017 - 02 - 08:-: 02 : 01 : 47");
 
  db.editData("elem1", setTime);
  std::cout << db.value("elem1").show();
  std::string setStTime = db.TimeConversion_time(setTime);
  std::cout << "\n-----------time demonstraion-----";
  std::cout << setStTime;
  std::cout << "\n  deleting keys";
  std::cout << "\n ------------------------------------------------------------------------------------------------------------------\n";
  db.delete_keys("elem2");
 
  std::cout << "\n  Retrieving elements from NoSqlDb<string>";
  std::cout << "\n ------------------------------------------\n";

  std::cout << "\n  size of db = " << db.count() << "\n";
  Keys keys = db.keys();
  for (Key key : keys)
  {
    std::cout << "\n  " << key << ":";
    std::cout << db.value(key).show();
  }
  std::cout << "\n\n";

  std::cout << "\n  Creating and saving NoSqlDb elements with int data";
  std::cout << "\n ----------------------------------------------------\n";

  NoSqlDb<intData> idb;

  Element<intData> ielem1;
  ielem1.name = "elem1";
  ielem1.category = "test";
  ielem1.data = 1;
  ielem1.description = " Elemen1 in the test category for integer database";

  std::vector<std::string> ikeysForElem1;
  ikeysForElem1.push_back("ielem2");
  ikeysForElem1.push_back("ielem3");
  ielem1.children = ikeysForElem1;

  idb.save(ielem1.name, ielem1);

  Element<intData> ielem2;
  ielem2.name = "elem2";
  ielem2.category = "test";
  ielem2.data = 2;

  ielem2.description = " Element2 in the test category for integer database";
  std::vector<std::string> ikeysForElem2;
  ikeysForElem2.push_back("ielem1");
  ielem2.children = ikeysForElem2;

  idb.save(ielem2.name, ielem2);

  Element<intData> ielem3;
  ielem3.name = "elem3";
  ielem3.category = "test";
  ielem3.data = 3;

  idb.save(ielem3.name, ielem3);
 
  
  Element<intData> ielem4;
  ielem3.name = "elem4";
  ielem3.category = "test";
  ielem3.data = 4;
  ielem3.description = "Element3 in the test category";
  std::vector<std::string> ikeysForElem3;
  ikeysForElem3.push_back("ielem2");
  ielem3.children = ikeysForElem3;

  idb.save(ielem3.name, ielem3);
  std::cout << "\n  Editing data";
  std::cout << "\n ------------------------------------------------------------------------------------------------------------------\n";
  idb.editData("elem1", 533);
 
  std::cout << "\n  Retrieving elements from NoSqlDb<int>";
  std::cout << "\n ---------------------------------------\n";

  std::cout << "\n  size of idb = " << idb.count() << "\n";
  Keys ikeys = idb.keys();
  for (Key key : ikeys)
  {
    std::cout << "\n  " << key << ":";
    std::cout << idb.value(key).show();
  }
  std::cout << "\n\n";
  getchar();
}