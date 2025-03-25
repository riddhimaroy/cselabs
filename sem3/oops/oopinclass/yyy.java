import java.util.Scanner;
import java.lang.Math;

interface in{
    void add(int x, int y);
    void root(int x);
}

class xxx implements in {
    public void add(int x, int y)
    {
        System.out.println(x+y);
    }
    public void root(int x)
    {
        System.out.println(Math.sqrt(x));
    }
}

public class yyy {
    public static void main(String[] args)
    {
        xxx x1= new xxx();
        in a = x1;
        a.add(2,4);
        a.root(64);
    }
}
