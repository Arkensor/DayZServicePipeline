/**********************************************************************************************************************\

    DESCRIPTION: Service pipeline that communicates with the game process via the filesystem

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  05.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#ifndef DAYZSERVICEPIPELINE_SERVICEPIPELINE_HPP
#define DAYZSERVICEPIPELINE_SERVICEPIPELINE_HPP
#include "Workload.hpp"

#include <filesystem>

class ServicePipeline
{
public:
    ServicePipeline( std::filesystem::path & basePath );
    virtual ~ServicePipeline();

    bool TryGetWorkload( Workload* oWorkload );
    bool TryWriteWorkloadResult( Workload* oWorkload );

public:
    std::filesystem::path m_oBasePath;
};


#endif //DAYZSERVICEPIPELINE_SERVICEPIPELINE_HPP
