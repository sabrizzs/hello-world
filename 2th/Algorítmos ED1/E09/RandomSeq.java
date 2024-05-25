/******************************************************************************
 * $ java-algs4 RandomSeq N M seed
 * 
 * N uniform integers in [0, M).  Uses seed as seed.
 * 
 * $ java-algs4 RandomSeq 10 20 121
 * 13 6 6 8 1 19 0 19 17 19 
 * $ 
 ******************************************************************************/

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

public class RandomSeq { 
    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        int M = Integer.parseInt(args[1]);
        long seed = Long.parseLong(args[2]);
	StdRandom.setSeed(seed);
        for (int i = 0; i < N; i++) 
            StdOut.print(StdRandom.uniform(M) + " ");
	StdOut.println();
    }
}
