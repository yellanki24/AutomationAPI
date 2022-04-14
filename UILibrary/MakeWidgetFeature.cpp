#include "MakeWidgetFeature.h"
#include <iostream>
#include "../AppLibrary/PartOps.h"

using namespace std;

void AddWidgetFeatureToPartUI(PartFile* partFile, bool option1, int values)
{
	cout << "AddWidgetFeatureToPartUI was called " << option1 << " " << values << endl;
	Journaling_Part_MakeWidgetFeature(partFile, option1, values);
	//MakeWidgetFeature(partFile, option1, values);


}
