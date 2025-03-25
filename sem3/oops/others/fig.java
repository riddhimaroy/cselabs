abstract class Figure
{
    int x;
    int y;

    Figure(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
    abstract int area();
}

class Rectangle extends Figure
{
    Rectangle (int x, int y)
    {
        super(x, y);
    }

    int area()
    {
        int r = x*y;
        return r;
    }
}

class Square extends Figure
{
    Square (int x)
    {
        super(x, x);
    }

    int area()
    {
        // if(x!=y)
        // {
        //     System.out.println("wrong");
        //     return 0;
        // }
        // else
        {
            int r = x*x;
            return r;
        }
    }
}

class Triangle extends Figure{

    Triangle (int x, int y)
    {
        super(x, y);
    }

    int area()
    {
        int r = x*y/2;
        return r;
    }
}

class fig
{
    public static void main(String args[])
    {
        Square s = new Square(2);
        System.out.println("Sq area: " + s.area());

        Triangle t = new Triangle(2,6);
        System.out.println("Tri area: " + t.area());
    }
}