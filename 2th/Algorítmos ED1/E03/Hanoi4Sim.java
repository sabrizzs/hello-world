/* javac-introcs Hanoi4Sim.java
 * $ time java-introcs Hanoi4 2 | java-introcs Hanoi4Sim 2 .
 * Initial configuration:
 * 0: 2 1
 * 1:
 * 2:
 * 3:
 * 1 2
 * 0: 2
 * 1:
 * 2: 1
 * 3:
 * 2 1
 * 0:
 * 1: 2
 * 2: 1
 * 3:
 * 1 1
 * 0:
 * 1: 2 1
 * 2:
 * 3:
 * Final configuration:
 * 0:
 * 1: 2 1
 * 2:
 * 3:
 * Worked!
 * Number of moves: 3
 * $ java-introcs Hanoi4 21 | java-introcs Hanoi4Sim 21
 * Worked!
 * Number of moves: 321
 * Number of moves should be at most 321
 * $
 */

public class Hanoi4Sim {
    public static Stack<Integer>[] initialize(int N) {
        Stack<Integer>[] s = (Stack<Integer>[]) new Stack[4];
        for (int i = 0; i < 4; i++) s[i] = new Stack<>();
        for (int i = N; i > 0; i--) s[0].push(i);
        return s;
    }

    public static void print(Stack<Integer>[] s) {
        for (int i = 0; i < 4; i++) {
            StdOut.print(i + ": ");
            Stack<Integer> t = new Stack<>();
            for (Integer d : s[i]) t.push(d);
            for (Integer d : t) StdOut.print(d + " ");
            StdOut.println();
        }
    }

    public static int simulate(int N, boolean verbose) {
        int[] peg = new int[N + 1];  // peg[d] = where disk d is; initially all 0
        Stack<Integer>[] s = initialize(N);
        int M = 0;
        if (verbose) {
            StdOut.println("Initial configuration:");
            print(s);
        }
        while (!StdIn.isEmpty()) {
            int d = StdIn.readInt();
            int p = StdIn.readInt();
            if (verbose)
                StdOut.println("Move: " + d + " " + p);
            if (d != s[peg[d]].peek()) {
                StdOut.println("Illegal: " + d + " not on top");
                print(s);
                return M;
            }
            if (!s[p].isEmpty() && d > s[p].peek()) {
                StdOut.println("Illegal: " + d + " larger than disk on top of peg " + p);
                print(s);
                return M;
            }
            s[peg[d]].pop();
            s[p].push(d);
            peg[d] = p;
            if (verbose) print(s);
            M++;
        }
        if (verbose) {
            StdOut.println("Final configuration:");
            print(s);
        }
        if (s[1].size() == N) StdOut.println("Worked!");
        else StdOut.println("Didn't work!");
        return M;
    }

    // n such that {n\choose2} < N \leq {n+1\choose2}
    // for N \geq 1
    public static int n(int N) {
        int n = 0, b = 0;
        while (b < N) {
            b += n;
            n++;
        }
        return n - 1;
    }

    public static boolean special(int N) {
        int n = n(N);
        return N == (n + 1) * n / 2;
    }

    public static int f(int n) {
        return (n - 1) * (1 << n) + 1;
    }

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        ccc
        int M = simulate(N, verbose);
        StdOut.println("Number of moves: " + M);
        if (special(N))
            StdOut.println("Should be at most " + f(n(N)));
    }
}

oooooooooooooooooooooooooooooooooooo

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
        for (int i : seq) {
            buscabinaria(
            if
        }

    }

    public static int buscabinaria(int[] A, int x) {
        return bisect_left(A, x, 0, A.length);
    }

    public static int buscabinaria(int[] A, int x, int lo, int hi) {
        int N = A.length;
        if (N == 0) {
            return 0;
        }
        if (x < A[lo]) {
            return lo;
        }
        if (x > A[hi - 1]) {
            return hi;
        }
        for (; ; ) {
            if (lo + 1 == hi) {
                return x == A[lo] ? lo : (lo + 1);
            }
            int mi = (hi + lo) / 2;
            if (x <= A[mi]) {
                hi = mi;
            } else {
                lo = mi;
            }
        }
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

