class student
{
    int rollno;
    int marks;

    int getNumber()
    {
        return rollno;
    }
    void putnumber(int x)
    {
        rollno = x;
    }

    int getMarks()
    {
        return rollno;
    }
    void putMarks(int x)
    {
        rollno = x;
    }
}

interface Sports
{
    int grade;

    void putgrade(int x);
        //grade = x;
    

    int getgrade();
      //  return this.grade;
    
}

public class result implements Sports extends student {
    public int getgrade()
    {
        return this.grade;
    }
}
