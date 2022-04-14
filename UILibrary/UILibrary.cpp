// UILibrary.cpp : Defines the exported functions for the DLL.
//

#include "framework.h"
#include "UILibrary.h"


// This is an example of an exported variable
UILIBRARY_API int nUILibrary=0;

// This is an example of an exported function.
UILIBRARY_API int fnUILibrary(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CUILibrary::CUILibrary()
{
    return;
}




