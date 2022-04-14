#include "Session.h"
#include "Part.h"
#include "..\Core\Core.h"
#include "..\AppLibrary\PartOps.h"





AutomationAPI::Session* AutomationAPI::Session::GetSession()
{
	static Session instance;
	bool authorized = true;

	if (!authorized || initializeProduct() != 0)
	{
		throw new std::exception("Not authorized to get Session, purchase license");
	}

	return &instance;
	
}

AutomationAPI::Part* AutomationAPI::Session::MakePart(std::string partFilePath)
{
	PartFile * partFile =  Journaling_MakePart(partFilePath);

	int guid = partFile->GetGuid();

	return AutomationAPI::Part::CreatePart(guid);
}


AutomationAPI::Session::~Session()
{
	shutdownProduct();
}

