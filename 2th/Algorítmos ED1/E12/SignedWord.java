/*
 * For pairs (word, signature), with compareTo() based on comparing
 * the
 *
 * javac-introcs SignedWord.java
 * java-introcs SignedWord
 */

import java.util.Arrays;

//import edu.princeton.cs.algs4.StdOut;

public class SignedWord implements Comparable<SignedWord> {

    private String word;
    private String signature;

    public SignedWord(String word) {
        this.word = word;
        String w = word.toLowerCase();
        char[] s = w.toCharArray();
        Arrays.sort(s);
        this.signature = new String(s);
    }

    public SignedWord(String word, String signature) {
        this.word = word;
        this.signature = signature;
    }

    public int compareTo(SignedWord that) {
        return this.signature.compareTo(that.signature);
    }

    public String toString() {
        return "(" + word + ", " + signature + ")";
    }

    public String signature() { // retorna palavra com letras em ordem alfabetica
        return signature;
    }

    public String word() { // retorna a palavra normal
        return word;
    }

    public static void main(String[] args) {
        SignedWord sw0 = new SignedWord("alphabet");
        SignedWord sw1 = new SignedWord("MacDonald's");
        SignedWord sw2 = new SignedWord("Google");

        StdOut.println("0: " + sw0);
        StdOut.println("1: " + sw1);
        StdOut.println("2: " + sw2);
        int cmp = sw0.compareTo(sw1);
        StdOut.println("teste: " + sw0.signature());
        if (cmp < 0) StdOut.println(sw0 + " < " + sw1);
        else if (cmp > 0) StdOut.println(sw0 + " > " + sw1);
        else StdOut.println(sw0 + " = " + sw1);
        cmp = sw1.compareTo(sw2);
        StdOut.println("teste 2: " + sw1.compareTo(sw2));
        if (cmp < 0) StdOut.println(sw1 + " < " + sw2);
        else if (cmp > 0) StdOut.println(sw1 + " > " + sw2);
        else StdOut.println(sw1 + " = " + sw2);
    }
}
