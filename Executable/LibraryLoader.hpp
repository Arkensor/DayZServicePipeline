/**********************************************************************************************************************\

    DESCRIPTION: Load dynamic libraries on windows and linux

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  05.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#ifndef DAYZSERVICEPIPELINE_LIBRARYLOADER_HPP
#define DAYZSERVICEPIPELINE_LIBRARYLOADER_HPP

#include <string>

#ifdef _MSC_VER
    #define NOMINMAX
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif


class LibraryLoader
{
public:
    LibraryLoader();
    virtual ~LibraryLoader();

    void* LoadDynamicLibrary( char* );
    void* GetFunctionPointer( void*, char* );
    bool FreeDynamicLLibrary( void* );

protected:
    static bool EndsWith(const std::string& str, const std::string& suffix);
};


#endif //DAYZSERVICEPIPELINE_LIBRARYLOADER_HPP