/*
 * javac-algs4 Patience.java
 * java-algs4 Patience
 *
 *
 */

import java.util.Arrays;

//import edu.princeton.cs.algs4.StdIn;
//import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.*;

public class Patience {
    public static boolean verbose;

    public static Stack<Integer>[] initialize(int N) {
        Stack<Integer>[] s = (Stack<Integer>[]) new Stack[4];
        for (int i = 0; i < 4; i++) s[i] = new Stack<>();
        for (int i = N; i > 0; i--) s[0].push(i);
        return s;
    }

    public static void patience(int[] seq) {
        int tam = seq.length;
        Stack<Integer>[] pilha = initialize(tam);
        int[] p = new int[tam];
        int count = 0;
        int ind = 0;
        for (int i : seq) {
            int t = buscabinaria(p, i);
            if (t == pilha[0].size()) {
                pilha[0].push(i);
                p[count] = i;
                count++;
                ind++;
            } else count++;
            StdOut.println(i + " " + t);
        }

    }

    public static int binary(Stack<Integer>[] stack, int i) {
        int l = 0; // left
        int r = stack.size() - 1; // right
        int m = -1; // middle

        if (stack.isEmpty()) return -1;

        while (l <= r) {
            /*
             * Pick the middle. Same as (l + r) / 2 but does not run the risk of integer overflow
             */
            m = l + (r - l) / 2;

            Stack<Integer>[] stack = stack.get(m);
            int c = stack.peek; // get the top card from this pile

            if (c.i == i) return m; // exact match

            if (c.i < i) {
                l = m + 1; // ignore left half
            } else {
                r = m - 1; // ignore right half
            }
        }

        if (l >= stack.size()) return -1;

        Stack<Integer>[] Pile = piles.get(l);
        return stack.peek.i >= i ? l : -1;
    }
    
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
        //int[] x = StdIn.readAllInts();
        int[] a = {1, 4, 2, 6, 3};
        patience(a);
        //StdOut.println(H);
        /*Queue<Integer> lis = lis(x);
        if (verbose) {
            StdOut.println("LIS:");
            int t = 0;
            for (Integer i : lis)
                StdOut.println(t++ + ": " + i + " / " + x[i]);
        }
        StdOut.println("LIS: " + lis.size() + " elements");

         */
    }
}
