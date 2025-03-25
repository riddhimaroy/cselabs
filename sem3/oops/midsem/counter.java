public class counter {
    static int c;

    counter()
    {
        (this.c)++;
    }

    public static void showCount()
    {
        System.out.println(c);
    }
    
    public static void main(String[] args) {
        showCount();
        counter a = new counter();
        showCount();
        counter b = new counter();
        showCount();
    }
}
