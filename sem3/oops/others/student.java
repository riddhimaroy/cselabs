import java.util.Scanner;

public class student {
    private String sname;
    private int[] marks_array;
    private int total;
    private float avg;

    void assign(String sname, int[] marks_array)
    {
        this.sname= sname;
        this.marks_array=marks_array;
        compute();
    }

    void compute()
    {
        for(int i: this.marks_array)
        {
            this.total = this.total + i;
        }
        this.avg = (float)this.total/this.marks_array.length;
    }

    void display()
    {
        System.out.println("Student Details:");
        System.out.println("Name: "+ this.sname);
        System.out.println("Total: "+ this.total);
        System.out.println("Average Marks: " + this.avg);
    }

    public static void main(String args[])
    {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter the marks");
        int[] marks = new int[4];
        String name = "ri";
        for(int i=0; i<4; i++)
        {
            marks[i] = s.nextInt();
        }
        student x = new student();
        x.assign(name, marks);
        x.display();
    }
}
