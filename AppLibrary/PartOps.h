#pragma once
#include "AppLibrary.h"
#include <string>
#include "..\Core\GuidObject.h"



class APPLIBRARY_API PartFile : public GuidObject
{
	public:
		static PartFile* CreatePartFile(std::string partFilePath);
		void SavePart();
		void MakeWidgetFeature(bool option1, int values);

	private:
		PartFile(std::string partFilePath, int guid);
		std::string m_partFilePath;
};

extern APPLIBRARY_API PartFile* Journaling_MakePart(std::string);

extern APPLIBRARY_API void Journaling_Part_Save(PartFile* partFile);

extern APPLIBRARY_API void Journaling_Part_MakeWidgetFeature(PartFile* partFile, bool option1, int values);

