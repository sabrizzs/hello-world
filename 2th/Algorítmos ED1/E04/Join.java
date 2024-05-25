/******************************************************************************
 *
 * MAC0121 ALGORITMOS E ESTRUTURAS DE DADOS I
 * Aluno: Sabrina Araújo da Silva
 * Numero USP: 12566182
 * Tarefa: E04
 * Data: 22/09/21
 *
 * Baseado em LongestCommonSubsequence.java disponível em https://introcs.cs.princeton.edu/java/23recursion/
 *
 * DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA.  TODAS AS
 * PARTES DO PROGRAMA, EXCETO AS QUE SÃO BASEADAS EM MATERIAL FORNECIDO
 * PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK & WAYNE,
 * FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS
 * AS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUÍ NEM FACILITEI A DISTRIBUIÇÃO
 * DE CÓPIAS DESTA PROGRAMA.
 *
 ******************************************************************************/


public class Join {
    // tamanho do LCS
    public static String lcs(String x, String y) {
        int m = x.length(), n = y.length();
        int[][] opt = new int[m + 1][n + 1];
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (x.charAt(i) == y.charAt(j)) {
                    opt[i][j] = opt[i + 1][j + 1] + 1;
                } else {
                    opt[i][j] = Math.max(opt[i + 1][j], opt[i][j + 1]);
                }
            }
        }

        // LCS
        String lcs = "";
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (x.charAt(i) == y.charAt(j)) {
                lcs += x.charAt(i);
                i++;
                j++;
            } else if (opt[i + 1][j] >= opt[i][j + 1]) i++;
            else j++;
        }
        return lcs;
    }

    public static void join(String args0, String args1, int i, int j, String lcs, int k) {

        while (k < lcs.length()) {

            if (args0.charAt(i) == lcs.charAt(k)) {
                for (int q = j; q < args1.length(); q++) //ver qual letra de args1 é igual a letra do LCS
                    if (args1.charAt(q) == lcs.charAt(k)) { // se for igual imprimir
                        for (int w = j; w <= q; w++) {
                            StdOut.print(args1.charAt(w)); // imprimir da esquerda até a letra que é igual ao LCS

                        }
                        i += 1;
                        j = q + 1;
                        k += 1;
                        break;
                    }

            } else {
                StdOut.print(args0.charAt(i)); // imprimir letras de args0 que são diferentes de args1
                i += 1;
            }
        }

        if (k == lcs.length()) {
            for (int q = i; q < args0.length(); q++)
                StdOut.print(args0.charAt(q)); // imprimir resto do args0
            for (int e = j; e < args1.length(); e++)
                StdOut.print(args1.charAt(e)); // imprimir resto do args0
        }

    }


    public static void main(String[] args) {
        String arg0 = StdIn.readLine();
        String arg1 = StdIn.readLine();
        String lcs = lcs(arg0, arg1);

        join(arg0, arg1, 0, 0, lcs, 0);

    }

}

