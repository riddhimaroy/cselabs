import java.util.*;

public class trg {
    public static void main(String args[])
    {
        int [][] arr = new int [10][];
        int i;

        for (i=0; i<10; i++)
        {
            arr[i] = new int[i];
        }

        for (i=0; i<10; i++)
        {
            for(int j=0; j<i; j++)
            {
                arr[i][j] = i+j;
            }
        }
        for (i=0; i<10; i++)
        {
            for(int j=0; j<i; j++)
            {
                System.out.print(arr[i][j] + " ");
            }
            
            System.out.println("");
        }
    }
}
