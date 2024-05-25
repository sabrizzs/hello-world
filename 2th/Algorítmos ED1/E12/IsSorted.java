/*
 * $ java-algs4 Anagrams < DATA/words6.txt | java-algs4 IsSorted
 * Success!
 * $ 
 */

import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

public class IsSorted
{
    public static boolean isSorted(String[] words) {
	int N = words.length;
	for (int i = 2; i < N; i++) {
	    if (words[i - 1].compareTo(words[i]) > 0)
		return false; 
	}
	return true;
    }
    
    public static void main(String[] args)
    {
	String prev = "";
	while (!StdIn.isEmpty()) {
	    String line = StdIn.readLine();
	    String[] words = line.split("\\s+");
	    if (!isSorted(words)) { 
		StdOut.println("Line not sorted: ");
		for (String s : words) 
		    StdOut.print(s + " ");
		StdOut.println();
		System.exit(0);
	    }
	    if (prev.compareTo(words[1]) > 0) {
		StdOut.print("Conflicting first words: ");
		StdOut.println(prev + " / " + words[1]);
		System.exit(0);
	    }
	    prev = words[1];
	}
	StdOut.println("Success!");
    }
}
