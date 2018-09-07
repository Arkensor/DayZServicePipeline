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
#include <filesystem>

bool EndsWith( const std::string& str, const std::string& suffix )
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}

int main( int argc, char *argv[] )
{
    cxxopts::Options options( "DayZServicePipeline", "Connect DayZ Standalone to external services the easy way." );

    options.add_options()
    ( "help", "Print help, what did you expect?" )
    (
        "listen", "(Required) Directory path the pipe is located.", cxxopts::value<std::string>()
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

    auto baseDir = std::filesystem::path( options [ "listen" ].as< std::string >() );

    if( baseDir.empty() || baseDir.string() == "nopath" )
    {
        std::cout << "[Error] No or incorrect path given" << std::endl;
        return -1;
    }

    if( baseDir.string().find( ".DayZServicePipeline" ) == std::string::npos )
    {
        baseDir = std::filesystem::path( baseDir / ".DayZServicePipeline" );
    }

    std::cout << "DayZServicePipeline version 1.0 initialized." << std::endl;

    auto oPipeline = new ServicePipeline( baseDir );
    auto oWorkLoad = new Workload();
    auto oProcessor = new WorkloadProcessor();

    bool bReturn = false;

    while( !bReturn )
    {
        //Try to get a workload
        if( oPipeline->TryGetWorkload( oWorkLoad ) )
        {
            //Pass workload to the processor.
            oProcessor->Process( oWorkLoad );

            oPipeline->TryWriteWorkloadResult( oWorkLoad );

            //Clean workload for next use
            oWorkLoad->clear();
        }

        Sleep( 10 );
    }

    return 0;
}
