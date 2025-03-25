class student
{
    private String name;
    private int id;

    student (String n, int i)
    {
        this.name = n;
        this.id = i;
    }

    String getName()
    {return name;}

    int getId()
    {return id;}
}

class Sports extends student{
    private int s_grade;

    Sports(String n, int i, int s)
    {
        super(n, i);
        this.s_grade = s;
    }

    int getS()
    {return s_grade;}
}

class Exam extends student{
    private int e_grade;

    Exam(String n, int i, int s)
    {
        super(n, i);
        this.e_grade = s;
    }
    int getE()
    {return e_grade;}
}

class Results extends Sports
{
    String fresult;
    Exam x;

    Results(String n, int i, int s, int e)
    {
        super(n, i, s);
        x = new Exam(n, i, e);
    }

    void display()
    {
        System.out.println("Name: " + this.getName());
        System.out.println("Id: " + this.getId());
        System.out.println("S grade: " + this.getS());
        System.out.println("E grade: " + x.getE());
    }
}

class stud
{
    public static void main(String[] args) {
        Results a = new Results("ri", 22, 1, 2);
        a.display();
    }
}