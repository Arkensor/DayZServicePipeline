/**********************************************************************************************************************\

    DESCRIPTION: Workload that is added to the pipeline by the game

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  05.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#ifndef DAYZSERVICEPIPELINE_WORKLOAD_HPP
#define DAYZSERVICEPIPELINE_WORKLOAD_HPP

#include <string>
#include <vector>

class Workload
{
public:
    Workload();
    Workload( std::string& strServiceName,
              std::string& strFunctionName,
              std::vector< std::string >& oFunctionArguments );

    virtual ~Workload();

    void clear();

public:
    std::string m_strServiceName;
    std::string m_strFunctionName;
    std::vector< std::string > m_oFunctionArguments;
    std::string m_strResult;
};


#endif //DAYZSERVICEPIPELINE_WORKLOAD_HPP