import java.util.*;

class arr<T>
{
    T ar[];

    arr(T a[])
    {
        ar = a;
    }

    void swap(int a, int b)
    {
        T temp = ar[a];
        ar[a] = ar[b];
        ar[b] = temp;

    }
}

public class gen1 {
    public static void main(String[] args) {

        Integer[] y = {1,2,3};
        arr<Integer> x = new arr<Integer>(y);

        x.swap(1,2);
        for(int i:x.ar)
            System.out.println(i);
    }
}
