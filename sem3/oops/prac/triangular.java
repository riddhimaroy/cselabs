import java.util.*;

public class triangular {
    public static void main(String[] args)
    { 
        int a[][] = new int[10][];

        for(int i=0; i<10; i++)
        {
            a[i] = new int[i+1];
            for(int j = 0; j<i+1; j++)
                a[i][j] = i+j;
        }

        for(int i=0; i<10; i++)
        {
            for(int j = 0; j<i+1; j++)
                System.out.print(a[i][j] + " ");
            System.out.println("");
        }
    }
}
