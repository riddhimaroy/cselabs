class person
{
    private String name;
    private int dob;

    person(String n, int m)
    {
        this.name = n;
        this.dob = m;
    }

    String getName()
    {
        return name;
    }

    int getDob()
    {
        return dob;
    }
}

class colgrad extends person
{
    private int gpa;
    private int year;

    colgrad(String n, int dob, int gpa, int year)
    {
        super(n, dob);
        this.gpa = gpa;
        this.year = year;
    }

    void display()
    {
        System.out.println("Name: " + getName());
        System.out.println("Dob: " + getDob());
        System.out.println("Gpa: " + this.gpa);
        System.out.println("Year: " + this.year);
    }
}

class person1
{
    public static void main(String args[])
    {
        colgrad x = new colgrad("ri", 10, 9, 2023);
        x.display();
    }
}