import java.util.*;
interface in1
{
    void add(int a, int b);
    void sub(int a, int b);
    void mul(int a, int b);
    //void div(int a, int b);
}

interface in2 extends in1{
    void div(int a, int b);
}

class c1 implements in1{
    public void add(int a, int b)
    {
        int c = a + b;
        System.out.println(c);
    }

    public void sub(int a, int b)
    {
        int c = a - b;
        System.out.println(c);
    }

    public void mul(int a, int b)
    {
        int c = a * b;
        System.out.println(c);
    }
    public void div(int a, int b)
    {
        int c = a / b;
        System.out.println(c);
    }

}

public class demo2{
    public static void main(String args[])
    {
        c1 c2 = new c1();
        // in1 c1;
        // in2 i2;
        // c1 = 
        c2.add(4,5);
        c2.sub(4,1);
        c2.mul(2,3);
        c2.div(6,3);
    }
}