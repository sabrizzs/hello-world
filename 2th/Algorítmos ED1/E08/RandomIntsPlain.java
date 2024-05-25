/*
 * Generates N random integers in [-M, M].
 *
 * javac RandomIntsPlain.java
 * $ java-algs4 RandomIntsPlain 10 5 121
 * 3 -3 -5 0 3 5 -4 -4 1 -3
 * $
 */

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

public class RandomIntsPlain {
    public static int[] randomSeq(int N, int M) {
        int[] a = new int[N];
        for (int i = 0; i < N; i++)
            a[i] = StdRandom.uniform(-M, M + 1);
        return a;
    }

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        int M = Integer.parseInt(args[1]);
        long seed = Long.parseLong(args[2]);
        StdRandom.setSeed(seed);

        int[] a = randomSeq(N, M);
        for (int i = 0; i < N; i++)
            StdOut.print(a[i] + " ");
        StdOut.println();
    }
}
