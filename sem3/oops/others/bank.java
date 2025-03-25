import java.util.*;

public class bank {
    String name;
    int bal;
    static int roi;

    bank()
    {
        this.name = "";
        this.bal = 0;
        this.roi = 0;
    }

    bank(String name, int bal, int roi)
    {
        this.name = name;
        this.bal = bal;
        this.roi = roi;
    }

    void deposit(int x)
    {
        this.bal = this.bal + x;
    }
    
    void withdraw(int x)
    {
        if((this.bal-x)<500)
        System.out.println("Balance too low");
        else
        this.bal = this.bal - x;
    }

    void display()
    {
        System.out.println("Name: " + this.name);
        System.out.println("Balance: " + this.bal);
    }

    static void droi()
    {
        System.out.println("ROI: " + roi + "%");
    }

    public static void main(String args[])
    {
        bank x = new bank("ri", 5000, 5);
        x.deposit(100);
        x.display();
        x.withdraw(6000);
        x.withdraw(200);
        x.display();
        droi();
    }
}
