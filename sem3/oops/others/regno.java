import java.util.*;

class student
{
    String regno;
    String name;
    int yoj;
    // short sem;
    // float gpa;
    // float cgpa;
    int count =0;

    student(int yoj, String name)
    {
        this.yoj = yoj;
        this.name = name;
        this.count++;
        computereg();
    }

    void computereg()
    {
        String a = "";
    //    a = String.valueOf(yoj).substring(2,4) + this.count;
        this.regno = a;
    }

    void display()
    {
        System.out.println("name: " + this.name + "\nRegno: " + this.regno);
    }
    String nameinit()
    {
        return name;
    }

}

class regno{

    static void sortname(student[] k)
    {
        Arrays.sort(k, Comparator.comparing(student::nameinit));
    }
    public static void main(String args[])
    {
        Scanner s = new Scanner(System.in);
        student[] k = new student[4];
        student temp = new student(0, "");
        for(int i =0; i<4; i++)
        {
            String a = s.next();
            k[i] = new student(i,a);
        }

        // for(int i=0; i<4; i++)
        // {
        //     for(int j=0; j<i; j++)
        //     {
        //         if(k[j].name.compareTo(k[j+1].name)>=0)
        //         {
        //             temp = k[j+1];
        //             k[j+1] = k[j];
        //             k[j] = temp;
        //         }
        //     }
        // }
        
        sortname(k);

        for(int i =0; i<4; i++)
        {
            k[i].display();
        }
    }
        
}