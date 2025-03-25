import java.util.*;

class tri{
    public static void trii(int n)
    {
        int [][] arr = new int[n][];

        for(int i=0; i<n; i++)
        {
            arr[i] = new int[i+1];

            for(int j = 0; j<=i; j++)
            {
                arr[i][j] = i+j;
            }
        }

        System.out.println("the matrix is: ");
        for(int[] m: arr)
        {
            for(int p: m)
            {
                System.out.print(p);
            }
            System.out.println("");
        }
    }
}

public class triangular {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter number of elements");
        int n = s.nextInt();
        
        tri.trii(n);
    }
}
