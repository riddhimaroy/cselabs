import java.util.*;

public class mixer {
    int arr[];

    public void accept()
    {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter limit of array");
        int l = s.nextInt();
        this.arr = new int[l];

        System.out.println("Enter elements into array");

        for(int i=0; i<l; i++)
        {
            this.arr[i] = s.nextInt();
        }
        Arrays.sort(this.arr);
    }

    mixer mix(mixer a)
    {
        int [] merge = new int[a.arr.length + this.arr.length];
        int i=0, j=0, k=0;

        while(i<this.arr.length && j<a.arr.length)
        {
            if(this.arr[i]<a.arr[j])
            {
                merge[k]=this.arr[i];
                k++;
                i++;
            }
            else
            {
                merge[k]=a.arr[j];
                k++;
                j++;
            }

            if(this.arr.length<a.arr.length)
            {
                while(j<a.arr.length)
                {
                    merge[k]=a.arr[j];
                    k++;
                    j++;
                }
            }
            else
            {
                while(i<this.arr.length)
                {
                    merge[k]=this.arr[i];
                    k++;
                    i++;
                }
            }
        }
        mixer res = new mixer();
        res.arr = merge;
        return res;
    }

    void display()
    {
        System.out.println("The merged array is");
        for(int p: this.arr)
        {
            System.out.println(p);
        }
    }

    public static void main(String args[])
    {
        Scanner s = new Scanner(System.in);

        mixer m1 = new mixer();
        mixer m2 = new mixer();
        mixer merge = new mixer();

        m1.accept();
        m2.accept();
        merge = m1.mix(m2);
        merge.display();

    }
}
