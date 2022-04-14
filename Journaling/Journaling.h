// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the JOURNALING_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// JOURNALING_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef JOURNALING_EXPORTS
#define JOURNALING_API __declspec(dllexport)
#else
#define JOURNALING_API __declspec(dllimport)
#endif


#include <string>
#include <vector>
#include "..\Core\GuidObject.h"
// This class is exported from the dll
//class JOURNALING_API CJournaling {
//public:
//	CJournaling(void);
//	// TODO: add your methods here.
//};

//extern JOURNALING_API int nJournaling;

//JOURNALING_API int fnJournaling(void);

class JournalCallParamData
{
	public:
		enum class ParameterMetaType
		{
			INPUT,
			OUTPUT,
			RETURN
		};

		enum class ParameterBasicType
		{
			STRING,
			BOOLEAN,
			INTEGER,
			NOT_BASIC
		};

		virtual void Journal() = 0;

	protected:
		JournalCallParamData(std::string paramName,
			ParameterMetaType paramType, ParameterBasicType parameterBasicType);
		JournalCallParamData(std::string paramName, ParameterMetaType paramType,
			std::string className);

		JournalCallParamData() = delete;
		JournalCallParamData(const JournalCallParamData&) = delete;
		JournalCallParamData& operator=(const JournalCallParamData&) = delete;
		std::string m_paramName;
		ParameterMetaType m_paramType;
		bool m_isClass;
		ParameterBasicType m_parameterBasicType;
		std::string m_className;


};

class JournalCallParamDataString : public JournalCallParamData
{
public:


	JournalCallParamDataString(std::string paramName,
		ParameterMetaType paramType, std::string value);

	void Journal() override;

private:
	JournalCallParamDataString() = delete;
	JournalCallParamDataString(const JournalCallParamDataString&) = delete;
	JournalCallParamDataString& operator=(const JournalCallParamDataString&) = delete;
	std::string m_value;
};

class JournalCallParamDataInt : public JournalCallParamData
{
public:


	JournalCallParamDataInt(std::string paramName,
		ParameterMetaType paramType, std::int64_t value);

	void Journal() override;

private:
	JournalCallParamDataInt() = delete;
	JournalCallParamDataInt(const JournalCallParamDataInt&) = delete;
	JournalCallParamDataInt& operator=(const JournalCallParamDataInt&) = delete;
	std::int64_t m_value;
};

class JournalCallParamDataBoolean : public JournalCallParamData
{
public:


	JournalCallParamDataBoolean(std::string paramName,
		ParameterMetaType paramType, bool value);

	void Journal() override;

private:
	JournalCallParamDataBoolean() = delete;
	JournalCallParamDataBoolean(const JournalCallParamDataBoolean&) = delete;
	JournalCallParamDataBoolean& operator=(const JournalCallParamDataBoolean&) = delete;
	bool m_value;
};


class JournalCallParamDataClass : public JournalCallParamData
{
public:


	JournalCallParamDataClass(std::string paramName,
		ParameterMetaType paramType, GuidObject* classObject, std::string className);

	void Journal() override;

private:
	JournalCallParamDataClass() = delete;
	JournalCallParamDataClass(const JournalCallParamDataClass&) = delete;
	JournalCallParamDataClass& operator=(const JournalCallParamDataClass&) = delete;
	GuidObject* m_classObject;
	std::string m_paramName;
	std::string m_className;
};

class JournalCallData
{
	public:
		enum class CannedGlobals
		{
			SESSION,
			NOT_CANNED
		};

		JournalCallData(std::string methodName, CannedGlobals cannedGlobals);
		JournalCallData(std::string methodName, GuidObject* classObject);
		void AddParameter(JournalCallParamData* param);
		void AddReturnValue(JournalCallParamData* param);

		virtual ~JournalCallData();

		void Journal();

	private:
		JournalCallData() = delete;
		JournalCallData(const JournalCallData&) = delete;
		JournalCallData& operator=(const JournalCallData&) = delete;
		std::string m_methodName;
		std::vector<JournalCallParamData *> m_params;
		bool m_isCanned;
		GuidObject* m_classObject;
		CannedGlobals m_cannedGlobal;
		JournalCallParamData* m_retVal; // nulptr is void

};


enum class JournalingLanguage
{
	CPP,
	Java
};

extern JOURNALING_API void SetJournalingLangauge(JournalingLanguage jnlLang);

extern JOURNALING_API JournalingLanguage GetJournalingLangauge();

extern JOURNALING_API void StartJournaling(std::string jnlFile);

void ProFormaStart();
void ProFormaStartCPP();
void ProFormaStartJava();

extern JOURNALING_API void EndJournaling();

void ProFormEnd();
void ProFormEndCPP();
void ProFormEndJava();

void WriteCall();
void WriteCallCPP();
void WriteCallJava();

std::string GenerateParamaterName(std::string paramName);

extern JOURNALING_API bool IsJournaling();

extern JOURNALING_API void JournalIntInParam(int value, std::string paramName);

extern JOURNALING_API void JournalBoolInParam(bool value, std::string paramName);

extern JOURNALING_API void JournalStringInParam(std::string value, std::string paramName);


extern JOURNALING_API void JournalStartCall(std::string methodName, JournalCallData::CannedGlobals cannedGlobal);
extern JOURNALING_API void JournalStartCall(std::string methodName, GuidObject* classObject);

extern JOURNALING_API void JournalEndCall();

extern JOURNALING_API void JournalReturnClass(GuidObject* classObject, std::string className, std::string paramName);



