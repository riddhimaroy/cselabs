import java.util.*;

class reverse
{
    public static int reverse(int n)
    {
        int rem;
        int rev = 0;
        while(n>0)
        {
            rev = rev*10;
            rem = n % 10;
            rev = rev + rem;
            n = n/10;
        }
        return rev;
    }
//}

//public class rev {
    public static void main(String[] args)
    {
        Scanner s = new Scanner(System.in);

        System.out.println("Enter a number:");
        int n = s.nextInt();

        r k = new r();

        int rev = reverse(n);
        System.out.println(rev);
    }    
}
