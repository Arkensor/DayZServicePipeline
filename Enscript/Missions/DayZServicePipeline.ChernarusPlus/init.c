#include "missions\\DayZServicePipeline.ChernarusPlus\\DayZServicePipeline.c"

void main()
{
    auto request = new ServiceRequest< float, string >( 1.234567890 );
    auto result = request.SendToService( "TEST" );

    Print( "Result: " + result );
}