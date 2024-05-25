/******************************************************************************
 *
 * MAC0121 ALGORITMOS E ESTRUTURAS DE DADOS I
 * Aluno: Sabrina Araújo da Silva
 * Numero USP: 12566182
 * Tarefa: E08
 * Data: 20/10/2021
 *
 *
 * DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA.  TODAS AS
 * PARTES DO PROGRAMA, EXCETO AS QUE SÃO BASEADAS EM MATERIAL FORNECIDO
 * PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK & WAYNE,
 * FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS
 * AS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUÍ NEM FACILITEI A DISTRIBUIÇÃO
 * DE CÓPIAS DESTA PROGRAMA.
 *
 ******************************************************************************/

import java.util.Arrays;

import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

public class ThreeSumSuper {

    public static void printAll(int[] a) {
        int n = a.length;
        Arrays.sort(a);
        for (int z = 0; z < n - 2; z++) {
            int i = a[z];
            int start = z + 1;
            int end = n - 1;

            while (start < end) {
                int j = a[start];
                int k = a[end];
                if (i + j + k == 0) {
                    if (a[start] != a[start + 1]) end = end - 1;
                    start++;
                    StdOut.println(i + " " + j + " " + k);
                } else if (i + j + k > 0) {
                    end--;
                } else
                    start++;
            }
        }
    }

    public static int count(int[] a) {
        int n = a.length;
        Arrays.sort(a);
        int count = 0;
        for (int z = 0; z < n - 2; z++) {
            int i = a[z];
            int start = z + 1;
            int end = n - 1;

            while (start < end) {
                int j = a[start];
                int k = a[end];
                if (i + j + k == 0) {
                    if (a[start] != a[start + 1]) end = end - 1;
                    start++;
                    count++;
                } else if (i + j + k > 0) {
                    end--;
                } else
                    start++;
            }
        }
        return count;
    }


    public static void main(String[] args) {
        int[] a = StdIn.readAllInts();
        int count = count(a);
        StdOut.println(count);
        if (count < 30) printAll(a);
    }
}
