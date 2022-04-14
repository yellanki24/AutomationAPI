#pragma once
#include "Core.h"

class CORE_API GuidObject
{
	public :
		GuidObject(int guid);
		

		int GetGuid();


		virtual ~GuidObject();

	private:
		GuidObject() = delete;
		int m_guid;

};

class CORE_API GuidObjectManager
{
	public:
		static GuidObjectManager& GetGuidObjectManager();

		GuidObject* GetObjectFromGUID(int guid);
		void SetObjectFromGUID(int guid, GuidObject* objectToStore);

	private:
		GuidObjectManager() = default;
		~GuidObjectManager() = default;
		GuidObjectManager(const GuidObjectManager&) = delete;
		GuidObjectManager& operator=(const GuidObjectManager&) = delete;

};

