// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the AUTOMATIONBINDING_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// AUTOMATIONBINDING_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef AUTOMATIONBINDING_EXPORTS
#define AUTOMATIONBINDING_API __declspec(dllexport)
#else
#define AUTOMATIONBINDING_API __declspec(dllimport)
#endif

//// This class is exported from the dll
//class AUTOMATIONBINDING_API CAutomationBinding {
//public:
//	CAutomationBinding(void);
//	// TODO: add your methods here.
//};
//
//extern AUTOMATIONBINDING_API int nAutomationBinding;
//
//AUTOMATIONBINDING_API int fnAutomationBinding(void);
