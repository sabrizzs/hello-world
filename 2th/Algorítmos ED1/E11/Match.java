/*	javac Match.java
 *  javac-algs4 NutsAndBolts.java
 *  javac-algs4 GenerateAndMatch.java
 *  java-algs4 GenerateAndMatch  10  10 1212021
 */

import pieces.Nut;
import pieces.Bolt;

public class Match {

    public static int[] match(NutsAndBolts nab) {
        int N = nab.N();

        Bolt[] bolts = new Bolt[N];
        Nut[] nuts = new Nut[N];

        int[] indicebolts = new int[N];
        int[] indicenuts = new int[N];

        for (int j = 0; j < N; j++) {
            nuts[j] = nab.nuts(j);
            bolts[j] = nab.bolts(j);
            indicebolts[j] = j;
            indicenuts[j] = j;
        }

        int[] p = new int[N];
        int[] temp = new int[N];

        matchNB(nuts, bolts, 0, N - 1, p, temp, indicebolts, indicenuts);

        return p;
    }

    private static void matchNB(Nut[] nuts, Bolt[] bolts, int low, int high, int[] p, int[] temp, int[] indicebolts, int[] indicenuts) {
        if (low < high) {
            // seleciona pivô entre as porcas
            int pivot = partitionNuts(nuts, bolts, low, high, temp);
            // separa os parafusos de acordo com o pivõ
            partitionBolts(bolts, nuts, indicebolts, low, high, pivot, p, indicebolts, indicenuts);

            matchNB(nuts, bolts, low, pivot - 1, p, temp, indicebolts, indicenuts);
            matchNB(nuts, bolts, pivot + 1, high, p, temp, indicebolts, indicenuts);
        }
    }

    private static int partitionNuts(Nut[] nuts, Bolt[] bolts, int low, int high, int[] p) {
        int i = low;
        Nut temp1, temp2;

        for (int j = low; j < high; j++) {

            if (nuts[j].compareTo(bolts[high]) == -1) {
                temp1 = nuts[i];
                nuts[i] = nuts[j];
                nuts[j] = temp1;
                i++;

            } else if (nuts[j].compareTo(bolts[high]) == 0) {
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

    // ordena os parafusos, assim como os indices e o p
    private static int partitionBolts(Bolt[] bolts, Nut[] nuts, int[] indice, int low, int high, int pivot, int[] p, int[] indicebolts, int[] indicenuts) {
        int i = low;
        Bolt temp1, temp2;
        int indice1, indice2;

        for (int j = low; j < high; j++) {

            if (bolts[j].compareTo(nuts[pivot]) == -1) {
                temp1 = bolts[i];
                indice1 = indice[i];
                bolts[i] = bolts[j];
                indice[i] = indice[j];
                p[indicenuts[i]] = indice[j];
                bolts[j] = temp1;
                indice[j] = indice1;
                p[indicenuts[j]] = indice1;
                i++;

            } else if (bolts[j].compareTo(nuts[pivot]) == 0) {
                temp1 = bolts[j];
                indice1 = indice[j];
                bolts[j] = bolts[high];
                indice[j] = indice[high];
                p[indicenuts[j]] = indice[high];
                bolts[high] = temp1;
                indice[high] = indice1;
                p[indicenuts[high]] = indice1;
                j--;
            }
        }
        temp2 = bolts[i];
        indice2 = indice[i];
        bolts[i] = bolts[high];
        indice[i] = indice[high];
        p[indicenuts[i]] = indice[high];
        bolts[high] = temp2;
        indice[high] = indice2;
        p[indicenuts[high]] = indice2;
        return i;
    }
}
