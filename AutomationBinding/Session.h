#pragma once

#include "AutomationBinding.h"
#include <string>



namespace AutomationAPI
{
	class Part;
	class AUTOMATIONBINDING_API Session
	{
		public :
			static Session* GetSession();

			/*
			Generates the Part File at the path specificed
			*/
			Part* MakePart(std::string partFilePath);
			
			

		private:
			Session() = default;
			virtual ~Session();
			Session(const Session&) = delete;
			Session& operator=(const Session&) = delete;
	};

}


