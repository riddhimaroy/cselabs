import java.util.*;

public class employee {
    String Ename;
    int Eid;
    double Basic;
    double DA;
    double Gross_Sal;
    double Net_Sal;

    public employee()
    {
        this.Ename="";
        this.Eid=0;
        this.Basic=0;
        this.DA=0;
        this.Gross_Sal=0;
        this.Net_Sal=0;
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
        compute_net_sal();
    }

    void compute_net_sal()
    {
        this.DA = 0.52 *  this.Basic;
        this.Gross_Sal = this.Basic + this.DA;
        double IT = 0.3 * this.Gross_Sal;
        this.Net_Sal = this.Gross_Sal - IT;
    }

    void display()
    {
        System.out.println("Name: " + this.Ename);
        System.out.println("Eid: " + this.Eid);
        System.out.println("Basic: " + this.Basic );
        System.out.println("Net Salary: " + this.Net_Sal);
    }

    public static void main(String args[])
    {
        int i;

        Scanner s = new Scanner(System.in);
        System.out.println("Enter the number of employees to be entered");
        int n = s.nextInt();
        employee[] emp = new employee[n];

        for (i=0; i<n; i++)
        {
            int x = i+1;
            System.out.println("Employee "+ i);
            emp[i] = new employee();
            emp[i].read();
        }

        for(i=0; i<n; i++)
        {
            System.out.println("Employee " + i+1);
            emp[i].display();
        }
    }
}
