package oopinclass;
// Create an abstract class called calculator.

import java.util.Scanner;
abstract class calc{
    void addition(int a, int b)
    {
        System.out.println("The sum is " + (a+b));
    }

    void subtraction(int a, int b)
    {
        System.out.println("The difference is " + (a-b));
    }
    abstract void mul(int a, int b);
    abstract void div(int a, int b);
}

class calc2 extends calc{
    void mul(int a, int b)
    {
        System.out.println("The product is " + (a*b));
    }
    
}
class calc3 extends calc2{
    void div(int a, int b)
    {
        System.out.println("The quotient is " + (a/b));
    }
}

public class calculator
{
    public static void main(String args[])
    {
        int a, b;
        Scanner s = new Scanner(System.in);
        System.out.println("Enter values to be performed arithmetic operations on: ");
        a = s.nextInt();
        b = s.nextInt();
        calc2 c = new calc2();
        calc c1 = c;
        calc3 c2 = new calc3();
        calc c3 = c2;
        c1.addition(a, b);
        c1.subtraction(a,b);
        c1.mul(a,b);
        c3.div(a,b);
    }
}