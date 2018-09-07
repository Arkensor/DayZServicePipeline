#include "missions\\DayZServicePipeline.ChernarusPlus\\DayZServicePipeline.c"

class TestRequest : BasicRequest
{
    int i = 11;
    bool b = true;
};

class TestResult : BasicResponse
{
    int i;
    bool b;
};

void main()
{

    auto oTest = new TestRequest();

    auto request = new ServiceRequest< TestRequest, TestResult >( oTest );
    auto result = request.SendToService( "TEST" );

    Print( "Result: " + result );
    Print( "Result: " + result.i );
    Print( "Result: " + result.b );
}