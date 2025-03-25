import java.util.*;
    
public class empcons 
{
    String Ename;
    int Eid;
    float Basic;
    float DA;
    float Gross_Sal;
    float Net_Sal;

    empcons()
    {
        Ename = "";
        Eid = 0;
        Basic = 0;
    }

    empcons(String e, int i, float b)
    {
        this.Ename = e;
        this.Eid = i;
        this.Basic = b;
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

        empcons []emp = new empcons[n];

        for(int i = 0; i<n; i++)
        {
           // emp[i] = new empcons();
            System.out.println("For employee "+(i+1));
            //Scanner s = new Scanner(System.in);

        System.out.println("enter the name:");
        String Ename = s.next();

        System.out.println("enter the reg no:");
        int Eid = s.nextInt();

        System.out.println("enter the basic salary:");
        float Basic = s.nextFloat();

        emp[i] = new empcons(Ename, Eid, Basic);
        }

        for(int i = 0; i<n; i++)
        {
            emp[i].display();
        }
    }
}
