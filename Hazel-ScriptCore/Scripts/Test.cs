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


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void Print();


        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
        //extern static void PrintString(string s);
    }
}