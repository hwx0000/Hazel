using System;
using System.Runtime.CompilerServices;

namespace MyNamespace
{
    public class Program
    {
        public float MyPublicFloatVar = 5.0f;
        public void PrintFloatVar()
        {
            Console.WriteLine("MyPublicFloatVar = {0:F}", MyPublicFloatVar);
            Print();
            //PrintString("PrintString");
		}

        public static void PrintVarStatic()
        {
            Console.WriteLine("MyPublicFloatVar = {0:F}", 5000.0f);
        }


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void Print();


        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern static void PrintString(string s);
    }
}