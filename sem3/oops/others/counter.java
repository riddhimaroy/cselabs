import java.util.*;

public class counter {

    static int n=0;

    counter()
    {
        n++;
    }

    void sc()
    {
        System.out.println("number of objects made is: " + n);
    }

    public static void main(String[] args)
    {
        counter a = new counter();
        a.sc();
        counter b = new counter();
        a.sc();
        b.sc();
        counter c = new counter();
        c.sc();
    }
}
