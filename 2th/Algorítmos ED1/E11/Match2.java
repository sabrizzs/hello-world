/*	javac-algs4 Match2.java
 *
 * javac-algs4 NutsAndBolts.java
 * javac-algs4 GenerateAndMatch.java
 * java-algs4 GenerateAndMatch  10  10 1212021
 *
 * Slow match (quadratic).  Example runs of GenerateAndMatch with this match:
 * java-algs4 GenerateAndMatch  10  10 1212021
 * $ java-algs4 GenerateAndMatch  50000  50000 1212021
 * Time to find the matching: 3.98
 * Success!
 * $ java-algs4 GenerateAndMatch  100000  100000 1212021
 * Time to find the matching: 15.802
 * Success!
 * $ java-algs4 GenerateAndMatch  200000  200000 1212021
 * Time to find the matching: 63.329
 * Success!
 * $
 */

import pieces.Nut;
import pieces.Bolt;

public class Match {

    public static int[] match(NutsAndBolts nab) {
        int N = nab.N();
        int[] p = new int[N];
        boolean[] hit = new boolean[N];
        Bolt[] bolts = new Bolt[N];
        System.out.println("print " + bolts[0]);


        System.out.println("Teste" + (nab.nuts(1).compareTo(nab.bolts(4)) > 0));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                if (nab.nuts(i).compareTo(nab.bolts(j)) == 0 && !hit[j]) {
                    p[i] = j;
                    hit[j] = true;
                    break;
                }
            }
        return p;
    }
}
