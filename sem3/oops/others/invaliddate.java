class InvalidDateException extends Exception{
    public String toString()
    {
        return "date not valid bae";
    }
}

class InvalidMonthException extends Exception{
    public String toString()
    {
        return "no month what";
    }
}

class CurrentDate
{
    int day;
    int month;
    int year;

    void createDate(int day, int month, int year)
    {
        this.day = day;
        this.month = month;
        this.year = year;
    }
}

public class invaliddate
{
    public static void main(String[] args) {
        CurrentDate k = new CurrentDate();
        k.createDate(89, 31, 2005);

        try{
            if(k.day < 1 || k.day > 31)
            {
                throw new InvalidDateException();
            }
            if(k.month < 1 || k.month > 12)
            {
                throw new InvalidMonthException();
            }

            System.out.println("The date printed is " + k.day +"-" + k.month +"-"+k.year);
        }

        catch(InvalidDateException exc)
        {
            exc.printStackTrace();
        }
        catch(InvalidMonthException exc)
        {
            exc.printStackTrace();
        }
    }
}