import java.io.*;
import java.util.*;

class Student {
    String rollNo;
    String name;
    String division;
    String address;

    public Student(String rollNo, String name, String division, String address) {
        this.rollNo = rollNo;
        this.name = name;
        this.division = division;
        this.address = address;
    }

    @Override
    public String toString() {
        return rollNo + "," + name + "," + division + "," + address;
    }

    public static Student fromString(String line) {
        String[] parts = line.split(",");
        if (parts.length == 4) {
            return new Student(parts[0], parts[1], parts[2], parts[3]);
        }
        return null;
    }
}

public class Main2{
    static final String FILE_NAME = "students.txt";
    static Scanner sc = new Scanner(System.in);

    public static void addStudent() throws IOException {
        System.out.print("Enter Roll No: ");
        String rollNo = sc.nextLine();
        System.out.print("Enter Name: ");
        String name = sc.nextLine();
        System.out.print("Enter Division: ");
        String division = sc.nextLine();
        System.out.print("Enter Address: ");
        String address = sc.nextLine();

        Student student = new Student(rollNo, name, division, address);
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(FILE_NAME, true))) {
            writer.write(student.toString());
            writer.newLine();
        }

        System.out.println("Student added successfully.");
    }

    public static void deleteStudent() throws IOException {
        System.out.print("Enter Roll No to delete: ");
        String rollNo = sc.nextLine();

        File inputFile = new File(FILE_NAME);
        File tempFile = new File("temp.txt");

        boolean found = false;

        try (
            BufferedReader reader = new BufferedReader(new FileReader(inputFile));
            BufferedWriter writer = new BufferedWriter(new FileWriter(tempFile))
        ) {
            String currentLine;

            while ((currentLine = reader.readLine()) != null) {
                Student student = Student.fromString(currentLine);
                if (student != null && student.rollNo.equals(rollNo)) {
                    found = true;
                    continue; // Skip this student
                }
                writer.write(currentLine);
                writer.newLine();
            }
        }

        if (found) {
            if (inputFile.delete() && tempFile.renameTo(inputFile)) {
                System.out.println("Student deleted successfully.");
            } else {
                System.out.println("Error updating student file.");
            }
        } else {
            System.out.println("Student not found.");
            tempFile.delete();
        }
    }

    public static void displayStudent() throws IOException {
        System.out.print("Enter Roll No to search: ");
        String rollNo = sc.nextLine();

        boolean found = false;

        try (BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME))) {
            String line;
            while ((line = reader.readLine()) != null) {
                Student student = Student.fromString(line);
                if (student != null && student.rollNo.equals(rollNo)) {
                    System.out.println("Student Found:");
                    System.out.println("Roll No: " + student.rollNo);
                    System.out.println("Name: " + student.name);
                    System.out.println("Division: " + student.division);
                    System.out.println("Address: " + student.address);
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            System.out.println("Student not found.");
        }
    }

    public static void displayAllStudents() {
        System.out.println("\n--- Contents of students.txt ---");
        File file = new File(FILE_NAME);
        if (!file.exists()) {
            System.out.println("No student data found.");
            return;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME))) {
            String line;
            boolean hasData = false;
            while ((line = reader.readLine()) != null) {
                hasData = true;
                System.out.println(line);
            }
            if (!hasData) {
                System.out.println("No student data found.");
            }
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        int choice = 0;
        do {
            System.out.println("\n--- Student Management ---");
            System.out.println("1. Add Student");
            System.out.println("2. Delete Student");
            System.out.println("3. Display Student");
            System.out.println("4. Exit");
            System.out.print("Enter your choice: ");
            try {
                choice = Integer.parseInt(sc.nextLine());
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter a number.");
                continue;
            }

            try {
                switch (choice) {
                    case 1: addStudent(); break;
                    case 2: deleteStudent(); break;
                    case 3: displayStudent(); break;
                    case 4: System.out.println("Exiting..."); break;
                    default: System.out.println("Invalid choice.");
                }
            } catch (IOException e) {
                System.out.println("An error occurred: " + e.getMessage());
            }

            displayAllStudents();
        } while (choice != 4);
    }
}
