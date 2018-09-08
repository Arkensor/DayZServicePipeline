using RGiesecke.DllExport;
using System.Runtime.InteropServices;
using System.Text;
using Newtonsoft.Json;

namespace DayZServicePipelineTest
{
    public class Main
    {
        #region DAYZSERVICE

        class InputData
        {
            public int i;
            public bool b;
        }

        class OutputData
        {
            public int i;
            public bool b;
        }

        [DllExport("DayZServiceVersion", CallingConvention = CallingConvention.Winapi)]
        public static void DayZServiceVersion(StringBuilder output, int outputSize)
        {
            output.Append("1.0");
        }

        [DllExport("DayZServiceCall", CallingConvention = CallingConvention.Winapi)]
        public static void DayZServiceCall(StringBuilder output, int outputSize, [MarshalAs(UnmanagedType.LPStr)] string data)
        {
            //Build the input data from the data
            var inputData = JsonConvert.DeserializeObject<InputData>(data);

            var outputData = new OutputData();
            outputData.i = inputData.i + 5;
            outputData.b = !inputData.b;

            string outString = JsonConvert.SerializeObject(outputData);

            output.Append(outString);
        }

        #endregion

        #region RVEXTENSION

        [DllExport("RVExtensionVersion", CallingConvention = CallingConvention.Winapi)]
        public static void RvExtensionVersion(StringBuilder output, int outputSize)
        {
            output.Append("1.0");
        }

        [DllExport("RVExtension", CallingConvention = CallingConvention.Winapi)]
        public static void RvExtension(StringBuilder output, int outputSize, [MarshalAs(UnmanagedType.LPStr)] string function)
        {
            output.Append(function);
        }

        [DllExport("RVExtensionArgs", CallingConvention = CallingConvention.Winapi)]
        public static int RvExtensionArgs(StringBuilder output, int outputSize, [MarshalAs(UnmanagedType.LPStr)] string function, [MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.LPStr, SizeParamIndex = 4)] string[] args, int argCount)
        {
            foreach (var arg in args)
            {
                output.Append(arg);
            }

            return 0;
        }

        #endregion
    }
}