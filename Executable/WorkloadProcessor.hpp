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

#include <filesystem>
#include <map>

class WorkloadProcessor
{
public:
    WorkloadProcessor( std::filesystem::path& libDir );
    virtual ~WorkloadProcessor();

    void Process( Workload* oWorkload );

protected:
    void* GetServiceInstance( std::string strServiceName );
    void* GetServiceFunction( std::string& strServiceName, const char *strFunctionName );

protected:
    LibraryLoader* m_poLoader;
    std::map< std::string, void* > m_oLoadedServices;
    std::map< std::string, std::map< std::string, void* > > m_oLoadedServiceFunctions;
};

#endif //DAYZSERVICEPIPELINE_WORKLOADPROCESSOR_HPP