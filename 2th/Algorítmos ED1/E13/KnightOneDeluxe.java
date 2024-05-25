/******************************************************************************
 *
 * MAC0121 ALGORITMOS E ESTRUTURAS DE DADOS I
 * Aluno: Sabrina Araújo da Silva
 * Numero USP: 12566182
 * Tarefa: E13
 * Data: 05/12
 *
 * Baseado em KnightOnePlain.java
 *
 * DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA.  TODAS AS
 * PARTES DO PROGRAMA, EXCETO AS QUE SÃO BASEADAS EM MATERIAL FORNECIDO
 * PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK & WAYNE,
 * FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS
 * AS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUÍ NEM FACILITEI A DISTRIBUIÇÃO
 * DE CÓPIAS DESTA PROGRAMA.
 *
 ******************************************************************************/

import edu.princeton.cs.algs4.StdOut;

public class KnightOneDeluxe {

    static int[][] board;
    static int N;
    static int arg;

    static int[] iMove = {2, 1, -1, -2, -2, -1, 1, 2};
    static int[] jMove = {1, 2, 2, 1, -1, -2, -2, -1};

    private static void initializeBoard() {
        board = new int[N][N];
    }

    private static void findTours(int i, int j, int k) {
        if (!valid(i, j) || board[i][j] != 0) return;
        board[i][j] = k;
        if (k == N * N) {
            if (arg == 1) printBoard();
            else StdOut.println("There is a Knight's tour on an " + N + "x" + N + " board.");
            System.exit(0);
        }

        IndexMinPQ<String> pq = new IndexMinPQ<String>(8);
        int[] mov = new int[8];

        for (int t = 0; t < 8; t++) {
            int ii = i + iMove[t];
            int jj = j + jMove[t];

            if (valid(ii, jj) && board[ii][jj] == 0) {
                int count = 0;
                for (int w = 0; w < 8; w++) {
                    int iii = ii + iMove[w];
                    int jjj = jj + jMove[w];

                    if (valid(iii, jjj) && board[iii][jjj] == 0) count++;
                }
                pq.insert(t, String.valueOf(count));
                mov[t] = count;
            }
        }

        while (!pq.isEmpty()) {
            int s = pq.delMin();
            int ii = i + iMove[s];
            int jj = j + jMove[s];
            findTours(ii, jj, k + 1);
        }

        board[i][j] = 0;
    }

    private static void findTours() {
        initializeBoard();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                findTours(i, j, 1);
            }
    }

    private static void printBoard() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                StdOut.printf("%2d ", board[i][j]);
            StdOut.println();
        }
    }

    private static boolean valid(int i, int j) {
        return 0 <= i && i < N && 0 <= j && j < N;
    }

    public static void main(String[] args) {
        N = Integer.parseInt(args[0]);
        arg = args.length;
        findTours();
        StdOut.println("Found no tours");
    }
}
