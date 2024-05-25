/******************************************************************************
 *  Prints N random integers in [1, M]
 *
 * $ java-introcs RandomInts 10 5 121
 * 4 2 2 4 2 5 1 5 3 5
 * $
 ******************************************************************************/

public class RandomInts {

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        int M = Integer.parseInt(args[1]);
        long seed = Long.parseLong(args[2]);
        StdRandom.setSeed(seed);
        for (int i = 0; i < N; i++)
            StdOut.print(1 + StdRandom.uniform(M) + " ");
        StdOut.println();
    }

}
