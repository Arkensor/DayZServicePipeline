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
#include "LibraryLoader.hpp"

class ServicePipeline
{
public:
    ServicePipeline( std::string& strBasePath );
    virtual ~ServicePipeline();

    bool TryGetWorkload( Workload* oWorkload );

public:
    std::string m_strBasePath;

protected:
    LibraryLoader* m_poLoader;
};


#endif //DAYZSERVICEPIPELINE_SERVICEPIPELINE_HPP
