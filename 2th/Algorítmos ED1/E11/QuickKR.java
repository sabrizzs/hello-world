/******************************************************************************
 *  Compilation:  javac-introcs QuickKR.java
 *  Execution:    java-introcs QuickKR N
 *  Dependencies: StdIn.java StdOut.java
 *
 *  Generate N random real numbers between 0 and 1 and quicksort them.
 *  Uses version of quicksort from K+R.
 *
 *  Reference: The C Programming Language by Brian W. Kernighan and
 *  Dennis M. Ritchie, p. 87.
 *
 *  Warning: goes quadratic if many duplicate keys.
 *
 ******************************************************************************/

//import edu.princeton.cs.algs4.StdOut;
//import edu.princeton.cs.algs4.StdIn;


public class QuickKR {

    public static void sort(Comparable[] a, Comparable[] b) {
        sort(a, 0, a.length - 1);
        sort(b, 0, b.length - 1);
    }

    private static void sort(Comparable[] a, int lo, int hi) {
        if (hi <= lo) return;
        exch(a, lo, (lo + hi) / 2);  // use middle element as partition
        int last = lo;
        for (int i = lo + 1; i <= hi; i++)
            if (less(a[i], a[lo])) exch(a, ++last, i);
        exch(a, lo, last);
        sort(a, lo, last - 1);
        sort(a, last + 1, hi);
    }


    /***************************************************************************
     *  Helper sorting functions.
     ***************************************************************************/

    // is v < w ?
    private static boolean less(Comparable v, Comparable w) {
        return v.compareTo(w) < 0;
    }

    // exchange a[i] and a[j]
    private static void exch(Object[] a, int i, int j) {
        Object swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }


    /***************************************************************************
     *  Check if array is sorted - useful for debugging.
     ***************************************************************************/
    private static boolean isSorted(Comparable[] a) {
        for (int i = 1; i < a.length; i++)
            if (less(a[i], a[i - 1])) return false;
        return true;
    }

    // print array to standard output
    private static void show(Comparable[] a) {
        for (int i = 0; i < a.length; i++) {
            StdOut.println(a[i]);
        }
    }

    public static void main(String[] args) {
        String nuts[] = {"93", "82", "05", "80", "96", "73", "47", "77", "99", "0"};
        String bolts[] = {"99", "77", "73", "80", "47", "0", "96", "82", "05", "93"};
        QuickKR.sort(nuts, bolts);
        show(bolts);
        showint(indicebolts);
        assert isSorted(bolts);
    }
}
