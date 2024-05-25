/* javac-algs4 KnightOnePlain.java
 * $ java-algs4 KnightOnePlain 4
 * Found no tours
 * $ java-algs4 KnightOnePlain 8
 *  1 60 39 34 31 18  9 64
 * 38 35 32 61 10 63 30 17
 * 59  2 37 40 33 28 19  8
 * 36 49 42 27 62 11 16 29
 * 43 58  3 50 41 24  7 20
 * 48 51 46 55 26 21 12 15
 * 57 44 53  4 23 14 25  6
 * 52 47 56 45 54  5 22 13
 */

import edu.princeton.cs.algs4.StdOut;

public class KnightOnePlain {

    static int[][] board;
    static int N;

    static int[] iMove = {2, 1, -1, -2, -2, -1, 1, 2};
    static int[] jMove = {1, 2, 2, 1, -1, -2, -2, -1};

    private static void initializeBoard() {
        board = new int[N][N];
    }

    private static void findTours(int i, int j, int k) {
        if (!valid(i, j) || board[i][j] != 0) return;
        board[i][j] = k;
        if (k == N * N) {
            printBoard();
            System.exit(0);
        }
        for (int t = 0; t < 8; t++) {
            int ii = i + iMove[t];
            int jj = j + jMove[t];
            findTours(ii, jj, k + 1);
        }
        board[i][j] = 0;
    }

    private static void findTours() {
        initializeBoard();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                findTours(i, j, 1);
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
        findTours();
        StdOut.println("Found no tours");
    }
}
