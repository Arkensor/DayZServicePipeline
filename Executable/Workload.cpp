/**********************************************************************************************************************\

    DESCRIPTION: Workload that is added to the pipeline by the game

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  05.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#include "Workload.hpp"

Workload::Workload()
    : m_strServiceName( "" )
    , m_strFunctionName( "" )
    , m_strResult( "" )
{
}


Workload::Workload( std::string& strServiceName,
                    std::string& strFunctionName,
                    std::vector< std::string >& oFunctionArguments )
    : m_strServiceName( strServiceName )
    , m_strFunctionName( strFunctionName )
    , m_oFunctionArguments( oFunctionArguments )
{
}


Workload::~Workload()
{
}

void Workload::clear()
{
    m_strServiceName.clear();
    m_strFunctionName.clear();
    m_oFunctionArguments.clear();
    m_strResult.clear();
}
