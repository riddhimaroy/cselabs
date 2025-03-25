import java.util.Scanner;
class OnlineShoppingSystem {
private String customerName;
private int customerId;
private String productName;
private int productId;
private double unitPrice;
private int quantity;
private double totalCost;
private static int totalOrders = 0;
private static double discountRate = 0.0;

public OnlineShoppingSystem() {
this.customerName = "";
this.customerId = 0;
this.productName = "";
this.productId = 0;
this.unitPrice = 0.0;
this.quantity = 0;
this.totalCost = 0.0;
}

public OnlineShoppingSystem(String customerName, int customerId, String
productName, int productId, double unitPrice, int quantity) {
    
        this.customerName = customerName;
        this.customerId = customerId;
        this.productName = productName;
        this.productId = productId;
        this.unitPrice = unitPrice;
        this.quantity = quantity;
        this.totalCost = calculateTotalCost();
    totalOrders++;
    }

    public void readOrderDetails() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter customer name: ");
        this.customerName = scanner.nextLine();
        System.out.print("Enter customer ID: ");
        this.customerId = scanner.nextInt();
        scanner.nextLine(); // Consume newline
        System.out.print("Enter product name: ");
        this.productName = scanner.nextLine();
        System.out.print("Enter product ID: ");
        this.productId = scanner.nextInt();
        System.out.print("Enter unit price: ");
        this.unitPrice = scanner.nextDouble();
        System.out.print("Enter quantity: ");
        this.quantity = scanner.nextInt();
        this.totalCost = calculateTotalCost();
        //totalOrders++;
    }

    public void updateQuantity(int newQuantity) {
        this.quantity = newQuantity;
        this.totalCost = calculateTotalCost();
    }

    private double calculateTotalCost() {
        return this.unitPrice * this.quantity;
    }
    public void displayOrderDetails() {
        System.out.println("Customer Name: " + this.customerName);
        System.out.println("Customer ID: " + this.customerId);
        System.out.println("Product Name: " + this.productName);
        System.out.println("Product ID: " + this.productId);
        System.out.println("Unit Price: " + this.unitPrice);
        System.out.println("Quantity: " + this.quantity);
        System.out.println("Total Cost: " + this.totalCost);
}

public static void displayTotalOrders() {
        System.out.println("Total Orders: " + totalOrders);
    }

public static void main(String[] args) {

    OnlineShoppingSystem[] orders = new OnlineShoppingSystem[8];
    Scanner scanner = new Scanner(System.in);

    for (int i = 0; i < orders.length; i++) 
    {
        System.out.println("Enter details for order " + (i + 1) + ":");
        orders[i] = new OnlineShoppingSystem();
        orders[i].readOrderDetails();
    }
    System.out.println("\nOrder Details:");
    for (OnlineShoppingSystem order : orders) {
        order.displayOrderDetails();
    }
    System.out.print("\nEnter the index of the order to update quantity (0-7): ");
    int index = scanner.nextInt();
    System.out.print("Enter new quantity: ");
    int newQuantity = scanner.nextInt();
    orders[index].updateQuantity(newQuantity);
    System.out.println("\nUpdated Order Details:");
    orders[index].displayOrderDetails();
    OnlineShoppingSystem.displayTotalOrders();
    }
}
