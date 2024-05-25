/*
 * $ cat tobe.txt
 * to be or not to - be - - that - - - is
 * $ java-introcs BagVariantClient < tobe.txt
 * javac-introcs BagVariantClient.java
 * *** Size of bag = 14
 * *** Bag content:
 * is
 * -
 * -
 * -
 * that
 * -
 * -
 * be
 * -
 * to
 * not
 * or
 * be
 * to
 * *** After sorting:
 * -
 * -
 * -
 * -
 * -
 * -
 * be
 * be
 * is
 * not
 * or
 * that
 * to
 * to
 * $
 */

/*import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;*/

public class BagVariantClient {
    public static void main(String[] args) {
        BagVariant<String> bag = new BagVariant<String>();
        while (!StdIn.isEmpty()) {
            String item = StdIn.readString();
            bag.add(item); /////
        }

        StdOut.println("*** Size of bag = " + bag.size());
        StdOut.println("*** Bag content:");
        for (String s : bag)
            StdOut.println(s);

        bag.sort(); /////
        StdOut.println("*** After sorting:");
        for (String s : bag)
            StdOut.println(s);
        StdOut.println("Size: " + bag.size());
    }
}
