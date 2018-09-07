/**********************************************************************************************************************\

    DESCRIPTION: Enscript library providing the functions to interact with the pipeleline application

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  06.09.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Paul L. (Arkensor) All rights reserved!

\**********************************************************************************************************************/
#ifndef DAYZSERVICEPIPELINE_C
#define DAYZSERVICEPIPELINE_C

class BasicRequest
{
};

class BasicResponse
{
};

class NoResult : BasicResponse
{
};

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
        auto strInputTypeName = GetTypeName( InputType );
        auto strOutputTypeName = GetTypeName( OutputType );

        array< string > primitiveTypes = { "string", "bool", "int", "float", "vector" };

        if( primitiveTypes.Find( strInputTypeName ) >= 0 )
        {
            auto wrappedData = new PrimitiveWrapper< InputType >();
            wrappedData.SetValue( m_oInputData );

            serializer.WriteToString( wrappedData, false, data );
        }
        else
        {
            serializer.WriteToString( m_oInputData, false, data );
        }

        auto ticket = GetPipeline().SendRequest( strServiceName, data );

        if( strOutputTypeName == GetTypeName( NoResult ) )
        {
            OutputType res;
            return res;
        }

        auto returnValue = GetPipeline().FetchResponse( ticket );

        Print( "returnValue: " + returnValue );

        string strError;

        //Primitive data
        if( primitiveTypes.Find( strOutputTypeName ) >= 0 )
        {
            //Deserialize primitive data type wrapper.
            auto primitiveResult = new PrimitiveWrapper< OutputType >();

            if( !serializer.ReadFromString( primitiveResult, returnValue, strError ) )
            {
                Print( "Deserialize error: " + strError );
            }

            return primitiveResult.GetValue();
        }

        //Object data
        OutputType resultObject;

        if( !serializer.ReadFromString( resultObject, returnValue, strError ) )
        {
            Print( "Deserialize error: " + strError );
        }

        return resultObject;
    }
};

class DayZServicePipeline
{
//    protected ref map< string, int > m_oServiceKeyMapping;

    void DayZServicePipeline()
    {
        Print( "DayZServicePipeline::DayZServicePipeline()" );

        if( !MakeDirectory( "$profile:.DayZServicePipeline" ) )
        {
            //Todo handle error
        }

        TryUnlock();
        CleanupRequest();
        CleanupResponse();

        //Make sure the pipeline dir exists
    }

    void ~DayZServicePipeline()
    {
        Print( "DayZServicePipeline::~DayZServicePipeline()" );
    }

    string SendRequest( string strServiceName, string strData )
    {
        TryLock();

        FileHandle file = OpenFile( "$profile:.DayZServicePipeline/request", FileMode.WRITE );

        if (file != 0)
        {
            FPrint( file, strServiceName + "^" + strData );

            CloseFile( file );
        }

        TryUnlock();

        return strServiceName;
    }

    string FetchResponse( string strTicket )
    {
        float timeout = 0;

        while( !( FileExist( "$profile:.DayZServicePipeline/response" ) && !FileExist( "$profile:.DayZServicePipeline/.lock" ) ) )
        {
//            if( timeout > 30 ) //Maximum timeout in seconds //Todo enable this again and check if the sleep even works...
//            {
//                CleanupRequest();
//                TryUnlock();
//
//                return "{\"Error\":\"Service response timed out.\"}";
//            }

            timeout += 0.1;

            Sleep( 0.1 );
        }

        FileHandle file = OpenFile( "$profile:.DayZServicePipeline/response", FileMode.READ );

		string strResult;
		string strLine;

		while ( FGets( file,  strLine ) > 0 )
		{
			strResult += strLine;
		}

		CloseFile( file );

        if( !CleanupResponse() )
        {
            //Todo handle response data not deleted
        }

        TryUnlock();

        return strResult;
    }

    bool TryLock()
    {
        FileHandle file = OpenFile( "$profile:.DayZServicePipeline/.lock", FileMode.WRITE );

        if ( file != 0 )
        {
            CloseFile( file );

            return true;
        }

        return false;
    }

    bool TryUnlock()
    {
        DeleteFile( "$profile:.DayZServicePipeline/.lock" );
        return IsLocked();
    }

    bool IsLocked()
    {
        return FileExist( "$profile:.DayZServicePipeline/.lock" );
    }

    bool CleanupResponse()
    {
        DeleteFile( "$profile:.DayZServicePipeline/response" );

        return !FileExist( "$profile:.DayZServicePipeline/response" );
    }

    bool CleanupRequest()
    {
        DeleteFile( "$profile:.DayZServicePipeline/request" );

        return !FileExist( "$profile:.DayZServicePipeline/request" );
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

    void SetValue( InputType value )
    {
        primitive = value;
    }

    InputType GetValue()
    {
        return primitive;
    }
};

string GetTypeName( typename type )
{
    return type.ToString();
}

#endif //DAYZSERVICEPIPELINE_C