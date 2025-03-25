import java.util.*;
    
public class employee 
{
    String Ename;
    int Eid;
    float Basic;
    float DA;
    float Gross_Sal;
    float Net_Sal;

    void read()
    {
        Scanner s = new Scanner(System.in);

        System.out.println("enter the name:");
        this.Ename = s.next();

        System.out.println("enter the reg no:");
        this.Eid = s.nextInt();

        System.out.println("enter the basic salary:");
        this.Basic = s.nextFloat();

        compute_net_sal();
    }

    void compute_net_sal()
    {
        DA = (float)0.52 * Basic;
        Gross_Sal = DA + Basic;
        float IT = (float) (0.3 * Gross_Sal);
        Net_Sal = Gross_Sal - IT;
    }

    void display()
    {
        System.out.println("Name: " + Ename);
        System.out.println("ID: " + Eid);
        System.out.println("Salary: " + Net_Sal);
    }

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        System.out.println("Enter number of employees: ");
        int n = s.nextInt();

        employee []emp = new employee[n];

        for(int i = 0; i<n; i++)
        {
            emp[i] = new employee();
            System.out.println("For employee "+(i+1));
            emp[i].read();
        }

        for(int i = 0; i<n; i++)
        {
            emp[i].display();
        }
    }
}
