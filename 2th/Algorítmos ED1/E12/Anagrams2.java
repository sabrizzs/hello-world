/*
 * javac-introcs Anagrams2.java
 * java-introcs Anagrams2
 * java-introcs Anagrams2 < exemplo.in
 */

//import edu.princeton.cs.algs4.StdOut;
//import edu.princeton.cs.algs4.StdRandom;
//import edu.princeton.cs.algs4.SET;


public class Anagrams2 {

    public static void sort(String[] a) {
        quickSort(a, 0, a.length - 1);
    }

    static void swap(String[] arr, int i, int j) {
        String temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    static int partition(String[] arr, int low, int high) {

        String pivot = arr[high];
        SignedWord sw1 = new SignedWord(pivot);
        StdOut.println("teste " + sw1.word() + " " + sw1.signature());
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {

            SignedWord sw0 = new SignedWord(arr[j]);
            if (sw0.compareTo(sw1) == 0) StdOut.println(sw0 + " e " + sw1 + " são anagramas");
            if (sw0.compareTo(sw1) < 0) { // compara palavras
                i++;
                swap(arr, i, j);
            }
        }
        swap(arr, i + 1, high);
        return (i + 1);
    }

    static void quickSort(String[] arr, int low, int high) {
        if (low < high) {

            int pi = partition(arr, low, high);

            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    static void printArray(String[] arr) {
        int size = arr.length;
        for (int i = 0; i < size; i++)
            System.out.print(arr[i] + " ");

        System.out.println();
    }

    public static void main(String[] args) {
        String[] arr = StdIn.readAllStrings();
        //String[] arr = {"saac", "casa", "bolo", "asac", "nabi", "olob", "bina", "sorvete", "aasc"};

        sort(arr);
        System.out.println("Sorted array: ");
        printArray(arr);
        //show(arr);

    }
}
