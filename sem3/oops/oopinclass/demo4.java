// create multiple threads. use runnable interface. implement logic for adding and multiplying.

class addition implements Runnable {
    private int a, b;

    public addition(int a, int b) {
        this.a = a;
        this.b = b;
    }

    public int a, b;

    @Override
    public void run() {
        int sum = a + b;
        System.out.println("Sum: " + sum);
    }
}

class multiply implements Runnable {
    private int a, b;

    public multiply(int a, int b) {
        this.a = a;
        this.b = b;
    }

    @Override
    public void run() {
        int product = a * b;
        System.out.println("Product: " + product);
    }
}

public class demo4 {
    public static void main(String[] args) {
        Runnable addition = new addition(3, 2);
        Runnable multiply = new multiply(3, 2);

        Thread addThread = new Thread(addition);
        Thread multiplyThread = new Thread(multiply);

        addThread.start();
        multiplyThread.start();
    }
}
