/*
 * javac-introcs BagTeste.java
 * java-introcs BagTeste
 */

public class BagTeste {
    public static void main(String[] args) {

        // read in numbers
        Bag<Double> numbers = new Bag<Double>();
        /*while (!StdIn.isEmpty()) {
            numbers.add(StdIn.readDouble());
        }*/
        double[] bolsa = {2.0, 1.0, 3.0, 4.0};
        for (int i = 0; i < bolsa.length; i++) numbers.add(bolsa[i]);
        int n = numbers.size();

        // compute sample mean
        double sum = 0.0;
        for (double x : numbers)
            sum += x;
        double mean = sum / n;

        // compute sample standard deviation
        sum = 0.0;
        for (double x : numbers) {
            sum += (x - mean) * (x - mean);
        }
        double stddev = Math.sqrt(sum / (n - 1));

        int i = 0;
        for (double s : numbers) {
            i++;
            if (i > 2) break;
            StdOut.println(s);
        }

        StdOut.printf("Mean:    %.2f\n", mean);
        StdOut.printf("Std dev: %.2f\n", stddev);
    }
}
