/**********************************************************************************************************************\

    DESCRIPTION: Function core to load all services and connect them

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  05.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#include "ServicePipeline.hpp"
#include "WorkloadProcessor.hpp"

#include "ThirdParty/cxxopts/cxxopts.hpp"

#include <iostream>

int main( int argc, char *argv[] )
{
    cxxopts::Options options( "DayZServicePipeline", "Connect DayZ Standalone to external services the easy way." );

    options.add_options()
    ( "help", "Print help, what did you expect?" )
    (
        "listen", "(Required) Path to the server that the pipeline lists on.", cxxopts::value<std::string>()
            ->default_value( "nopath" )
            ->implicit_value( "nopath" )
    );

    if ( argc < 2  )
    {
        std::cout << options.help( { "" } ) << std::endl;
        return 404;
    }

    try
    {
        options.parse( argc, argv );
    }
    catch ( ... )
    {
        std::exception_ptr oPtr = std::current_exception();
        try {
            if ( oPtr ) {
                std::rethrow_exception( oPtr );
            }
        }
        catch ( const std::exception & oException )
        {
            throw std::runtime_error( std::string( std::string( "[Error] " ) + oException.what() ) );
        }
    }

    if ( options.count( "help" ) )
    {
        std::cout << options.help( { "" } ) << std::endl;
        return 200;
    }

    auto strBaseDir = options [ "listen" ].as<std::string>();

    if( strBaseDir.empty() || strBaseDir == "nopath" )
    {
        std::cout << "[Error] No or incorrect path given" << std::endl;
        return -1;
    }

    std::cout << "DayZServicePipeline version 1.0 initialized." << std::endl;

    auto oPipeline = new ServicePipeline( strBaseDir );
    auto oWorkLoad = new Workload();
    auto oProcessor = new WorkloadProcessor();

    bool bReturn = false;

    while( !bReturn )
    {
        //Try to get a workload
        oPipeline->TryGetWorkload( oWorkLoad );

        //Pass workload to the processor.
        oProcessor->Process( oWorkLoad );

        //Clean workload for next use
        oWorkLoad->clear();
    }

    return 0;
}
