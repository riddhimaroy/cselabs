import java.util.*;

class shop {
    private String customerName;
    private double unitPrice;
    private int quantity;
    private static int totalOrders;
    private double discountRate;

    shop()
    {
        this.customerName = "";
        this.unitPrice = 0;
        this.quantity = 0;
        this.totalOrders = 0;
        this.discountRate = 0;
    }

    shop(String customerName, int customerId, String productName, int productId, double unitPrice, int quantity, int totalOrders, double discountRate)
    {
        this.customerName = customerName;
        this.unitPrice = unitPrice;
        this.quantity = quantity;
        this.totalOrders = totalOrders;
        this.discountRate = discountRate;
    }

    void readOrderDetails()
    {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter name: ");
        this.customerName = s.next();
        System.out.println("Enter unit price: ");
        this.unitPrice = s.nextInt();
        System.out.println("Enter the quantity: ");
        this.quantity = s.nextInt();
        System.out.println("Enter discount: ");
        this.discountRate = s.nextDouble();
        totalOrders++;
    }

    void updateQuantity(int x)
    {
        quantity = x;
    }

    void displayOrderDetails()
    {
        System.out.println(this.customerName);
        System.out.println(this.quantity);
        double c = (double) this.quantity * (double) this.unitPrice;
        System.out.println("Total Price: " + c);
    }

    static void displayTotalOrders()
    {
        System.out.println("Total Orders: " + totalOrders);
    }

    public static void main(String args[])
    {
        Scanner s = new Scanner(System.in);
        shop [] list = new shop[8];
        for(int i = 0; i<2; i++)
        {
            list[i] = new shop();
            list[i].readOrderDetails();
        }

        for (int i=0; i<2; i++)
        list[i].displayOrderDetails();
        
        list[1].updateQuantity(3);

        for (int i=0; i<2; i++)
        list[i].displayOrderDetails();

        displayTotalOrders();
    }
}
