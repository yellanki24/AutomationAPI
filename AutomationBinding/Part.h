#pragma once

#include "AutomationBinding.h"
#include <string>


namespace AutomationAPI
{
	class AUTOMATIONBINDING_API Part
	{
		public :

			/**
			Saves the Part File.
			*/
			void Save();

			/**
			Makes a Widget Feature
			*/
			void MakeWidgetFeature(bool option1, int values);

			static Part* CreatePart(int guid);

			virtual ~Part();

		private:
			Part();
			Part(int guid);
			int m_guid;

	};

}
