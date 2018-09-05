/**********************************************************************************************************************\

    DESCRIPTION: Service pipeline that communicates with the game process via the filesystem

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  05.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#include "ServicePipeline.hpp"

#include <experimental/filesystem>

ServicePipeline::ServicePipeline( std::string& strBasePath )
    : m_strBasePath( strBasePath )
    , m_poLoader( new LibraryLoader() )
{
}

ServicePipeline::~ServicePipeline()
{
}

bool ServicePipeline::TryGetWorkload( Workload* oWorkload )
{
    if( true )
    {
        oWorkload->m_strServiceName = "";
        oWorkload->m_strFunctionName = "";

        oWorkload->m_oFunctionArguments.emplace_back( "" );

        return true;
    }

    return false;
}

