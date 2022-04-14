#include "PartsUtilsUI.h"
#include <iostream>

using namespace std;
void SavePartUI(PartFile* partFile)
{
	cout << "SavePartUI was called" << endl;
	
	Journaling_Part_Save(partFile);

	//SavePart(partFile);
}

PartFile* MakePartUI(std::string s)
{
	cout << "MakePartUI was called with args " << s << endl;

	return Journaling_MakePart(s);

	//return MakePart(s);


}
