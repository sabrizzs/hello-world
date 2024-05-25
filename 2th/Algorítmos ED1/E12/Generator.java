/*
 * Random strings; no repetition.
 * 
 * Uses a SET<String> to keep track of the strings already sent to stdout.
 * 
 * $ java-algs4 Generator 10 3 abc 1212021
 * ccb
 * aca
 * acb
 * aaa
 * aac
 * cba
 * cbb
 * bcc
 * cab
 * bbb
 * $ java-algs4 Generator 15 8 0123 1212021
 * 21112120
 * 01102300
 * 03030213
 * [...]
 * $ 
 */

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.SET;

public class Generator {

    public static String randomString(int L, String alpha) {
	char[] a = new char[L];
	for (int i = 0; i < L; i++)  { 
	    int t = StdRandom.uniform(alpha.length());
	    a[i] = alpha.charAt(t);
	}
	return new String(a);
    }
    
    public static void main(String[] args) {
	int N = Integer.parseInt(args[0]);
	int L = Integer.parseInt(args[1]);
	String alpha = args[2];
	long seed = Long.parseLong(args[3]);
	StdRandom.setSeed(seed);

	SET<String> S = new SET<>();
	while (S.size() < N) {
	    String s = randomString(L, alpha);
	    if (S.contains(s)) continue;
	    StdOut.println(s);
	    S.add(s);
	} 
    }

}
