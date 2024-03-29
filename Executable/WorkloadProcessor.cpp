/**********************************************************************************************************************\

    DESCRIPTION: Process workloads and load the dynamic libraries if needed

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  05.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#include "WorkloadProcessor.hpp"

#include <iostream>
#include <filesystem>

typedef void( __stdcall *DayZServiceCall )   ( char *output, int outputSize, const char *data );
typedef void( __stdcall *DayZServiceVersion )( char *output, int outputSize );

typedef void( __stdcall *RVExtension )       ( char *output, int outputSize, const char *function );
typedef void( __stdcall *RVExtensionVersion )( char *output, int outputSize );
typedef  int( __stdcall *RVExtensionArgs )   ( char *output, int outputSize, const char *function, const char **args, int argCnt );

WorkloadProcessor::WorkloadProcessor( std::filesystem::path& libDir )
    : m_poLoader( new LibraryLoader( libDir ) )
{
}

WorkloadProcessor::~WorkloadProcessor()
{
}

void WorkloadProcessor::Process( Workload *oWorkload )
{
//    std::cout << "m_strServiceName:" << oWorkload->m_strServiceName << std::endl;
//    std::cout << "m_strFunctionName:" << oWorkload->m_strFunctionName << std::endl;
//
//    for ( auto & m_oFunctionArgument : oWorkload->m_oFunctionArguments )
//        std::cout << "m_oFunctionArgument: " << m_oFunctionArgument << std::endl;

    if( oWorkload->m_strFunctionName == "DayZServiceInterface" )
    {
        auto func = reinterpret_cast< DayZServiceCall >( GetServiceFunction( oWorkload->m_strServiceName, "DayZServiceCall" ) );

        if( func )
        {
            const int bufferSize = 100 * 1024; //Output data size
            char buffer[ bufferSize ] = { 0 };

            func( buffer, bufferSize, oWorkload->m_oFunctionArguments.front().c_str() );

            std::string result( buffer );

            std::cout << "Input: " << oWorkload->m_oFunctionArguments.front() << " - Result: " << result << std::endl;

            oWorkload->m_strResult = result;
        }
    }
    else
    {
        //Todo handle RVExtensions
    }
}

void *WorkloadProcessor::GetServiceInstance( std::string strServiceName )
{
    //Do we have the service loaded?
    if( m_oLoadedServices.find( strServiceName ) == std::end( m_oLoadedServices ) )
    {
        auto pointer = m_poLoader->LoadDynamicLibrary( strServiceName );

        m_oLoadedServices[ strServiceName ] = pointer;

        //First time calling the service -> give feedback to the user that it has been loaded
        auto func = reinterpret_cast< DayZServiceVersion >( GetServiceFunction( strServiceName, "DayZServiceVersion" ) );
        if( func )
        {
            const int bufferSize = 512; //Output data size
            char buffer[ bufferSize ] = { 0 };

            func( buffer, bufferSize );

            std::string result( buffer );

            std::cout << "[INFO] Service '" << strServiceName << "' version " << result << " loaded." << std::endl;
        }
    }

    return m_oLoadedServices[ strServiceName ];
}

void* WorkloadProcessor::GetServiceFunction( std::string& strServiceName, const char *strFunctionName )
{
    bool bLoaded = true;

    //Do we have the service loaded?
    if( m_oLoadedServiceFunctions.find( strServiceName ) == std::end( m_oLoadedServiceFunctions ) )
    {
        bLoaded = false;
    }
    else
    {
        //Do we have the function loaded?
        if( m_oLoadedServiceFunctions[ strServiceName ].find( strFunctionName ) == std::end( m_oLoadedServiceFunctions[ strServiceName ] ) )
        {
           bLoaded = false;
        }
    }

    if( !bLoaded )
    {
        m_oLoadedServiceFunctions[ strServiceName ][ strFunctionName ] = m_poLoader->GetFunctionPointer( GetServiceInstance( strServiceName ), strFunctionName );
    }

    return m_oLoadedServiceFunctions[ strServiceName ][ strFunctionName ];
}