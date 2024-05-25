/******************************************************************************
 *
 * MAC0121 ALGORITMOS E ESTRUTURAS DE DADOS I
 * Aluno: Sabrina Araújo da Silva
 * Numero USP: 12566182
 * Tarefa: E05
 * Data: 26/09/21
 *
 * Baseado em Permutations.java
 *
 * DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA.  TODAS AS
 * PARTES DO PROGRAMA, EXCETO AS QUE SÃO BASEADAS EM MATERIAL FORNECIDO
 * PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK & WAYNE,
 * FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS
 * AS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUÍ NEM FACILITEI A DISTRIBUIÇÃO
 * DE CÓPIAS DESTA PROGRAMA.
 *
 ******************************************************************************/


public class ABPerms {

    static int numperm = 0;

    public static int lislds(String s, int ordem) {

        int[] A = new int[26];

        int N = s.length();

        int lislds = 0;

        if (ordem == 0) {
            // calcula LIS
            for (int i = 0; i < N; i++) {

                int val = (int) s.charAt(i) - 97;

                int atual = 0;

                for (int j = 0; j < val; j++) {
                    atual = Math.max(atual, A[j]);
                }

                atual++;

                lislds = Math.max(lislds, atual);

                A[val] = Math.max(A[val], atual);
            }
        } else {
            // calcula LDS
            for (int i = N - 1; i >= 0; i--) {

                int val = (int) s.charAt(i) - 97;

                int atual = 0;

                for (int j = 0; j < val; j++) {
                    atual = Math.max(atual, A[j]);
                }

                atual++;

                lislds = Math.max(lislds, atual);

                A[val] = Math.max(A[val], atual);
            }
        }

        // retorna LIS/LDS
        return lislds;
    }


    // (a,b)-permutações
    public static void perm(String s, int k, int j, String imprimir) {
        perm("", s, k, j, imprimir);
    }

    private static void perm(String prefix, String s, int k, int j, String imprimir) {
        int n = s.length();

        int lis = lislds(prefix, 0);
        if (lis > k) return;
        int lds = lislds(prefix, 1);
        if (lds > j) return;


        if (n == 0) {
            if (imprimir.equals("-v") || imprimir.equals("-V")) StdOut.println(prefix);
            numperm += 1;

        } else {
            for (int i = 0; i < n; i++)
                perm(prefix + s.charAt(i), s.substring(0, i) + s.substring(i + 1, n), k, j, imprimir);
        }

    }

    private static void swap(char[] a, int i, int j) {
        char c = a[i];
        a[i] = a[j];
        a[j] = c;
    }


    public static void main(String[] args) {

        int n = Integer.parseInt(args[0]);
        String alphabet = "abcdefghijklmnopqrstuvwxyz";
        String elements = alphabet.substring(0, n);

        String s = elements;
        int k = Integer.parseInt(args[1]);
        int j = Integer.parseInt(args[2]);

        String imprimir = "";
        if (args.length == 4) imprimir = args[3];

        if (k * j >= n) perm(elements, k, j, imprimir);
        if (!imprimir.equals("-v")) StdOut.print(numperm);

    }

}

