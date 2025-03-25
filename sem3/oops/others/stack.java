import java.util.*;

public class stack {
    int tos;
    int[] stk;
    int cap;

    stack()
    {
        this.tos = 0;
        this.stk = new int[0];
        this.cap = 0;
    }

    stack(int tos, int[] stk, int cap)
    {
        this.tos = tos;
        this.stk = stk;
        this.cap = cap;
    }

    void initos()
    {
        tos = -1;
    }

    void pop()
    {
        if(tos==-1)
        {
            System.out.println("Stack underflow!!");
            System.out.println(tos);
        }
        else
        {
            System.out.println("Popped " + stk[tos]);
            tos--;
            
        }
    }

    void push(int x)
    {
        if(tos == cap-1)
        {
            System.out.println("Stack overflow");
        }
        else
        {
            //System.out.println(tos);
            tos++;
            stk[tos] = x;
        }
    }

    void display()
    {
        int i;
        for(i=tos; i>=0; i--)
        {
            System.out.println(stk[i]);
        }
    }

    public static void main(String[] args) 
    {
        Scanner s = new Scanner(System.in);
        stack x = new stack();

        System.out.println("Enter the capacity");
        x.cap = s.nextInt();
        x.stk = new int[x.cap];
        x.initos();
        x.pop();
        x.push(4);
        x.push(5);
        x.push(6);
        x.display();
    }
}
