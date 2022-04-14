#include <iostream>
#include "..\AutomationBinding\Session.h"
#include "..\AutomationBinding\Part.h"

int main()
{
    std::cout << "Hello World!\n";
    AutomationAPI::Session* mySession = AutomationAPI::Session::GetSession();
AutomationAPI::Part * Part1 = mySession->MakePart("d:\\workdir\\someDir\\SomeName.part");
Part1->MakeWidgetFeature(true,10);
Part1->Save();

}
