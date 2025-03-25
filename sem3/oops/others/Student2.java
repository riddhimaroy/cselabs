import java.util.Scanner;

class Student2 {
    // Fields representing the student record
    private int reg;
    private String fullName;
    private int doj;
    private int moj;
    private int yoj;
    private int sem;
    private float gpa;
    private float cgpa;

    // Static counter to keep track of the number of students for generating registration numbers
    private static int sc = 0;

    // Parameterized constructor
    public Student2(String fullName, int day, int month, int year, int sem, float gpa, float cgpa) {
        this.fullName = fullName;
        this.doj = day;
        this.moj = month;
        this.yoj = year;
        this.sem = sem;
        this.gpa = gpa;
        this.cgpa = cgpa;

        // Increment student counter and generate registration number
        sc++;
        this.reg = genreg(year, sc);
    }

    // Method to generate registration number based on the year of joining and the student count
    private static int genreg(int year, int count) {
        int yp = year % 100; // Get the last two digits of the year
        return yp * 100 + count; // Combine year and count for registration number
    }

    // Display method to show the student record
    public void display() {
        System.out.println("Registration Number: " + reg);
        System.out.println("Full Name: " + fullName);
        System.out.println("Date of Joining: " + doj + "-" + moj + "-" + yoj);
        System.out.println("Semester: " + sem);
        System.out.println("GPA: " + gpa);
        System.out.println("CGPA: " + cgpa);
        System.out.println("-----------------------------");
    }

    public static void sort1(Student2[] students) {
        for (int i = 0; i < students.length - 1; i++) {
            for (int j = 0; j < students.length - i - 1; j++) {
                // First, compare by semester
                if (students[j].sem > students[j + 1].sem) {
                    swap(students, j, j + 1);
                } else if (students[j].sem == students[j + 1].sem) {
                    // If semesters are equal, compare by CGPA
                    if (students[j].cgpa < students[j + 1].cgpa) {
                        swap(students, j, j + 1);
                    }
                }
            }
        }
    }

    // Method to sort student records with respect to name
    public static void sort2(Student2[] students) {
        for (int i = 0; i < students.length - 1; i++) {
            for (int j = 0; j < students.length - i - 1; j++) {
                if (students[j].fullName.compareToIgnoreCase(students[j + 1].fullName) > 0) {
                    swap(students, j, j + 1);
                }
            }
        }
    }

    // Utility method to swap two students in an array
    private static void swap(Student2[] students, int i, int j) {
        Student2 temp = students[i];
        students[i] = students[j];
        students[j] = temp;
    }


    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        System.out.println("Enter number of students");
        int n = s.nextInt(); // Minimum of 5 students as required

        // Array to store student records
        Student2[] students = new Student2[n];

        // Input the student records
        for (int i = 0; i < n; i++) {
            System.out.println("Enter details for student " + (i + 1) + ":");
            System.out.print("Full Name: ");
            String fullName = s.nextLine();

            System.out.print("Enter date of joining (day month year): ");
            int day = s.nextInt();
            int month = s.nextInt();
            int year = s.nextInt();

            System.out.print("Semester: ");
            int sem = s.nextShort();

            System.out.print("GPA: ");
            float gpa = s.nextFloat();

            System.out.print("CGPA: ");
            float cgpa = s.nextFloat();
            s.nextLine(); // Consume newline character

            // Create a new student record
            students[i] = new Student2(fullName, day, month, year, sem, gpa, cgpa);
        }

        // Display all the student records
        System.out.println("\nStudent2 Records:");
        for (Student2 student : students) {
            student.display();
        }

                // Sort by semester and CGPA and display sorted records
                System.out.println("\nSorting by Semester and CGPA...");
                sort1(students);
                for (Student2 student : students) {
                    student.display();
                }
        
                // Sort by name and display sorted records
                System.out.println("\nSorting by Name...");
                sort2(students);
                for (Student2 student : students) {
                    student.display();
                }
        
    }
}
