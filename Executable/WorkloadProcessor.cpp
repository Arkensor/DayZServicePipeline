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

typedef void(__stdcall *DayZServiceCall)(char *output, int outputSize, const char *data);
typedef void(__stdcall *DayZServiceVersion)(char *output, int outputSize, const char *data);

typedef void(__stdcall *RVExtension)(char *output, int outputSize, const char *function);
typedef void(__stdcall *RVExtensionVersion)(char *output, int outputSize);
typedef void(__stdcall *RVExtensionArgs)(char *output, int outputSize, const char *function, const char **args, int argCnt);


WorkloadProcessor::WorkloadProcessor( std::filesystem::path& libDir )
    : m_poLoader( new LibraryLoader( libDir ) )
{
}

WorkloadProcessor::~WorkloadProcessor()
{
}

void WorkloadProcessor::Process( Workload *oWorkload )
{
    std::cout << "m_strServiceName:" << oWorkload->m_strServiceName << std::endl;
    std::cout << "m_strFunctionName:" << oWorkload->m_strFunctionName << std::endl;

    for ( auto & m_oFunctionArgument : oWorkload->m_oFunctionArguments )
        std::cout << "m_oFunctionArgument: " << m_oFunctionArgument << std::endl;

    auto func = reinterpret_cast< DayZServiceCall >( GetServiceFunction( oWorkload->m_strServiceName, "DayZServiceCall" ) );

    if( func )
    {
        const int bufferSize = 10 * 1024;
        char buffer[ bufferSize ] = { 0 };

        std::string data = "This is an input data test";

        func( buffer, bufferSize, data.c_str() );

        std::string result( buffer );

        std::cout << "Result: " << result << std::endl;

        oWorkload->m_strResult = result;
    }
}

void *WorkloadProcessor::GetServiceInstance( std::string strServiceName )
{
    //Do we have the service loaded?
    if( m_oLoadedServices.find( strServiceName ) == std::end( m_oLoadedServices ) )
    {
        auto pointer = m_poLoader->LoadDynamicLibrary( strServiceName );

        m_oLoadedServices[ strServiceName ] = pointer;
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