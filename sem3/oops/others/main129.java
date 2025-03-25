class student
{
    private String sname;
    private int [] marks_array;
    private int total;
    private float avg;

    student()
    {
        this.sname = "";
        this.marks_array = new int[0];
    }

    student(String s, int[] m)
    {
        this.sname = s;
        this.marks_array = m;
        compute();
    }

    void compute()
    {
        total = 0;
        for (int i: marks_array)
        {
            total = total + i;
        }

        avg = (float)total / marks_array.length;
    }

    void display()
    {
        System.out.println("Name: " + sname);
        System.out.println("Total : " + total);
        System.out.println("Avg: " + avg);
    }

    int getTot()
    {return total;}

    void setTot(int x)
    {
        total = x;
    }

    float getAvg()
    {return avg;}

    void setAvg(float x)
    {
        avg = x;
    }

    int[] getm()
    {return marks_array;}
}

class sci extends student
{
    private int prac;

    sci(String s, int[] m, int prac)
    {
        super(s, m);
        this.prac = prac;
        compute();
    }
    void compute()
    {
        super.compute();
        int a = getTot() + prac;
        setTot(a);
        //float c = ((float)prac / (getm().length + 1));
        float b = ((float)getTot() / (getm().length + 1));
        setAvg(b);
    }
    void displaypr()
    {
        super.display();
        System.out.println("prac: " + prac);
    }
}

class arts extends student{
    private String elec;

    arts(String s, int[] m, String elec)
    {
        super(s, m);
        this.elec = elec;
        super.compute();
    }

    void display()
    {
        super.display();
        System.out.println("Elective: " + elec);
    }
}

class main129
{
    public static void main(String args[])
    {
        int [] m = {1,2,3,4};
        int [] n = {9,2,3,4};

        arts x = new arts("ri", m, "pedo");
        x.display();

        sci y = new sci("kes", n, 10);
        y.displaypr();

    }
}