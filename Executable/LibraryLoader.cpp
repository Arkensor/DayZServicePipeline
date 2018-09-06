/**********************************************************************************************************************\

    DESCRIPTION: Load dynamic libraries on windows and linux

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  05.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#include "LibraryLoader.hpp"

LibraryLoader::LibraryLoader()
{
}

LibraryLoader::~LibraryLoader()
{
}

void* LibraryLoader::LoadDynamicLibrary( char* pstrLibraryName )
{
    std::string strLibName = pstrLibraryName;
#ifdef _MSC_VER
    if( !EndsWith( strLibName, ".dll" ) )
    {
        strLibName += ".dll";
    }
#else
    if( !EndsWith( strLibName, ".so" ) )
    {
        strLibName += ".so";
    }
#endif

#ifdef _MSC_VER
    return ( void* )LoadLibrary( strLibName.c_str() );
#else
    return dlopen( strLibName.c_str(), 1 );
#endif

}
void* LibraryLoader::GetFunctionPointer( void* pLibrary, char* pstrFunctionName )
{
#ifdef _MSC_VER
    return ( void* )GetProcAddress( ( HINSTANCE )pLibrary, pstrFunctionName );
#else
    return dlsym( pLibrary, pstrFunctionName );
#endif
}

bool LibraryLoader::FreeDynamicLLibrary( void* pLibrary )
{
#ifdef _MSC_VER
    return static_cast< bool >( FreeLibrary( ( HINSTANCE )pLibrary ) );
#else
    return dlclose( pLibrary );
#endif
}

bool LibraryLoader::EndsWith( const std::string& str, const std::string& suffix )
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}