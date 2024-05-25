/******************************************************************************
 *
 * MAC0121 ALGORITMOS E ESTRUTURAS DE DADOS I
 * Aluno: Sabrina Araújo da Silva
 * Numero USP: 12566182
 * Tarefa: E10
 * Data: 09/11/2021
 *
 * Baseado em MergeSort
 *
 * DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA.  TODAS AS
 * PARTES DO PROGRAMA, EXCETO AS QUE SÃO BASEADAS EM MATERIAL FORNECIDO
 * PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK & WAYNE,
 * FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS
 * AS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUÍ NEM FACILITEI A DISTRIBUIÇÃO
 * DE CÓPIAS DESTA PROGRAMA.
 *
 ******************************************************************************/

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Arrays;

public class BagVariant<Item extends Comparable<Item>> implements Iterable<Item> {

    private Node<Item> first;    // beginning of bag
    private int n;               // number of elements in bag

    //Ordena uma lista ligada com mergesort e in-place!
    public void sort() {
        mergeSort(first);
    }

    public Node<Item> mergeSort(Node<Item> lo) {
        if (lo == null || lo.next == null) return lo;

        Node<Item> mid = midBag(lo);
        Node<Item> lo2 = mid.next;
        mid.next = null;

        return (first = merge(mergeSort(lo), mergeSort(lo2)));
    }

    private Node<Item> merge(Node<Item> lo1, Node<Item> lo2) {
        Node<Item> result = new Node<Item>();
        Node<Item> current = result;

        while (lo1 != null && lo2 != null) {
            if (lo1.item.compareTo(lo2.item) < 0) {
                current.next = lo1;
                lo1 = lo1.next;
            } else {
                current.next = lo2;
                lo2 = lo2.next;
            }
            current = current.next;
        }

        if (lo1 != null) current.next = lo1;
        if (lo2 != null) current.next = lo2;
        return result.next;
    }

    // Encontra meio da bag
    private Node<Item> midBag(Node<Item> lo) {
        Node<Item> mid = lo;
        Node<Item> midseq = lo.next;

        while (midseq != null && midseq.next != null) {
            mid = mid.next;
            midseq = midseq.next.next;
        }
        return mid;
    }

    // helper linked list class
    private static class Node<Item extends Comparable<Item>> {
        private Item item;
        private Node<Item> next;
    }

    /**
     * Initializes an empty bag.
     */
    public BagVariant() {
        first = null;
        n = 0;
    }

    /**
     * Returns true if this bag is empty.
     *
     * @return {@code true} if this bag is empty;
     * {@code false} otherwise
     */
    public boolean isEmpty() {
        return first == null;
    }

    /**
     * Returns the number of items in this bag.
     *
     * @return the number of items in this bag
     */
    public int size() {
        return n;
    }

    /**
     * Adds the item to this bag.
     *
     * @param item the item to add to this bag
     */
    public void add(Item item) {
        Node<Item> oldfirst = first;
        first = new Node<Item>();
        first.item = item;
        first.next = oldfirst;
        n++;
    }


    /**
     * Returns an iterator that iterates over the items in this bag in arbitrary order.
     *
     * @return an iterator that iterates over the items in this bag in arbitrary order
     */
    public Iterator<Item> iterator() {
        return new LinkedIterator(first);
    }

    // an iterator, doesn't implement remove() since it's optional
    private class LinkedIterator implements Iterator<Item> {
        private Node<Item> current;

        public LinkedIterator(Node<Item> first) {
            current = first;
        }

        public boolean hasNext() {
            return current != null;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }

        public Item next() {
            if (!hasNext()) throw new NoSuchElementException();
            Item item = current.item;
            current = current.next;
            return item;
        }

    }

    /**
     * Unit tests the {@code Bag} data type.
     *
     * @param args the command-line arguments
     */
    public static void main(String[] args) {
        Bag<String> bag = new Bag<String>();
        while (!StdIn.isEmpty()) {
            String item = StdIn.readString();
            bag.add(item);
        }

        StdOut.println("size of bag = " + bag.size());
        for (String s : bag) {
            StdOut.println(s);
        }
    }

}
