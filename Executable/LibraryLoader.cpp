/**********************************************************************************************************************\

    DESCRIPTION: Load dynamic libraries on windows and linux

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  05.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#include "LibraryLoader.hpp"

#include <filesystem>

LibraryLoader::LibraryLoader( std::filesystem::path& libDir )
    : m_libDir( libDir )
{
}

LibraryLoader::~LibraryLoader()
{
}

void* LibraryLoader::LoadDynamicLibrary( std::string strLibName )
{
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

    std::string strFullPath = ( m_libDir / strLibName ).string();

#ifdef _MSC_VER
    return ( void* )LoadLibrary( strFullPath.c_str() );
#else
    return dlopen( strFullPath.c_str(), 1 );
#endif

}
void* LibraryLoader::GetFunctionPointer( void* pLibrary, std::string strFunctionName )
{
#ifdef _MSC_VER
    return ( void* )GetProcAddress( ( HINSTANCE )pLibrary, strFunctionName.c_str() );
#else
    return dlsym( pLibrary, pstrFunctionName.c_str() );
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