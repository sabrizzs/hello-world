/*	javac-algs4 NutsAndBolts.java
 * $ java-algs4 NutsAndBolts 10 2 20195
 * Unsorted: Unmatched pair: 1
 * Sorted:   Lucky!  (Should always be lucky here)
 * $ java-algs4 NutsAndBolts 10 100 20195
 * Unsorted: Unmatched pair: 0
 * Sorted:   Lucky!  (Should always be lucky here)
 * $ java-algs4 NutsAndBolts 100 100 20195
 * Unsorted: Unmatched pair: 0
 * Sorted:   Lucky!  (Should always be lucky here)
 * $ java-algs4 NutsAndBolts 2 2 121
 * Unsorted: Lucky!  (In general, very unlikely)
 * Sorted:   Lucky!  (Should always be lucky here)
 * $
 */

import pieces.Nut;
import pieces.Bolt;

import java.util.Arrays;

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

public final class NutsAndBolts {
    private final Nut[] nuts;
    private final Bolt[] bolts;
    private int N;

    public NutsAndBolts(int N, int t, long seed) {
        this(N, t, seed, false);
    }

    public NutsAndBolts(int N, int t, long seed, boolean sorted) {
        nuts = new Nut[N];
        bolts = new Bolt[N];
        this.N = N;

        StdRandom.setSeed(seed);
        int[] dimen = new int[N];
        // t distinct dimensions of nuts and bolts
        for (int i = 0; i < N; i++)
            dimen[i] = StdRandom.uniform(t);

        if (sorted) { // evil
            Arrays.sort(dimen);
            for (int i = 0; i < N; i++)
                nuts[i] = new Nut(dimen[i]);
            for (int i = 0; i < N; i++)
                bolts[i] = new Bolt(dimen[i]);
        } else {
            for (int i = 0; i < N; i++)
                nuts[i] = new Nut(dimen[i]);
            StdRandom.shuffle(dimen);
            for (int i = 0; i < N; i++)
                bolts[i] = new Bolt(dimen[i]);
        }
    }

    public int N() {
        return N;
    }

    public Nut nuts(int i) {
        return nuts[i];
    }

    public Bolt bolts(int i) {
        return bolts[i];
    }

    // public void printNuts() {
    // 	for (int i = 0; i < N; i++) StdOut.print(nuts[i]);
    // 	StdOut.println();
    // }

    // public void printBolts() {
    // 	for (int i = 0; i < N; i++) StdOut.print(bolts[i]);
    // 	StdOut.println();
    // }

    // Is the identity permutation a match?
    public int check() {
        int[] p = new int[N];
        for (int i = 0; i < N; i++) p[i] = i;
        return check(p);
    }

    public int check(int[] p) {
        if (p.length != N) {
            StdOut.println("check(): argument not of right length");
            System.exit(0);
        }
        for (int i = 0; i < N; i++)
            if (nuts[i].compareTo(bolts[p[i]]) != 0)
                return i;
        boolean[] hit = new boolean[N];
        for (int i = 0; i < N; i++)
            hit[p[i]] = true;
        for (int i = 0; i < N; i++)
            if (!hit[i]) {
                StdOut.println("check(): argument not a permutation");
                System.exit(0);
            }
        return -1; // success
    }

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        int t = Integer.parseInt(args[1]);
        long seed = Long.parseLong(args[2]);

        // N nuts and N bolts; unmatched
        NutsAndBolts nutsAndBolts = new NutsAndBolts(N, t, seed);
        StdOut.print("Unsorted: ");
        // nutsAndBolts.printNuts();
        // nutsAndBolts.printBolts();

        int i = nutsAndBolts.check();
        if (i < 0)
            StdOut.println("Lucky!  (In general, very unlikely)");
        else
            StdOut.println("Unmatched pair: " + i);

        // N nuts and N bolts; sorted and therefore matched
        nutsAndBolts = new NutsAndBolts(N, t, seed, true);
        StdOut.print("Sorted:   ");
        // nutsAndBolts.printNuts();
        // nutsAndBolts.printBolts();

        i = nutsAndBolts.check();
        if (i < 0)
            StdOut.println("Lucky!  (Should always be lucky here)");
        else
            StdOut.println("Unmatched pair: " + i + "(shouldn't happen)");
    }

}
