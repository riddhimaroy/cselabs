import java.util.*;

public class emp
{
    String Ename;
    int Eid;
    double Basic;

    emp()
    {
        this.Ename = "";
        this.Eid = 0;
        this.Basic = 0;
    }

    emp(String Ename, int Eid, double Basic)
    {
        this.Ename = Ename;
        this.Eid = Eid;
        this.Basic = Basic;
    }

    void read()
    {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter the name of employee");
        this.Ename = s.next();
        System.out.println("Enter the ID: ");
        this.Eid = s.nextInt();
        System.out.println("Enter the basic salary: ");
        this.Basic = s.nextInt();
    }

    void display()
    {
        System.out.println(this.Ename);
        System.out.println(this.Eid);
        System.out.println(this.Basic);
    }

    public static void main(String args[])
    {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter the number of employees");
        int n = s.nextInt();
        emp[] employee = new emp[n];

        for(int i=0; i<n; i++)
        {
            employee[i] = new emp();
            employee[i].read();
        }

        for(int i=0; i<n; i++)
        employee[i].display();
    }
}