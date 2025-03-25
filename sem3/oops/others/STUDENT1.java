import java.util.Scanner;

class STUDENT1 {
    private String name;

    public STUDENT1(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public String extractInitials() {
        String initials = "";
        for (String part : name.split("\\s+")) {
            if (!part.isEmpty()) {
                initials += part.substring(0, 1).toUpperCase();
            }
        }
        return initials;
    }

    public String removeWhitespace() {
        return name.replaceAll("\\s+", "");
    }

    public static String[] subf(STUDENT1[] students, String substring) {
        String[] results = new String[students.length];
        int count = 0;

        for (STUDENT1 student : students) {
            if (student.getName().toLowerCase().contains(substring.toLowerCase())) {
                results[count++] = student.getName();
            }
        }

        String[] ress = new String[count];
        System.arraycopy(results, 0, ress, 0, count);
        return ress;
    }

    public static void alph(STUDENT1[] students) {
        for (int i = 0; i < students.length - 1; i++) {
            for (int j = 0; j < students.length - i - 1; j++) {
                if (students[j].getName().compareToIgnoreCase(students[j + 1].getName()) > 0) {
                    STUDENT1 temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
    }

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        System.out.println("Enter the number of students: ");
        int n = s.nextInt();
        s.nextLine(); 

        STUDENT1[] students = new STUDENT1[n];

        for (int i = 0; i < n; i++) {
            System.out.print("Enter the name of student " + (i + 1) + ": ");
            String name = s.nextLine();
            students[i] = new STUDENT1(name);
        }

        System.out.println("\nInitials of each student:");
        for (STUDENT1 student : students) {
            System.out.println(student.getName() + " -> " + student.extractInitials());
        }
        System.out.println("\nNames without whitespace:");
        for (STUDENT1 student : students) {
            System.out.println(student.getName() + " -> " + student.removeWhitespace());
        }

        System.out.print("\nEnter a substring to search for in the student names: ");
        String substring = s.nextLine();
        String[] containingSubstring = STUDENT1.subf(students, substring);
        System.out.println("Names containing '" + substring + "':");
        for (String name : containingSubstring) {
            System.out.println(name);
        }

        STUDENT1.alph(students);
        System.out.println("\nSorted Student2s:");
        for (STUDENT1 student : students) {
            System.out.println(student.getName());
        }

        s.close();
       
    }
}