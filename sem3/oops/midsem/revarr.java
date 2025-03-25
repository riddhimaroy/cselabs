
import java.util.Scanner;

class r
{
    void reverse(int[] n)
    {
        int x = n.length;
        int i;
        int [] n1 = new int[x];

        for(i=0; i<x; i++)
        {
            n1[i] = n[x-i-1];
        }

        System.out.println("The reversed matrix is: ");
        for(int j: n1)
        {
            System.out.println(j);
        }
    }
}
public class revarr {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter the number of elements in array");
        int x = s.nextInt();
        int [] n = new int[x];

        for(int i =0; i<x; i++)
        {
            n[i] = s.nextInt();
        }

        r k = new r();
        k.reverse(n);

    }    
}
