// Core.cpp : Defines the exported functions for the DLL.
//

#include "framework.h"
#include "Core.h"
#include <iostream>

CORE_API int initializeProduct(void)
{
	std::cout << "Product Core is Initialized" << std::endl;
	return 0;
}

CORE_API int shutdownProduct(void)
{
	std::cout << "Product Core is Shutdown" << std::endl;
	return 0;
}



//// This is an example of an exported variable
//CORE_API int nCore=0;
//
//// This is an example of an exported function.
//CORE_API int fnCore(void)
//{
//    return 0;
//}
//
//// This is the constructor of a class that has been exported.
//CCore::CCore()
//{
//    return;
//}
