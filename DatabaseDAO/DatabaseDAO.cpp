#include "DatabaseDAO.h"
#include "../NoSqlDb/NoSqlDb.h"

#include <iostream>
#include <time.h>
using StrData = std::string;
using Keys = std::vector<StrData>;
using timeThin = std::time_t;
using IntData = int;




int main() {
	try
	{

	

std::cout << "\n--------------<Requirement 11><Test Executive Demonstrating all the Requirements >------------------------------------------------------\n\n";


std::cout << "\n Contents of database populated as project structure using the file present in ../xmlfiles/project1Structure.xml";
	DatabaseDAO<StrData> prjStr("../xmlfiles/project1Structure.xml");

	Keys childList;
	timeThin timeStamp = 0;


	std::cout << "\n --------------<Requirement 4><Editing an Elements data >----------------------------";
	std::cout << "\n Before:-\n";
	prjStr.show({ "Deleting.h" });
	prjStr.editElements("Deleting.h", "elem1's changed");
	std::cout << "\n After:-\n";
	prjStr.show({ "Deleting.h" });
	std::cout << "\n********************<End of Demonstration of Editing to the data >*************************************\n\n";


	std::cout << "\n---------------<Requirement 4><Editing an Elements category>------------------------";
	std::cout << "\n Before:-\n";
	prjStr.show({ "NoSqlDb.h" });
	prjStr.editElements("NoSqlDb.h", "category", "changed category");
	std::cout << "\n After:-\n";
	prjStr.show({ "NoSqlDb.h" });
	std::cout << "\n********************<End of Demonstration of Editing to the Elements category >*************************************\n\n";


	std::cout << "\n---------------<Requirement 4><Editing an Elements Description>------------------------";
	std::cout << "\n Before:-\n";
	prjStr.show({ "NoSqlDb.h" });
	prjStr.editElements("NoSqlDb.h", "description", "Its implements unordered map ");
	std::cout << "\n After:-\n";
	prjStr.show({ "NoSqlDb.h" });
	std::cout << "\n********************<End of Demonstration of Editing to the Elements Description >*************************************\n\n";

	std::cout << "\n --------------<Requirement 4><Adding a child relation to an Elements  >----------------------------";
	std::cout << "\n Before:-\n";
	prjStr.show({ "Convert.h" });
	prjStr.editElements("Convert.h", "children", "Deleting", "add");
	std::cout << "\n After:-\n";
	prjStr.show({ "Convert.h" });
	std::cout << "\n********************<End of Demonstration of Adding a child relation an Elements >*************************************\n\n";
	std::cout << "\n --------------<Deleting a child relation to an Elements  >----------------------------";
	std::cout << "\n Before:-\n";
	prjStr.show({ "Convert.h" });
	prjStr.editElements("Convert.h", "children", "Deleting", "remove"); //the fourth argument should be either "add" or "remove"
	std::cout << "\n After:-\n";
	prjStr.show({ "Convert.h" });
	std::cout << "\n********************<End of Demonstration of Deleting a child relation an Elements >*************************************\n\n";
	std::cout << "\n---------------<Requirement 4><Editing an Elements timestamp >------------------------";
	std::cout << "\n Before:-\n";
	prjStr.show({ "DatabaseDAO.h" });
	time_t curr = time(&curr);
	prjStr.editElements("DatabaseDAO.h", curr);
	std::cout << "\n After:-\n";
	prjStr.show({ "DatabaseDAO.h" });
	std::cout << "\n********************<End of Demonstration of Editing an Elements timestamp  >*************************************\n\n";

	std::cout << "\n <Requirement 7.1> Demostrating Querying for a value of specific Key";
	std::cout << "\n---------------------------------------------------------\n";
	Element<StrData> temp = prjStr.getValue_Of("XmlDocument.h");
	std::cout << temp.show();
	std::cout << "\n********************<End of Demonstration of  Querying for a value of specific Key>*************************************\n\n";

	std::cout << "\n---------------<Requirement 7.2><Querying for the children of a specific Key >------------------------\n";
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "\n The keys  are:\n";
	Keys returnedKey = prjStr.locate("children", "NoSqlDb.h");
	prjStr.validateKeys(returnedKey);
	std::cout << "\n********************<End of Demonstration of Querying for the children of a specific Key>*************************************\n\n";

	std::cout << "\n  <Requirement 7.3>Demostrating Querying for matching Key = .h in which defaults in all keys";
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "\n The keys are:\n";
	 returnedKey = prjStr.locate("key", ".h");
	prjStr.validateKeys(returnedKey);

	std::cout << "\n  <Requirement 7.3>Demostrating Querying for matching Key = .h which defaults in all keys using REGULAR Expression";
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "\n The keys  are:\n";
	returnedKey = prjStr.rlocate("key", ".h");
	prjStr.validateKeys(returnedKey);

	std::cout << "\n********************<End of Demonstration of  Querying for Key= .h>*************************************\n\n";

	std::cout << "\n  <Requirement 7.4>Demostrating Querying for matching name = DAO ";
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "\n The keys  are:\n";
	returnedKey = prjStr.locate("name", "DAO");
	prjStr.validateKeys(returnedKey);
	

	std::cout << "\n  <Requirement 7.4>Demostrating Querying for matching name = DAO using REGULAR EXPRESSION ";
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "\n The keys  are:\n";
	returnedKey = prjStr.rlocate("name", "DAO");
	prjStr.validateKeys(returnedKey);
	std::cout << "\n********************<End of Demonstration of  Querying for name= DAO>*************************************\n\n";


	std::cout << "\n  <Requirement 7.5>Demostrating Querying for matching category = Properties ";
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "\n The keys are:\n";
	returnedKey = prjStr.locate("category", "Properties");
	prjStr.validateKeys(returnedKey);

	std::cout << "\n  <Requirement 7.5>Demostrating Querying for matching category = Properties using Regular Expression";
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "\n The keys are:\n";
	returnedKey = prjStr.rlocate("category", "Properties");
	prjStr.validateKeys(returnedKey);
	std::cout << "\n********************<End of Demonstration of  Querying for category = Properties>*************************************\n\n";

	std::cout << "\n  <Requirement 7.6>Demostrating Querying for matching data = CppProperties.cpp; ";
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "\n  The keys are:\n";
	returnedKey = prjStr.queryForData("CppProperties.cpp;");
	prjStr.validateKeys(returnedKey);
	std::cout << "\n  <Requirement 7.6>Demostrating Querying for matching data = CppProperties.cpp; using Regular Expression";
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "\n  The keys are:\n";
	returnedKey = prjStr.rqueryForData("CppProperties.cpp;");
	prjStr.validateKeys(returnedKey);

	std::cout << "\n********************<End of Demonstration of  Querying for data = Data>*************************************\n\n";


	std::cout << "\n  <Requirement 7.7>Demostrating Querying for timestamp from 2017 - 02 - 08:-: 02 : 01 : 47 and 2017 - 02 - 08:-: 02 : 01 : 47 ";
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "\nwhen Only start time is given\n";
	std::cout << "\n  The keys are:\n";
	returnedKey = prjStr.locate("timeStamp","null", "2017-02-08:-:02:01:47");
	prjStr.validateKeys(returnedKey);

	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "\nwhen both start time and end time is given\n";
	std::cout << "\n  The keys are:\n";
	returnedKey = prjStr.locate("timeStamp", "null","2017-02-08:-:02:01:47","2017-03-10:-:23:01:47");
	prjStr.validateKeys(returnedKey);
	std::cout << "\n********************<End of Demonstration of  Querying for timeStampwith the satrting date>*****************\n\n";


	std::cout << "\n  <Requirement 8>Demostrating Querying for the same kinds of queries in integer database where name = e and category = test";
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "\n  The keys are:\n";
	Keys q1 = returnedKey = prjStr.locate("name", "e");
	returnedKey = prjStr.locate("category", "test", "null", "null", q1);
	prjStr.validateKeys(returnedKey);
	std::cout << "\n********************<End of Demonstration of  Compound Queryies *****************\n\n";

	std::cout << "\n  <Requirement 8>Demostrating Querying for union of queries in integer database where name = e or category = test";
	std::cout << "\n  The keys are:\n";
	q1 = returnedKey = prjStr.locate("name", "e");
	Keys q2 = prjStr.locate("category", "test");
	returnedKey = prjStr.unionOfKeys(q1, q2);
	prjStr.validateKeys(returnedKey);

	std::cout << "\n********************<End of Demonstration of  Union Queryies *****************\n\n";
	std::cout << "\n--------------<Requirement 3><Demonstration of Adding to the database >--------------------------------";
	childList._Pop_back_n(childList.size());
	childList.push_back("elem2");
	childList.push_back("elem4");
	prjStr.createElement("elem4", "elem4", "Developer", "elem4's Description", timeStamp, childList, "elem4's Data");
	childList.pop_back();
	prjStr.createElement("elem5", "elem5forKeys", "test", "elem5's Description", timeStamp, childList, "elem5's Data");
	prjStr.show({ "elem4","elem5" });
	std::cout << "\n********************<End of Demonstration of Adding to the database >*************************************\n\n";
	std::cout << "\n---- <Requirement 3> Demostrating Deletion of a Key deleating";
	prjStr.deleteKey("elem4");
	prjStr.deleteKey("elem5");
	prjStr.deleteKey("Deleting.h");
	std::cout << "\n********************<End of Demonstration of deleting the key *****************\n\n";

	std::cout << "\n-----<Requirement 5>Demaonstrating persistance of database on command----------\n";
	StrData pro = prjStr.convertIntoXml();
	std::cout << "\n\n" << pro;
	std::cout << "\n----------------End of xml database ----------\n";
	std::cout << "\n--------------<End of Test Executive Demonstrating all the Requirements >----------------------------------------\n\n";
	
	}
	catch (...)
	{
		std::cout << "exception thrown";
	}
}