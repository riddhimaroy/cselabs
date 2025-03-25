import java.util.*;

class idkk
{
    String str;

    idkk()
    {
        this.str="";
    }

    idkk(String s)
    {
        this.str = s;
    }

    String formatEmployeeName(String s)
    {
        String name = "";
        s = s.toLowerCase();
        String [] words = s.split(" ");

        for(String i: words)
        {
            String a = String.valueOf(i.charAt(0));
            name = name + a.toUpperCase() + i.substring(1) + " ";
        }

        return name;
    }

    String generateEmail(String s)
    {
        String email = "";
        String[] w = s.split(" ");
        email = email + String.valueOf(w[0].charAt(0)).toLowerCase() + w[1].toLowerCase() + "@example.com";

        return email;
    }    

    String initials(String s)
    {
        s = s.toUpperCase();
        String [] words = s.split(" ");
        String in ="";

        for(String i: words)
        {
            in = in + i.charAt(0);
        }

        return in;
    }

    String removeWhitespace(String s)
    {
        String [] w = s.split(" ");
        String news = "";

        for(String i: w){
            news = news + i;
        }
        return news;
    }

    void containingSubstring(String[] s, String w)
    {
        for(String i: s)
        {
            int a = i.indexOf(w);

            if(a!=-1)
            {
                System.out.println(i);
            }
        }
    }

    void familyname(String s)
    {
        int i, n;
        String nw ="";
        String[] w = s.split(" ");
        n = w.length;
        for(i=0; i<n-1; i++)
        {
            nw = nw + String.valueOf(w[i].charAt(0)).toUpperCase() + ". ";
        }

        nw = nw + String.valueOf(w[n-1].charAt(0)).toUpperCase() + w[n-1].substring(1);
        System.out.println(nw);
    }

    String nameinit()
    {
        return this.str;
    }

    static void sortname(idkk[] k)
    {
        Arrays.sort(k, Comparator.comparing(idkk::nameinit));

        for(idkk l:k)
        {
            System.out.println(l.str);
        }
    }
}

public class stringsallprog
{
    public static void main (String args[])
    {
        String[] s = {"william", "billy", "phil", "lily", "mitch"};

        idkk[] k = new idkk[3];

        k[0] = new idkk("hi");
        k[1] = new idkk("amul");
        k[2] = new idkk("ri");

        idkk.sortname(k);

        idkk q = new idkk();
        
        q.familyname("riddhima mohan harry styles roy");
    }
}