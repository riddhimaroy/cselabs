class mult implements Runnable
{
    int n;

    mult(int n)
    {
        this.n = n;
    }
    
    public void run()
    {
        System.out.println("mult table is");

        for(int i=0; i<10; i++)
        {
            System.out.println(n*i);
        }
    }
}

public class th1 {
    public static void main(String[] args) {
        
    mult x = new mult(5);
    mult y = new mult(7);
    Thread xx = new Thread(x);
    Thread yy = new Thread(y);

    xx.start();
    yy.start();
    

    try
    {
        xx.join();
        yy.join();
    }

    catch(InterruptedException exc)
    {
        System.out.println("interrupted");
    }
}
}
