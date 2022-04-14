#include <iostream>
#include "..\AutomationBinding\Session.h"
#include "..\AutomationBinding\Part.h"


int NotMain()
{
    std::cout << "Hello World!\n";

    AutomationAPI::Session* mySession = AutomationAPI::Session::GetSession();

    AutomationAPI::Part* myPart = mySession->MakePart("d:\\workdir\\someDir\\SomeName.part");
    myPart->MakeWidgetFeature(true, 10);
    myPart->Save();


    delete myPart;

    return 0;
}