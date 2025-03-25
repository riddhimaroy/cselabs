class phone
{
    String brand;
    int memcapacity;

    phone(String s, int i)
    {
        this.brand = s;
        this.memcapacity = i;
    }

    interface Callable
    {
        void makeAudioCall(String cellNum);
        void makeVideoCall(String cellNum);
    }
}

class BasicPhone extends phone implements phone.Callable
{
    BasicPhone(String b, int m)
    {
        super(b, m);
    }

    public void makeAudioCall(String cellNum)
    {
        System.out.println("making call");
    }

    // public void makeVideoCall(String cellNum)
    // {
    //     System.out.println("not making call");
    // }
}

public class phonemain {
    public static void main(String [] args) 
    {
        BasicPhone x = new BasicPhone("vivo", 999);
        x.makeAudioCall("77");
        //x.makeVideoCall("98");
    }
}
