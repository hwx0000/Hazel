using System;

namespace MyNameSpace
{
    public class Program
    {
        public float MyPublicFloatVar = 5.0f;
        public void PrintFloatVar()
        {
            Console.WriteLine("MyPublicFloatVar = {0:F}", MyPublicFloatVar);
        }
    }
}