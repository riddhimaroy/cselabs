// add sub mult div in in1, log expo in in2. 

import java.util.*;
import java.lang.Math;

interface in1
{
    void add(int x, int y);
    void sub(int x, int y);
    void mul(int x, int y);
    void div(int x, int y);
}

interface in2 extends in1{
    void expo(int x, int y);
    void log(int x);
}

class inc implements in2{
    public void add(int x, int y)
    {
        System.out.println(x+y);
    }
    public void sub(int x, int y)
    {
        System.out.println(x-y);
    }
    public void mul(int x, int y)
    {
        System.out.println(x*y);
    }
    public void div(int x, int y)
    {
        System.out.println(x/y);
    }
    public void expo(int x, int y)
    {
        System.out.println(Math.pow(x, y));
    }
    public void log(int x)
    {
        System.out.println(Math.log(x));
    }
}

public class inf{
    public static void main(String args[])
    {
        inc p = new inc();
        p.add(16,4);
        p.sub(16,4);
        p.mul(16,4);
        p.div(16,4);
        p.expo(16,4);
        p.log(16);
    }
}