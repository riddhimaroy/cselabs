class ThrowDemo{
    publix static void main(String args[])
    {
        try{
            System.out.println("Before throw");
            throw new ArithmeticException();
        }
        catch (ArithmeticException exc)
        {
            System.out.println("Exception Caught");
        }
        System.out.println("After try/catch block");
    }
}