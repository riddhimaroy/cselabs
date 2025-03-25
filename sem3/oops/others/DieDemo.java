import java.util.*;

class Die
{
    int sideUp;

    void getSideUp()
    {
        Random rand = new Random();
        this.sideUp = rand.nextInt(1,7);
    }
}

public class DieDemo{
    public static void main(String[] args) {
        Die d1 = new Die();
        Die d2 = new Die();
        d1.getSideUp();
        d2.getSideUp();

        System.out.println(d1.sideUp + " " +d2.sideUp);
    }
}