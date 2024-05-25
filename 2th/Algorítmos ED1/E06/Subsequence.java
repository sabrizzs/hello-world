/******************************************************************************
 *  Compilation:  javac-introcs Subsequence.java
 *  Execution:    java-introcs Subsequence s k
 *
 *  Print out all subsequences of the string s of length k.
 *
 *  % java Subsequence abcd 3
 *  abc
 *  abd
 *  acd
 *  bcd
 *
 *  % java Subsequence abcc 3
 *  abc
 *  abc
 *  acc
 *  bcc
 *
 ******************************************************************************/

public class Subsequence {

    public static void print(String prefix, String remaining, int k) {
        if (k == 0) {
            StdOut.println(prefix);
            return;
        }
        if (remaining.length() == 0) return;
        print(prefix + remaining.charAt(0), remaining.substring(1), k - 1);
        print(prefix, remaining.substring(1), k);
    }

    public static void printd(String prefix, String remaining, int k) {
        if (k == 0) {
            StdOut.println(prefix);
            return;
        }
        if (remaining.length() == 0) return;
        printd(prefix + remaining.charAt(0), remaining.substring(1), k - 1);
        printd(prefix, remaining.substring(1), k);
    }


    public static void main(String[] args) {
        String s = args[0];
        int k = Integer.parseInt(args[1]);
        print("", s, k);
    }

}

