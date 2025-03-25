import java.util.Scanner;

class factory
{
    int start;
    int end;
    int size;
    int cap;
    String buffer[];
    
    factory(int x)
    {
        start = 0;
        end = 0;
        size = 0;
        cap = x;
        buffer = new String[100];
    }

    Scanner s = new Scanner(System.in);

    public synchronized void produce()
    {
;        try{
            if(size>=cap)
            {
                System.out.println("waiting...");
                wait();
            }
            System.out.println("enter name of to be produced object");
            String x = s.next();
            end++;

            buffer[end] = x;

            notifyAll();

            System.out.println("\nItems in production currently are: ");
            for(int i = start; i<=end; i++)
            {
                System.out.println(buffer[i]);
            }

            size = end - start;
        }

        catch(InterruptedException e)
        {
            System.out.println(e.getMessage());
        }

        
    }

    public synchronized void delete()
    {
        try
        {
            if(size<=0)
            {
                System.out.println("waiting for items");
                wait();
            }
            notifyAll();

            System.out.println("item packaged off is: " + buffer[start]);
            start++;
            size = end - start;

        }
        catch(InterruptedException e)
        {
            System.out.println(e.getMessage());
        }
    }
}

class Manuf extends Thread
{
    factory fact;

    Manuf(factory fact)
    {
        this.fact = fact;
    }

    public void run()
    {
        for(int i = 0; i<20; i++)
        {
            fact.produce();

            try
            {
                Thread.sleep(400);
            }
            catch(InterruptedException e)
            {
                System.out.println(e.getMessage());
            }
        }
    }

}

class Packager extends Thread
{
    factory fact;

    Packager(factory fact)
    {
        this.fact = fact;
    }

    public void run()
    {
        for(int i = 0; i<20; i++)
        {
            fact.delete();

            try
            {
                Thread.sleep(800);
            }
            catch(InterruptedException e)
            {
                System.out.println(e.getMessage());
            }
        }
    }

}

public class multithreading
{
    public static void main(String[] args)
    {
        factory fact = new factory(5);

        Manuf x = new Manuf(fact);
        Packager y = new Packager(fact);

        x.start();
        y.start();
    }
}