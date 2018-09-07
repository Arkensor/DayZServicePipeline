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
#include <filesystem>

#ifdef _MSC_VER
    #define NOMINMAX
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif


class LibraryLoader
{
public:
    LibraryLoader( std::filesystem::path& libDir );
    virtual ~LibraryLoader();

    void* LoadDynamicLibrary( std::string strLibName );
    void* GetFunctionPointer( void*, std::string strFunctionName );
    bool FreeDynamicLLibrary( void* );

protected:
    static bool EndsWith(const std::string& str, const std::string& suffix);

protected:
    std::filesystem::path m_libDir;
};


#endif //DAYZSERVICEPIPELINE_LIBRARYLOADER_HPP