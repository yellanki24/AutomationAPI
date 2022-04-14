
#include "UI.h"
#include "PartsUtilsUI.h"
#include "MakeWidgetFeature.h"
#include "..\AppLibrary\PartOps.h"
#include "..\Journaling\Journaling.h"


UI::UI()
{

}


void UI::Init()
{

}

void UI::StartGUILoop()
{

	// This is just mimic'ing a simple CAD workflow.
	// We are going to pretend the user makes  part, makes a widget feature, saves the part,
	// and then exits.  And this will stop the GUI loop and lead to exit on main

	//Setup Journaling File
	SetJournalingLangauge(JournalingLanguage::CPP);
	StartJournaling("C:\\Users\\Pavan\\Desktop\\AutomationAPI\\AutomationAPI\\JournaledCPPFileProject\\SampleJournal.cpp");


	PartFile * partFile = MakePartUI("d:\\workdir\\someDir\\SomeName.part");
	AddWidgetFeatureToPartUI(partFile, true, 10);
	SavePartUI(partFile);

	//End Journaling
	EndJournaling();


}