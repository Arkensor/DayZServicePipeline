/**********************************************************************************************************************\

    DESCRIPTION: Enscript library providing the functions to interact with the pipeleline application

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  06.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#ifndef DAYZSERVICEPIPELINE_C
#define DAYZSERVICEPIPELINE_C

class ServiceRequest< Class InputType, Class OutputType >
{
    protected InputType m_oInputData;

    void ServiceRequest( InputType input )
    {
        Print( "ServiceRequest::ServiceRequest()" );

        m_oInputData = input;
    }

    void ~ServiceRequest()
    {
        Print( "ServiceRequest::~ServiceRequest()" );
    }

    OutputType SendToService( string strServiceName )
    {
        string data;

        auto serializer = new JsonSerializer();

        //Process primitive types
        auto strTypeName = GetTypeName( InputType );

        if( strTypeName == "string" || strTypeName == "bool" || strTypeName == "int" || strTypeName == "float" || strTypeName == "vector" )
        {
            auto wrappedData = new PrimitiveWrapper< InputType >( m_oInputData );

            serializer.WriteToString( wrappedData, false, data );
        }
        else
        {
            serializer.WriteToString( m_oInputData, false, data );
        }

        return GetPipeline().SendRequest( strServiceName, data ); //Todo build return object from string
    }
};

class DayZServicePipeline
{
    protected ref map< string, int > m_oServiceKeyMapping;

    void DayZServicePipeline()
    {
        Print( "DayZServicePipeline::DayZServicePipeline()" );
    }

    void ~DayZServicePipeline()
    {
        Print( "DayZServicePipeline::~DayZServicePipeline()" );
    }

    string SendRequest( string strServiceName, string strData )
    {
        return "Result: " + strServiceName + " - " + strData;
    }
};

//Global instance //todo check if this can be made static
ref DayZServicePipeline g_ServicePipeline = new ref DayZServicePipeline();

//Global getter
ref DayZServicePipeline GetPipeline()
{
    return g_ServicePipeline;
}

//Global getter alias
ref DayZServicePipeline GetServicePipeline()
{
    return GetPipeline();
}

//Helper for serialization
class PrimitiveWrapper< Class InputType >
{
    InputType primitive;

    void PrimitiveWrapper( InputType value )
    {
        primitive = value;
    }
}

string GetTypeName( typename type )
{
    return type.ToString();
}

#endif //DAYZSERVICEPIPELINE_C