import java.util.*;

class projass
{
    String ename;
    String proj;
    int start;
    int end;
    int count =0;

    projass(String e, String p, int s, int en)
    {
        this.ename = e;
        this.proj = p;
        this.start = s;
        this.end = en;
        this.count++;
    }
}

class company
{
    Scanner s = new Scanner(System.in);

    void read(projass[] lis)
    {
       // projass[] lis = new projass[n];
        int n = lis.length;
        int i;

        for(i=0; i<n; i++)
        {
            System.out.println("Enter name: ");
            String a = s.next();
            System.out.println("Proj name: ");
            String b = s.next();
            System.out.println("Start date: ");
            int c = s.nextInt();
            System.out.println("End date: ");
            int d = s.nextInt();
            lis[i] = new projass(a, b, c, d);
        }
    }

    void display(projass[] lis)
    {
        int i, n;

        n = lis.length;

        for(i=0; i<n; i++)
        {
            System.out.println(lis[i].ename);
            System.out.println(lis[i].proj);
            System.out.println(lis[i].start);
            System.out.println(lis[i].end + "\n");
        }
    }
}

class abc extends projass{

    static int slim;

    abc(String s, String t, int r, int u)
    {
        super(s, t, r, u);
    }

    static void getslim(int n)
    {
        slim = n;
    }

    void check()
    {
        if(slim<super.count)
        {
            System.out.println("Entered employees is more than set limit.");
        }
    }

    

    //String 
}

public class pranprac {

    public static void main(String[] args) {

        int n;

        System.out.println("Enter the number of employees");
        n = 1;
        projass[] lis = new projass[n];

        company k = new company();
        k.read(lis);
        k.display(lis);
        abc.getslim(2);

        abc d = new abc("", "", 0, 0);
        d.check();
    }
    
}
