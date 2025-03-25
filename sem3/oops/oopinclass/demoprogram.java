package oopinclass;
abstract class demo1
{
    int x = 2;

    void print()
    {
        System.out.println(x);
    }
    abstract void show(int x);
}

class demo2 extends demo1
{
    void show(int x)
    {
        System.out.println(x);
    }
}

class demoprogram
{
    public static void main(String args[])
    {
        demo2 d = new demo2();
        demo1 d1 = d;
        d1.print();
        d1.show(5);
    }
}