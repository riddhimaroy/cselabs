import java.util.*;

class stuconstr {
    String sname;
    int[] marks_array;
    private int total;
    float avg;

    stuconstr(String s, int[] m)
    {
        this.sname = s;
        this.marks_array = m;
        compute();
    }

    void compute()
    {
        int n = marks_array.length;
        int sum = 0;

        for(int i = 0; i<n; i++)
        {
            sum = sum + marks_array[i];
        }

        this.total = sum;
        this.avg = (float)sum / n;
    }

    void display()
    {
        System.out.println("Student details:");
        System.out.println("Name: " + sname);
        System.out.println("Total Marks: " + total);
        System.out.println("Avg Marks: " + avg);
    }

    int GetTotal()
    {
        return this.total;
    }

    void SetTotal(int x)
    {
        this.total = x;
    }

    float getAvg()
    {
        return avg;
    }
}

class SciStu extends stuconstr
{
    int prac;

    SciStu(String s, int[] m, int p)
    {
        super(s, m);
        this.prac = p;
        compute();
    }

    void compute()
    {
        super.compute();
        int total = super.GetTotal() + this.prac;
        SetTotal(total);
        this.avg = total / (marks_array.length);
    }

    void display()
    {
        super.display();
        System.out.println("prac marks: " + prac);
    }
}

public class stuinh
{    public static void main(String[] args) {
        
        Scanner s = new Scanner(System.in);

        System.out.println("What is ur name lil bro");
        String name = s.next();
        System.out.println("how many subjects lil bro");
        int x = s.nextInt();

        int[] arr = new int[x];

        for(int j = 0; j<x; j++)
        {
            System.out.println("Enter the marks of sub " + (j+1));
            arr[j] = s.nextInt();
        }

        SciStu stu = new SciStu(name, arr, 50);

        //stu.assign(name, arr);
        stu.display();
    }
}
