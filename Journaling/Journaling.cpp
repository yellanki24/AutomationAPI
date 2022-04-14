// Journaling.cpp : Defines the exported functions for the DLL.
//

#include "framework.h"
#include "Journaling.h"
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include<algorithm>
#include <stdbool.h>
#include <regex>
using namespace std;
//// This is an example of an exported variable
//JOURNALING_API int nJournaling=0;
//
//// This is an example of an exported function.
//JOURNALING_API int fnJournaling(void)
//{
//    return 0;
//}

static JournalingLanguage m_JournalingLanguage;
static bool m_isJournaling = false;
static std::ofstream* m_file;
static std::stringstream preProForma; // Include files for example
static std::stringstream journalContents;
static JournalCallData * currentCall = nullptr;
static std::map<int, std::string> m_guidToParamMap;
static std::map<std::string, int> m_paramNameCounts;

void SetJournalingLangauge(JournalingLanguage jnlLang)
{
    m_JournalingLanguage = jnlLang;
}

JournalingLanguage GetJournalingLangauge()
{
    return m_JournalingLanguage;
}

void StartJournaling(std::string jnlFile)
{
    if (m_isJournaling)
    {
        throw new std::exception("Already Journaling , StartJournaling");
    }
    else
    {
        m_isJournaling = true;
        m_file = new std::ofstream(jnlFile);
        journalContents.clear();
        preProForma.clear();
    }
}

void ProFormaStart()
{
    if (m_JournalingLanguage == JournalingLanguage::CPP)
    {
        ProFormaStartCPP();
    }
    else
    {
        ProFormaStartJava();
    }
}

void ProFormaStartCPP()
{
    //Write out include Files
    *m_file << "#include <iostream>" << std::endl;
    *m_file << "#include \"..\\AutomationBinding\\Session.h\""<< std::endl;
    *m_file << "#include \"..\\AutomationBinding\\Part.h\"" << std::endl;

    *m_file << preProForma.str() << std::endl;
    
    *m_file << "int main()" << std::endl;
    *m_file << "{" << std::endl;
    *m_file << "    std::cout << \"Hello World!\\n\";" << std::endl;
    *m_file << "    AutomationAPI::Session* mySession = AutomationAPI::Session::GetSession();" << std::endl;
}

void ProFormaStartJava()
{
    *m_file << "NIY Java" << std::endl;
}

void EndJournaling()
{
    if (!m_isJournaling)
    {
        throw new std::exception("Not Journaling, EndJournaling");
    }
    else
    {
        ProFormaStart();
        *m_file << journalContents.str() << std::endl;
        ProFormEnd();
        m_file->close();
        m_isJournaling = false;
        m_guidToParamMap.clear();
        m_paramNameCounts.clear();
    }

}
void ProFormEnd()
{
    if (m_JournalingLanguage == JournalingLanguage::CPP)
    {
        ProFormEndCPP();
    }
    else
    {
        ProFormEndJava();
    }
}

void ProFormEndCPP()
{
    *m_file << "}" << std::endl;
}
void ProFormEndJava()
{
    *m_file << "NIY END" << std::endl;
}

bool IsJournaling()
{
    return m_isJournaling;
}

void JournalIntInParam(int value, std::string paramName)
{
    JournalCallParamDataInt* journalCallParamData = new JournalCallParamDataInt(paramName, JournalCallParamData::ParameterMetaType::INPUT, value);
    currentCall->AddParameter(journalCallParamData);
}

void JournalBoolInParam(bool value, std::string paramName)
{
    JournalCallParamDataBoolean* journalCallParamData = new JournalCallParamDataBoolean(paramName, JournalCallParamData::ParameterMetaType::INPUT, value);
    currentCall->AddParameter(journalCallParamData);
}

void JournalStringInParam(std::string value, std::string paramName)
{
    JournalCallParamDataString* journalCallParamData = new JournalCallParamDataString(paramName, JournalCallParamData::ParameterMetaType::INPUT, value);
    currentCall->AddParameter(journalCallParamData);
}

void JournalReturnClass(GuidObject* classObject, std::string className, std::string paramName)
{
    JournalCallParamDataClass* journalCallParamData = 
        new JournalCallParamDataClass(paramName, JournalCallParamData::ParameterMetaType::RETURN, classObject, className);

    currentCall->AddReturnValue(journalCallParamData);
}

void JournalStartCall(std::string methodName, JournalCallData::CannedGlobals cannedGlobal)
{
    currentCall = new JournalCallData(methodName, cannedGlobal);
}

void JournalStartCall(std::string methodName, GuidObject* classObject)
{
    currentCall = new JournalCallData(methodName, classObject);
}

void JournalEndCall()
{
    WriteCall();
}

void WriteCall()
{
    if (m_JournalingLanguage == JournalingLanguage::CPP)
    {
        WriteCallCPP();
    }
    else
    {
        WriteCallJava();
    }
}

void WriteCallCPP()
{
    currentCall->Journal();
}

void WriteCallJava()
{
    journalContents << "NIY WriteCallJava" << std::endl;
}

std::string GenerateParamaterName(std::string paramNameBase)
{
    std::string retVal;
    int numAppend = 0;
    //Is nameBase in map already?
    if (m_paramNameCounts.find(paramNameBase) == m_paramNameCounts.end())
    {
        //Not in map so append 1 and store it
        m_paramNameCounts[paramNameBase] = 1;
        numAppend = 1;
    }
    else
    {
        numAppend = m_paramNameCounts[paramNameBase] ;
        numAppend = numAppend + 1;
        m_paramNameCounts[paramNameBase] = numAppend;
    }

    std::stringstream paramNameBuilder;
    paramNameBuilder << paramNameBase << numAppend;
    retVal = paramNameBuilder.str();
    
    return retVal;
}

JournalCallData::JournalCallData(std::string methodName, CannedGlobals cannedGlobals) 
    : m_methodName(methodName), m_cannedGlobal(cannedGlobals), m_isCanned(true), m_retVal(nullptr), m_classObject(nullptr)
{
}

JournalCallData::JournalCallData(std::string methodName, GuidObject*  m_classObject)
    : m_methodName(methodName), m_cannedGlobal(CannedGlobals::NOT_CANNED), m_isCanned(false), m_retVal(nullptr) ,m_classObject(m_classObject)
{

}

void JournalCallData::AddParameter(JournalCallParamData* param)
{
    m_params.push_back(param);
}

void JournalCallData::AddReturnValue(JournalCallParamData* param)
{
    m_retVal = param;
}

JournalCallData::~JournalCallData()
{
    for(int i=0; i < m_params.size(); i++)
    {
        delete m_params[i];
    }

    delete m_retVal;
}

void JournalCallData::Journal()
{
    // First check if we have a return value
    if (this->m_retVal != nullptr)
    {
        m_retVal->Journal();
    }
    // Then print out call to object (the this) and the method call

    if (this->m_isCanned)
    {
        if (this->m_cannedGlobal == CannedGlobals::SESSION)
        {
            journalContents << "mySession->";
        }
    }
    else
    {
        //Retrieve param Name
        std::string paramName = m_guidToParamMap[this->m_classObject->GetGuid()];

        journalContents << paramName << "->";
    }

    journalContents <<  this->m_methodName << "(";
    
    for (int i = 0; i < m_params.size(); i++)
    {
        m_params[i]->Journal();
    }
    journalContents << ");" << std::endl;


}

JournalCallParamData::JournalCallParamData(std::string paramName,
    ParameterMetaType paramType, ParameterBasicType parameterBasicType) :
        m_paramName(paramName), m_paramType(paramType), m_parameterBasicType(parameterBasicType),
        m_isClass(false), m_className()
{

}

JournalCallParamData::JournalCallParamData(std::string paramName, ParameterMetaType paramType,
    std::string className) : m_paramName(paramName), m_paramType(paramType),
    m_isClass(true), m_className(className), m_parameterBasicType(ParameterBasicType::NOT_BASIC)
{

}

JournalCallParamDataInt::JournalCallParamDataInt(std::string paramName,
    ParameterMetaType paramType, std::int64_t value) :
    JournalCallParamData(paramName, paramType, JournalCallParamData::ParameterBasicType::INTEGER), m_value(value)
{

}
JournalCallParamDataBoolean::JournalCallParamDataBoolean(std::string paramName,
    ParameterMetaType paramType, bool value) :
    JournalCallParamData(paramName, paramType, JournalCallParamData::ParameterBasicType::BOOLEAN), m_value(value)
{

}





JournalCallParamDataString::JournalCallParamDataString(std::string paramName,
    ParameterMetaType paramType, std::string value) : 
        JournalCallParamData(paramName, paramType, JournalCallParamData::ParameterBasicType::STRING), m_value(value)
{

}

void JournalCallParamDataString::Journal()
{
    if (this->m_paramType == JournalCallParamData::ParameterMetaType::INPUT)
    {
        //There is a bug here, all \ need to be replaced with \\

        m_value = std::regex_replace(m_value, std::regex(R"(\\)"), R"(\\)");

        journalContents << "\"" << m_value << "\"" ;
    }
    else if (this->m_paramType == JournalCallParamData::ParameterMetaType::OUTPUT)
    {
        throw new std::exception("NIY ");
    }
    else // RETURN
    {
        throw new std::exception("NIY");
    }


}

void JournalCallParamDataBoolean::Journal()
{
    if (this->m_paramType == JournalCallParamData::ParameterMetaType::INPUT)
    {
        string s;
        if (m_value == 1)
            s = "true";
        else
            s = "false";

        journalContents << s << ",";
    }
    else if (this->m_paramType == JournalCallParamData::ParameterMetaType::OUTPUT)
    {
        throw new std::exception("NIY ");
    }
    else // RETURN
    {
        throw new std::exception("NIY");
    }


}

void JournalCallParamDataInt::Journal()
{
    if (this->m_paramType == JournalCallParamData::ParameterMetaType::INPUT)
    {

        journalContents << m_value ;
    }
    else if (this->m_paramType == JournalCallParamData::ParameterMetaType::OUTPUT)
    {
        throw new std::exception("NIY ");
    }
    else // RETURN
    {
        throw new std::exception("NIY");
    }


}

JournalCallParamDataClass::JournalCallParamDataClass(std::string paramName, ParameterMetaType paramType,
    GuidObject* classObject, std::string className) :
     JournalCallParamData(paramName, paramType, JournalCallParamData::ParameterBasicType::STRING), m_classObject (classObject),
         m_paramName(paramName),  m_className (className)
{

}

void JournalCallParamDataClass::Journal()
{
    

    if (this->m_paramType == JournalCallParamData::ParameterMetaType::INPUT)
    {
        
        throw new std::exception("NIY ");
    }
    else if (this->m_paramType == JournalCallParamData::ParameterMetaType::OUTPUT)
    {
        throw new std::exception("NIY ");
    }
    else // RETURN
    {
        std::string paramName;

        if (m_guidToParamMap.find(this->m_classObject->GetGuid()) == m_guidToParamMap.end())
        {
            paramName = GenerateParamaterName(m_paramName);
            m_guidToParamMap[this->m_classObject->GetGuid()] = paramName;

            journalContents << m_className << " * " << paramName << " = ";
        }
        else
        {
            paramName = m_guidToParamMap[this->m_classObject->GetGuid()];
            //from a query method called multiple times

            journalContents <<  paramName << " = ";

        }

        


    }

}

