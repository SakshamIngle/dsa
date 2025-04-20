import java.io.*;
import java.util.*;

public class Main{

    static int MEMORY_LIMIT = 5; // m: number of records memory can sort at once

    // Step 1: Split the input file into sorted runs of size m
    public static List<String> createInitialRuns(String inputFile) throws IOException {
        List<String> runFiles = new ArrayList<>();
        BufferedReader reader = new BufferedReader(new FileReader(inputFile));
        List<Integer> buffer = new ArrayList<>();

        int runCount = 0;
        String line;

        while ((line = reader.readLine()) != null) {
            buffer.add(Integer.parseInt(line));
            if (buffer.size() == MEMORY_LIMIT) {
                Collections.sort(buffer);
                String runFile = "run" + runCount++ + ".txt";
                writeRunToFile(runFile, buffer);
                runFiles.add(runFile);
                buffer.clear();
            }
        }

        // Write remaining records
        if (!buffer.isEmpty()) {
            Collections.sort(buffer);
            String runFile = "run" + runCount++ + ".txt";
            writeRunToFile(runFile, buffer);
            runFiles.add(runFile);
        }

        reader.close();
        return runFiles;
    }

    public static void writeRunToFile(String filename, List<Integer> run) throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter(filename));
        for (int num : run) {
            writer.write(num + "\n");
        }
        writer.close();
    }

    // Step 2: Merge runs two at a time (2-way merge)
    public static void mergeRuns(List<String> runFiles, String outputFile) throws IOException {
        int pass = 0;

        while (runFiles.size() > 1) {
            List<String> newRunFiles = new ArrayList<>();

            for (int i = 0; i < runFiles.size(); i += 2) {
                if (i + 1 < runFiles.size()) {
                    String run1 = runFiles.get(i);
                    String run2 = runFiles.get(i + 1);
                    String mergedRun = "merged_pass" + pass + "_run" + (i / 2) + ".txt";
                    mergeTwoRuns(run1, run2, mergedRun);
                    newRunFiles.add(mergedRun);
                    new File(run1).delete();
                    new File(run2).delete();
                } else {
                    newRunFiles.add(runFiles.get(i)); // odd one out
                }
            }

            runFiles = newRunFiles;
            pass++;
        }

        // Final merged file is the result
        new File(runFiles.get(0)).renameTo(new File(outputFile));
    }

    public static void mergeTwoRuns(String file1, String file2, String outputFile) throws IOException {
        BufferedReader reader1 = new BufferedReader(new FileReader(file1));
        BufferedReader reader2 = new BufferedReader(new FileReader(file2));
        BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile));

        String line1 = reader1.readLine();
        String line2 = reader2.readLine();

        while (line1 != null && line2 != null) {
            int num1 = Integer.parseInt(line1);
            int num2 = Integer.parseInt(line2);

            if (num1 <= num2) {
                writer.write(num1 + "\n");
                line1 = reader1.readLine();
            } else {
                writer.write(num2 + "\n");
                line2 = reader2.readLine();
            }
        }

        while (line1 != null) {
            writer.write(line1 + "\n");
            line1 = reader1.readLine();
        }

        while (line2 != null) {
            writer.write(line2 + "\n");
            line2 = reader2.readLine();
        }

        reader1.close();
        reader2.close();
        writer.close();
    }

    public static void main(String[] args) throws IOException {
        String inputFile = "input.txt";
        String outputFile = "sorted.txt";

        // Step 1: Create initial sorted runs
        List<String> runs = createInitialRuns(inputFile);

        // Step 2: Merge runs
        mergeRuns(runs, outputFile);

        System.out.println("Sorting completed. Sorted data is in: " + outputFile);
    }
}
