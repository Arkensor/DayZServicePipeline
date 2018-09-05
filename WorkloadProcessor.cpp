/**********************************************************************************************************************\

    DESCRIPTION: Process workloads and load the dynamic libraries if needed

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  05.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#include "WorkloadProcessor.hpp"

WorkloadProcessor::WorkloadProcessor()
{
}

WorkloadProcessor::~WorkloadProcessor()
{
}

void WorkloadProcessor::Process( Workload *oWorkload )
{
    oWorkload->m_oResults.emplace_back( "" );
}
