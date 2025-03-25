interface Series
{
    int getNext();
    void reset();
    void setStart(int x);

}

class byTwos implements Series{

    int current;
    int start;
    
    byTwos()
    {
        current = 0;
        start = 0;
    }

    public int getNext()
    {
        return current = current + 2;
    }

    public void reset()
    {
        current = start;
    }
    public void setStart(int x)
    {
        start = x;
        reset();
    }
}

public class ifseries {
    public static void main(String[] args) {
        byTwos k = new byTwos();

        System.out.println(k.getNext());
        k.setStart(5);
        System.out.println(k.getNext());

    }
    
}
