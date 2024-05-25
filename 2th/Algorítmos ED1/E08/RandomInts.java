/*
 * Generates N distinct random integers in [-M, M].
 * Output is sorted in increasing order.
 *
 * javac RandomInts.java
 * $ java-algs4 RandomInts 10 20 121
 * -17 -8 -4 5 7 8 9 11 12 17
 * $
 */

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.SET;

public class RandomInts {
    public static int[] randomSeq(int N, int M) {
        SET<Integer> s = new SET<>();
        int NN = N;
        while (NN > 0) {
            int x = StdRandom.uniform(-M, M + 1);
            if (s.contains(x)) continue;
            s.add(x);
            NN--;
        }
        int[] a = new int[N];
        int i = 0;
        for (Integer x : s) a[i++] = x;
        return a;
    }

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        int M = Integer.parseInt(args[1]);
        long seed = Long.parseLong(args[2]);
        StdRandom.setSeed(seed);

        int[] s = randomSeq(N, M);
        for (int i = 0; i < N; i++) {
            StdOut.print(s[i] + " ");
        }
        StdOut.println();
    }
}
