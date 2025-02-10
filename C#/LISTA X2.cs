using System;
using System.Collections.Generic;

class Program
{
    int numeros;
    static void Main()
    {
        List<int> numeros = new List<int> {1,2,3,4,5};
        numeros.ForEach(n => Console.WriteLine(n*2));
    }
}
