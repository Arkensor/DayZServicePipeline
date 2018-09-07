/**********************************************************************************************************************\

    DESCRIPTION: Process workloads and load the dynamic libraries if needed

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  05.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#include "WorkloadProcessor.hpp"

#include <iostream>

WorkloadProcessor::WorkloadProcessor()
    : m_poLoader( new LibraryLoader() )
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

    oWorkload->m_strResult = oWorkload->m_oFunctionArguments.front();
}
