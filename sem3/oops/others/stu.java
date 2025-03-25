import java.util.*;

public class stu{
    
    private String name;
    private int reg;
    private int[] marks;

    stu()
    {
        this.name = "";
        this.reg = 0;
        this.marks = new int[0];
    }

    stu(String name, int reg, int[] marks)
    {
        this.name = name;
        this.reg = reg;
        this.marks = marks;
    }

    void display()
    {
        System.out.println("Name: " + this.name);
        System.out.println("Roll No.: " + this.reg);
        System.out.println("Marks: ");
        for(int i=0; i<this.marks.length; i++)
        {
            System.out.println(this.marks[i]);
        }
    }

    public static void main(String[] args)
    {
        //int [] arr = new int[3];
        int[] arr = {1,2,3};
        stu x = new stu("ri", 1, arr);
        x.display();
    }
}