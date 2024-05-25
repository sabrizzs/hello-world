/* javac BagSort.java
 * java-introcs BagSort
 * $ java-algs4 RandomInts 10 2100000000 121 | java-introcs BagSort
 * Sorted as numbers:
 *    61201360
 *   372288721
 *   708643167
 *   735733880
 *   845867922
 *  1032466240
 *  1173150458
 *  1552620034
 *  1664962027
 *  1940816169
 * Sorted as strings:
 * 1032466240
 * 1173150458
 * 1552620034
 * 1664962027
 * 1940816169
 * 372288721
 * 61201360
 * 708643167
 * 735733880
 * 845867922
 * $
 */

/*import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;*/

public class BagSort {
    public static void sort(Comparable[] a) {
        BagVariant b = new BagVariant();
        for (Comparable x : a) b.add(x);  // foreach works for arrays
        b.sort();
        int i = 0;
        for (Object x : b) a[i++] = (Comparable) x;
    }

    public static void main(String[] args) {
        String[] v = StdIn.readAllStrings();

        Integer[] a = new Integer[v.length];
        int i = 0;
        for (String s : v)
            a[i++] = Integer.parseInt(s);
        sort(a);
        StdOut.println("Sorted as numbers:");
        for (Integer x : a)
            StdOut.printf("%11d\n", x);

        sort(v);
        StdOut.println("Sorted as strings:");
        for (String s : v)
            StdOut.println(s);
    }
}
