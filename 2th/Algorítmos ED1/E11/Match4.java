/*	javac Match4.java
 *  java-introcs Match3
 */

import pieces.Nut;
import pieces.Bolt;

// Java program to solve nut and bolt problem using Quick Sort
public class Match {

    public static int indicebolts[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; //preciso criar esse indice do zero
    public static int indicenuts[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    //Driver method
    public static int[] match(NutsAndBolts nab) {
        int N = nab.N();
        int[] p = new int[N];
        boolean[] hit = new boolean[N];
        Bolt[] bolts = new Bolt[N];
        Nut[] nuts = new Nut[N];
        System.out.println("print " + bolts[0]);

        for (int j = 0; j < N; j++) {
            nuts[j] = nab.nuts(j);
            bolts[j] = nab.bolts(j);
        }
        // o array de nuts and bolts esta em nab
        matchnab(nab, 0, N - 1, p, bolts, nuts);

        return p;
    }

    private static void printArray(String[] arr) {
        for (String ch : arr) {
            System.out.print(ch + " ");
        }
        System.out.print("\n");
    }

    private static void matchnab(NutsAndBolts nab, int low, int high, int[] p, Bolt[] bolts, Nut[] nuts) {
        System.out.println("Erro 5");
        if (low < high) {
            System.out.println("Erro 1");
            int pivot = partitionnuts(nab, indicenuts, low, high, bolts[high], nuts);

            partitionbolts(nab, indicebolts, low, high, nuts[pivot], p, bolts);

            matchnab(nab, low, pivot - 1, p, bolts, nuts);

            matchnab(nab, pivot + 1, high, p, bolts, nuts);
        }
    }

    private static int partitionnuts(NutsAndBolts nab, int[] indice, int low, int high, Bolt pivot, Nut[] nuts) {
        int i = low;
        Nut temp1, temp2;

        for (int j = low; j < high; j++) {

            if (nuts[j].compareTo(pivot) == -1) {
                System.out.println("Erro 11");
                temp1 = nuts[i];
                nuts[i] = nuts[j];
                nuts[j] = temp1;
                i++;

            } else if (nuts[j].compareTo(pivot) == 0) {
                temp1 = nuts[j];
                nuts[j] = nuts[high];
                nuts[high] = temp1;
                j--;
            }
        }

        temp2 = nuts[i];
        nuts[i] = nuts[high];
        nuts[high] = temp2;

        return i;
    }

    private static int partitionbolts(NutsAndBolts nab, int[] indice, int low, int high, Nut pivot, int[] p, Bolt[] bolts) {
        int i = low;
        Bolt temp1, temp2;
        int indice1, indice2;
        System.out.println("Erro 6");

        for (int j = low; j < high; j++) {

            //System.out.println("Erro 8");
            if (bolts[j].compareTo(pivot) == -1) {
                System.out.println("Erro 9");
                temp1 = bolts[i];
                indice1 = indice[i];
                bolts[i] = bolts[j];
                indice[i] = indice[j]; //
                p[indicenuts[i]] = indice[j];
                bolts[j] = temp1;
                indice[j] = indice1; //
                p[indicenuts[j]] = indice1;
                i++;

            } else if (bolts[j].compareTo(pivot) == 0) {
                System.out.println("Erro 10");
                temp1 = bolts[j];
                indice1 = indice[j];
                bolts[j] = bolts[high];
                indice[j] = indice[high]; //
                p[indicenuts[j]] = indice[high];
                bolts[high] = temp1;
                indice[high] = indice1; //
                p[indicenuts[high]] = indice1;
                j--;
            }
        }

        temp2 = nab.bolts(i);
        indice2 = indice[i];
        bolts[i] = bolts[high];
        indice[i] = indice[high]; //
        p[indicenuts[i]] = indice[high];
        bolts[high] = temp2;
        indice[high] = indice2; //
        p[indicenuts[high]] = indice2;

        return i;
    }
}
