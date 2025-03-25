import java.util.Scanner;

class student {
    private String sname;
    private int[] marks_array;
    private int total;
    private float avg;

    student(String sname, int[] marks_array)
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

    int getTot()
    {
        return this.total;
    }

    float getAvg()
    {
        return this.avg;
    }

    int[] getMarks()
    {
        return this.marks_array;
    }

    void display()
    {
        System.out.println("Student Details:");
        System.out.println("Name: "+ this.sname);
        System.out.println("Total: "+ this.total);
        System.out.println("Average Marks: " + this.avg);
    }
}

class sci extends student{
    int prac;
    int totall;
    float avgg;

    sci(String sname, int[] marks_array, int prac)
    {
        super(sname, marks_array);
        this.prac = prac;
        compute();
    }

    void compute()
    {
        super.compute();
        this.totall = super.getTot() + this.prac;
        this.avgg = (float)this.totall/(super.getMarks().length+1);
    }

    void display()
    {
        //super.display();
        System.out.println("Total: " + this.totall);
        System.out.println("Avg: " + this.avgg);
        displayprac();
    }

    void displayprac()
    {
        System.out.println("The practical marks are: " + this.prac);
    }
}

class arts extends student{
    String elec;

    arts(String sname, int[] marks_array, String elec)
    {
        super(sname, marks_array);
        this.elec = elec;
    }
}

class stumain
{
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
        sci x = new sci(name, marks, 100);
        //student x = new student(name, marks);
        //x.assign(name, marks);
        x.display();
        System.out.println(x.getTot());
       // x.displayprac();
    }
}

