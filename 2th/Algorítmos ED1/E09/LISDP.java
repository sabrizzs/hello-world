/*
 * $ java-algs4 RandomSeq 10 20 121 | java-algs4 LISDP
 * LIS: 4 elements
 * $ java-algs4 RandomSeq 10 20 121 | java-algs4 LISDP +
 * LIS:
 * 0: 2 / 6
 * 1: 3 / 8
 * 2: 8 / 17
 * 3: 9 / 19
 * LIS: 4 elements
 * $ java-algs4 RandomSeq 30000 1000000000 121 | java-algs4 LISDP
 * LIS: 339 elements
 * $ java-algs4 RandomSeq 40000 1000000000 121 | java-algs4 LISDP
 * Exception in thread "main" java.lang.OutOfMemoryError: Java heap space
 * 	at LISDP.lcs(LISDP.java:38)
 * 	at LISDP.lis(LISDP.java:16)
 * 	at LISDP.main(LISDP.java:75)
 * $ java-algs4 RandomSeq 40000 1000000000 121 | java-algs4 -Xmx8G LISDP
 * LIS: 391 elements
 * $
 */

import java.util.Arrays;

import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.Queue;

public class LISDP {
    public static boolean verbose;

    public static Queue<Integer> lis(int[] x) {
        int N = x.length;
        int[] y = new int[N];
        for (int i = 0; i < N; i++) y[i] = x[i];
        Arrays.sort(y);
        y = uniq(y);
        return lcs(x, y);
    }

    public static int[] uniq(int[] y) {
        Queue<Integer> q = new Queue<>();
        int a = y[0];
        q.enqueue(a);
        for (int i = 1; i < y.length; i++)
            if (y[i] != a) {
                a = y[i];
                q.enqueue(a);
            }
        int[] u = new int[q.size()];
        for (int i = 0; i < u.length; i++)
            u[i] = q.dequeue();
        return u;
    }

    // as in LongestCommonSubsequence.java
    public static Queue<Integer> lcs(int[] x, int[] y) {
        int m = x.length, n = y.length;
        int[][] opt = new int[m + 1][n + 1];
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (x[i] == y[j])
                    opt[i][j] = opt[i + 1][j + 1] + 1;
                else
                    opt[i][j] = Math.max(opt[i + 1][j], opt[i][j + 1]);
            }
        }

        // recover LCS itself
        Queue<Integer> lcs = new Queue<>();
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (x[i] == y[j]) {
                lcs.enqueue(i);
                i++;
                j++;
            } else if (opt[i + 1][j] >= opt[i][j + 1]) i++;
            else j++;
        }
        return lcs;
    }

    public static void main(String[] args) {
        verbose = args.length > 0;
        int[] x = StdIn.readAllInts();
        Queue<Integer> lis = lis(x);
        if (verbose) {
            StdOut.println("LIS:");
            int t = 0;
            for (Integer i : lis)
                StdOut.println(t++ + ": " + i + " / " + x[i]);
        }
        StdOut.println("LIS: " + lis.size() + " elements");
    }
}
