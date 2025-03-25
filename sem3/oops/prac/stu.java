package prac;

public class stu {
    
        String name;
        int rollno;
    
        stu()
        {
            name = "";
            rollno = 0;
        }
    
        stu(String a, int b)
        {
            name = a;
            rollno = b;
        }
    
        int compute()
        {
            int x = this.rollno*100;
            return x;
        }
    
}
