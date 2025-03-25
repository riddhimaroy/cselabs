class abc
{
    int x = 23;
    void show()
    {
        System.out.println(x);
        }
}
class abc1 extends abc
{
    int y = 32;
    void show()
    {
        System.out.println(y);
    }
}

class abcdemo
{
    public static void main(String args[])
    {
        abc a = new abc();
       // a.x=3;
        // System.out.println(a.x);
        a.show();
        abc1 a1 = new abc1();
        a1.show();
    }
}