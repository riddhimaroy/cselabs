import java.util.*;

class employee {
    String Ename;
    int Eid;
    int Basic;
    float DA;
    float Gross_Sal;
    float Net_Sal;

    employee(String n, int i, int b)
    {
        Ename = n;
        Eid = i;
        Basic = b;
        compute_net_sal();
    }

    void setNetsal(double n)
    {
        Net_Sal = (float)n;
    }

    float getnet()
    {return Net_Sal;}

    void compute_net_sal()
    {
        DA = (float) (0.52 * Basic);
        Gross_Sal = Basic + DA;
        float IT = (float) (0.3 * Gross_Sal);
        Net_Sal = Gross_Sal - IT;
    }

    void display()
    {
        System.out.println("Name: " + Ename);
        System.out.println("Eid: " + Eid);
        System.out.println("Basic: " + Basic );
        System.out.println("Net Salary: " + Net_Sal);
    }
}

class pt extends employee{
    int hrs;
    static double hrate;

    pt(String n, int i, int h, double hr)
    {
        super(n, i, 0);
        this.hrs = h;
        hrate = hr;
        compute_net_sal();
    }

    void compute_net_sal()
    {
        super.setNetsal((double)hrs*hrate);
    }

    void display()
    {
        System.out.println("Name: " + Ename);
        System.out.println("Eid: " + Eid);
        System.out.println("Net Salary: " + Net_Sal);
    }
}

class ft extends employee
{
    int bonus;
    double ded;

    ft(String n, int i,int bas, int b, double d)
    {
        super(n, i, bas);
        this.bonus = b;
        ded = d;
        compute_net_sal();
    }

    void compute_net_sal()
    {
        super.compute_net_sal();
        double a = getnet() + bonus - ded;
        setNetsal(a);
    }

    void display()
    {
        System.out.println("Name: " + Ename);
        System.out.println("Eid: " + Eid);
        System.out.println("Net Salary: " + Net_Sal);
    }
}

public class employee1{
    public static void main(String args[])
    {
        Scanner s = new Scanner(System.in);

        // int n, i, b, c; String a;

        // System.out.println("Enter number of employees");
        // n = s.nextInt();
        
        // employee[] emp = new employee[n];

        // for(i=0; i<n; i++)
        // {
        //     System.out.println("Enter the name of employee");
        //     a = s.next();
        //     System.out.println("Enter the ID: ");
        //     b = s.nextInt();
        //     System.out.println("Enter the basic salary: ");
        //     c = s.nextInt();
        //     emp[i] = new employee(a, b, c);
        // }

        // System.out.println("The details of the employees are: ");
        // for(i=0; i<n; i++)
        // {
        //     emp[i].display();
        // }

        pt x = new pt("ri", 1, 8, 20);
        x.display();

        ft y = new ft("kes", 2, 123, 20, 10);
        y.display();
    }
}
