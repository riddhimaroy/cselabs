class arrayy<T extends Number>
{
    T a[];
    double avg;

    arrayy(T a[])
    {
        this.a = a;
        avg = 0;
    }

    double avrg(arrayy<?> ob)
    {
        for(int i=0; i<(this.a.length); i++)
        {
            avg = avg + a[i].doubleValue();
        }

        avg = avg / a.length;
        return avg;
    }
}


public class test<T extends Number>
{
    // double avg (?[] arr)
    // {
    //     double av = 0.0;
    //     int len = arr.length;

    //     for(int i =0; i<len; i++)
    //     {
    //         av = av + arr[i].doubleValue();
    //     }
        
    //     av = av/len;
    //     return av;
    // }

    public static void main(String[] args) 
    {
        
        Integer[] x = {1, 2, 3};
        arrayy<Integer> a = new arrayy<Integer>(x);
        System.out.println(a.avrg(x));

        test<Float> b = new test();
        test<Double> c = new test();

        Float[] y = {1.0f, 2.0f, 3.0f};
        System.out.println(b.avg(y));

        Double[] z = {1.0, 2.0, 3.0};
        System.out.println(c.avg(z));
    }
}