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

public class KnightOneSuperDeluxe {

    static int[][] board;
    static int N;
    static boolean breakr = false;
    static boolean found = false;
    static boolean stop = false;

    static int[] iMove = {2, 1, -1, -2, -2, -1, 1, 2};
    static int[] jMove = {1, 2, 2, 1, -1, -2, -2, -1};

    private static void initializeBoard() {
        board = new int[N][N];
    }

    private static void findTours(int i, int j, int k, Stopwatch timer) {
        if (stop == true) return;
        double time = timer.elapsedTime();
        if (time > 1) {
            stop = true;
            return;
        }
        if (breakr == true) return;

        if (!valid(i, j) || board[i][j] != 0) {
            return;
        }
        board[i][j] = k;
        if (k == N * N || N == 1) {
            StdOut.println(" There is a Knight's tour on an " + N + "x" + N + " board");
            found = true;
            breakr = true;
            return;
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
            findTours(ii, jj, k + 1, timer);
        }

        board[i][j] = 0;
    }

    private static void findTours() {
        initializeBoard();
        if (N == 1) {
            found = true;
            StdOut.println(" (0, 0) : There is a Knight's tour on an " + N + "x" + N + " board");
        }
        for (int i = 0; i < N / 2; i++)
            for (int j = 0; j < N / 2; j++) {
                StdOut.print(" (" + i + ", " + j + ") :");
                Stopwatch timer = new Stopwatch();
                findTours(i, j, 1, timer);
                if (breakr == true) {
                    breakr = false;
                    return;
                }
                stop = false;
            }
    }

    private static boolean valid(int i, int j) {
        return 0 <= i && i < N && 0 <= j && j < N;
    }

    public static void main(String[] args) {
        int lo = Integer.parseInt(args[0]);
        int hi = Integer.parseInt(args[1]);
        while (lo <= hi) {
            N = lo;
            StdOut.print(lo + ":");
            findTours();
            if (found == false) StdOut.println(" Found no tours");
            else found = false;
            lo++;
        }
    }
}
