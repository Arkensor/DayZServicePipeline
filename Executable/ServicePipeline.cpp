/**********************************************************************************************************************\

    DESCRIPTION: Service pipeline that communicates with the game process via the filesystem

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  05.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#include "ServicePipeline.hpp"

#include <filesystem>
#include <sstream>
#include <fstream>
#include <iostream>

ServicePipeline::ServicePipeline( std::filesystem::path & basePath )
    : m_oBasePath( basePath )
{
}

ServicePipeline::~ServicePipeline()
{
}

bool ServicePipeline::TryGetWorkload( Workload* oWorkload )
{
    std::filesystem::path oRequestPath( m_oBasePath );

    if( std::filesystem::exists( oRequestPath / "request" ) && !std::filesystem::exists( oRequestPath / ".lock" ) )
    {
        std::ifstream in( std::filesystem::path( oRequestPath / "request" ).string() );
        std::string strData( dynamic_cast< std::stringstream const & >( std::stringstream() << in.rdbuf()).str() );
        in.close();

        auto pos = strData.find( '^' );

        if( pos != std::string::npos )
        {
            oWorkload->m_strServiceName = strData.substr( 0, pos );
            oWorkload->m_strFunctionName = "DayZServiceInterface";
            oWorkload->m_oFunctionArguments.emplace_back( strData.substr( pos + 1 ) );

        }

        std::filesystem::remove( oRequestPath / "request" );

        return true;
    }

    return false;
}

bool ServicePipeline::TryWriteWorkloadResult( Workload *oWorkload )
{
    std::filesystem::path oResponsePath( m_oBasePath );

    std::ofstream out( std::filesystem::path( oResponsePath / "response" ).string() );

    if( out.good() )
    {
        out << oWorkload->m_strResult;
    }

    out.close();

    return out.good();
}

