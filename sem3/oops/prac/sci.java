package prac;

public class sci extends stu
{
    int pract;
    sci(String a, int b, int c)
    {
        super(a, b);
        pract = c;
    }

    @Override
    int compute() 
    {
        int x = super.compute();
        x = x + pract;

        return x;
    }

    void display()
    {
        System.out.println("hi " + this.compute());
    }
}
