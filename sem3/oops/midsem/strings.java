import java.util.*;

class prog
{
    String lala;
    prog(String s)
    {
        this.lala = s;
    }
        static void formatEmployeeName(String s)
    {
        s = s.toLowerCase();
        String[] w = s.split(" ");
        String name;

        for(String i: w)
        {
            char a = i.charAt(0);
            String n = String.valueOf(a).toUpperCase() + i.substring(1);
            System.out.print(n + " ");
        }

    }

    static void generateEmail(String s)
    {
        s = s.toLowerCase();
        String[] w = s.split(" ");
        int n = w.length;

        String name = String.valueOf(w[0].charAt(0));

        for(int i = 1; i<n; i++)
        {
            name = name + w[i];
        }
        name = name + "@gmail.com";
        System.out.println(name);
    }

    static void initials(String s)
    {
        s = s.toUpperCase();
        String[] w = s.split(" ");
        String name = "";

        for(String i: w)
        {
            name = name + String.valueOf(i.charAt(0));
        }
        System.out.println(name);
    }

    String getName()
    {
        return this.lala;
    }

    static void sortname(prog[] k)
    {
        Arrays.sort(k, Comparator.comparing(prog::getName));

        for(prog i: k)
        {
            System.out.println(i.lala);
        }
    }

    static void familyname(String s)
    {
        s = s.toLowerCase();
        String[] w = s.split(" ");

        int n =w.length;
        String name = "";

        for(int i=0; i<n-1; i++)
        {
            name = name + String.valueOf(w[i].charAt(0)).toUpperCase() +". ";
        }

        name = name + String.valueOf(w[n-1].charAt(0)).toUpperCase() + w[n-1].substring(1);
        System.out.println(name);   
}
}

public class strings {
    public static void main(String[] args) 
    {
        String s = "JOHN DOE kamala harris";
        
        //prog.formatEmployeeName(s);
        //prog.generateEmail(s);
        prog.familyname(s);

        prog[] k = new prog[3];

        k[0] = new prog("hi");
        k[1] = new prog("amul");
        k[2] = new prog("ri");

        prog.sortname(k);

    }
}
