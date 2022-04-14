#include "Part.h"
#include "..\Core\GuidObject.h"
#include "..\AppLibrary\PartOps.h"

using namespace AutomationAPI;

void AutomationAPI::Part::Save()
{
	PartFile* part = dynamic_cast<PartFile*>(GuidObjectManager::GetGuidObjectManager().GetObjectFromGUID(m_guid));
	if (part == nullptr)
	{
		throw new std::exception("not able to retrieve Part Object");
	}
	else
	{
		Journaling_Part_Save(part);
	}

}

void AutomationAPI::Part::MakeWidgetFeature(bool option1, int values)
{
	PartFile* part = dynamic_cast<PartFile*>(GuidObjectManager::GetGuidObjectManager().GetObjectFromGUID(m_guid));
	if (part == nullptr)
	{
		throw new std::exception("not able to retrieve Part Object");
	}
	else
	{
		Journaling_Part_MakeWidgetFeature(part, option1, values);
	}
}

Part* AutomationAPI::Part::CreatePart(int guid)
{
	// We should check the guid being passed in, as this is public
	// but that is for another day

	return new Part(guid);
}

AutomationAPI::Part::Part(int guid)
{
	m_guid = guid;
}

AutomationAPI::Part::~Part()
{

}

