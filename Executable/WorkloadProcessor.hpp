/**********************************************************************************************************************\

    DESCRIPTION: Process workloads and load the dynamic libraries if needed

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  05.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#ifndef DAYZSERVICEPIPELINE_WORKLOADPROCESSOR_HPP
#define DAYZSERVICEPIPELINE_WORKLOADPROCESSOR_HPP

#include "Workload.hpp"
#include "LibraryLoader.hpp"

class WorkloadProcessor
{
public:
    WorkloadProcessor();
    virtual ~WorkloadProcessor();

    void Process( Workload* oWorkload );

protected:
    LibraryLoader* m_poLoader;
};


#endif //DAYZSERVICEPIPELINE_WORKLOADPROCESSOR_HPP
