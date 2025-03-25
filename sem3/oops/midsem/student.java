import java.util.*;

public class student {
    String sname;
    int[] marks_array;
    int total;
    float avg;

    void assign(String s, int[] m)
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

    public static void main(String[] args) {
        student stu = new student();
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

        stu.assign(name, arr);
        stu.display();
    }
}
