/*
 * javac-introcs Anagrams1.java
 * java-introcs Anagrams
 * java-introcs Anagrams < exemplo.in
 */

//import edu.princeton.cs.algs4.StdOut;
//import edu.princeton.cs.algs4.StdRandom;
//import edu.princeton.cs.algs4.SET;

//import SignedWord.java;

public class Anagrams {
    // usar o SignedWord pra ver se é anagrama, se for igual é anagrama, i think
    // tenho que pensar em como usar a Queue :(((((((((((((((


    public static void sort1(String[] a) {
        sort(a);
        Queue<Queue<String>> queue = new Queue<Queue<String>>();
        queue = sort1(a, 0, a.length - 1, queue);
        for (Queue<String> i : queue) {
            if (i.size() > 1) {
                StdOut.print("+ ");
                StdOut.println(i);
            }
        }
    }

    private static Queue<Queue<String>> sort1(String[] a, int lo, int hi, Queue<Queue<String>> queue) {
        if (hi <= lo) return queue;
        //exch(a, lo, (lo + hi) / 2);  // use middle element as partition || não uso o meio como partição e sim a primeira palavra
        int last = lo;
        Queue<String> queue1 = new Queue<String>(); // cria fila de anagramas
        queue1.enqueue(a[lo]);
        for (int i = lo + 1; i <= hi; i++) {
            if (less1(a[i], a[lo])) {
                //StdOut.println("enqueando: " + a[i] + " comparado com: " + a[lo]);
                queue1.enqueue(a[i]);
                //exch(a, ++last, i);
                last++;
            } else break;
        }
        //StdOut.println("acabou de enquear");

        queue.enqueue(queue1);
        //StdOut.println("printando queue de queue");

        //exch(a, lo, last);
        //sort(a, lo, last - 1, queue); //posso colocar aqui para ordernar em ordem alfabetica normal em.. sortqueue()
        sort1(a, last + 1, hi, queue);

        return queue;
    }

    private static boolean less1(String v, String w) {
        SignedWord sw0 = new SignedWord(v);
        SignedWord sw1 = new SignedWord(w);

        //(sw0.compareTo(sw1) < 0) && (v.compareTo(w) < 0);

        // devolve array na ordem certa, ou nao
        return (sw0.compareTo(sw1) == 0);
    }

    // exchange a[i] and a[j]
    private static void exch(Object[] a, int i, int j) {
        Object swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }


    public static void main(String[] args) {

        // TESTES
        String[] words = StdIn.readAllStrings();
        //String[] words = {"ovo", "casa", "sabrina", "voo", "asac", "saca", "bola", "olab"};
        //String[] words = {"casa", "saca", "aacs", "olab", "blao"};

        //Queue<String> queue1 = new Queue<String>();
        //for (String i : words) queue1.enqueue(i);

        //for (String i : words) StdOut.println(i);
        sort1(words);
        StdOut.println("//// sorted:");
        //for (String i : words) StdOut.println(i);
        StdOut.println("//// show:");
        //show(words);

        //StdOut.println("//// queue:");
        //Queue<String> queue = new Queue<String>();
        //StdOut.println("queue size: " + queue.size());
        //for (String i : words) queue.enqueue(i);
        //StdOut.println("queue size: " + queue.size());
        //for (String i : queue) StdOut.println(i);

        //StdOut.println("//// queue2:");
        //Queue<Queue<String>> queue2 = new Queue<Queue<String>>();
        //queue2.enqueue(queue);
        //queue2.enqueue(queue1);
        //for (Queue<String> i : queue2) {
        //StdOut.print("+ ");
        //if (i.size() >= 2) StdOut.println(i);
        //}

        // Como transformar queue em array? método ou iterativamente?

        //String num[] = {"6", "2", "1", "7"};
        //int[] teste = Merge.indexSort(num);
        //for (int i : teste) StdOut.println(i);
    }

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

        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {

            SignedWord sw0 = new SignedWord(arr[j]);
            //if (sw0.compareTo(sw1) == 0) StdOut.println(sw0 + " e " + sw1 + " são anagramas");
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

}
