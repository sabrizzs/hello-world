/* 
 * Nearly sorted integers
 * 
 * $ java-algs4 RandomSeqNS 30 5 121
 * 3 -2 -3 3 7 10 2 3 9 6 13 10 16 10 9 20 16 18 15 16 20 17 19 25 23 29 27 30 28 29 
 */ 

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

public class RandomSeqNS
{
    public static void main(String[] args)
    {
        int N = Integer.parseInt(args[0]);
        int D = Integer.parseInt(args[1]);
        long seed = Long.parseLong(args[2]);
	StdRandom.setSeed(seed);
        for (int i = 0; i < N; i++) 
	    StdOut.print((i + StdRandom.uniform(-D, D + 1)) + " ");
	StdOut.println();
    }
}
