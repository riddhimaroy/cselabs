package mypackage.p1;

public class maximum {
    public int max(int a, int b, int c)
    {
        if(a>b && a>c)
        return a;
        else if(b>a && b>c)
        return b;
        else
        return c;
    }

    public double max(double a, double b, double c)
    {
        if(a>b && a>c)
        return a;
        else if(b>a && b>c)
        return b;
        else
        return c;
    }

    int max(int[] n)
    {
        int l = n.length;
        int large = 0;
        for(int i=0; i<l; i++)
        {
            large = n[i];
            for(int j = i; j<l ; j++)
            {
                if(large<n[j])
                {
                    large = n[j];
                }
            }
        }
        return large;
    }
}
