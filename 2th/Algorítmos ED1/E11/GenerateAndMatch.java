/* javac-algs4 GenerateAndMatch.java
 * $ java-algs4 GenerateAndMatch 8000000 8000000 20195
 * Time to find the matching: 6.228
 * Success!
 * $ java-algs4 GenerateAndMatch 8000000 8000000 20195 -s
 * Time to find the matching: 2.244
 * Success!
 * $
 */

import pieces.Nut;
import pieces.Bolt;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.Stopwatch;

public class GenerateAndMatch {

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        int t = Integer.parseInt(args[1]);
        long seed = Long.parseLong(args[2]);
        boolean sorted = args.length > 3;

        // N nuts and N bolts
        NutsAndBolts nutsAndBolts = new NutsAndBolts(N, t, seed, sorted);
        // for (int i = 0; i < N; i++)
        //     StdOut.printf("%3d", i);
        // StdOut.println();
        // nutsAndBolts.printNuts();
        // nutsAndBolts.printBolts();

        Stopwatch sw = new Stopwatch();
        int[] p = Match.match(nutsAndBolts);
        StdOut.println("Time to find the matching: " + sw.elapsedTime());
        // for (int i = 0; i < N; i++)
        //     StdOut.printf("%3d", p[i]);
        // StdOut.println();

        int i = nutsAndBolts.check(p);
        if (i < 0)
            StdOut.println("Success!");
        else
            StdOut.println("Unmatched pair: " + i);
    }

}
