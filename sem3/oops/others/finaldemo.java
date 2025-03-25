class Logic{

}

class finaldemo{
    public static void main(String [] args)
    {
        Logic l = new Logic();
        Thread t1 = new Thread(new Runnable)
        {
            public void run{
                try
                {
                    for(int i=0; i<10; i++)
                        l.cal();
                        
                    
                }
                Thread.sleep(1000);
            } 
            catch (InterruptedException e)
            {
                e.printStackTrace();
            }
        }
    }
}