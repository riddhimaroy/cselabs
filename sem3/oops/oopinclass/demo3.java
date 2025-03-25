import java.util.*;
interface in1
{
    void add(int a, int b);
}

interface in2 extends in1{
    void sub(int a, int b);
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
}

public class demo3{
    public static void main(String args[])
    {
        c1 c = new c1();
        in1 i1;
        in2 i2;
        i2 = c;
        i1 = c;
    
        i1.add(4,5);
        i2.sub(4,3);
    }
}