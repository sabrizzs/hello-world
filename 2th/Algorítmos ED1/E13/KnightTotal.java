/*

  $ java-introcs KnightTotal 5
  1728 tours
  $ java-introcs KnightTotal 5 . | head -n11
   1  6 15 10 21 
  14  9 20  5 16 
  19  2  7 22 11 
   8 13 24 17  4 
  25 18  3 12 23 

   1  6 11 18 21 
  12 17 20  5 10 
   7  2 15 22 19 
  16 13 24  9  4 
  25  8  3 14 23 
  $ 

 */

public class KnightTotal {

    static int[][] board;
    static int N;

    static int[] iMove = {2, 1, -1, -2, -2, -1, 1, 2};
    static int[] jMove = {1, 2, 2, 1, -1, -2, -2, -1};

    static boolean verbose = false;
    static int T;
    
    private static void initializeBoard() {
	board = new int[N][N];
    }

    private static void findTours(int i, int j, int k) {
	if (!valid(i, j) || board[i][j] != 0) return;
	board[i][j] = k;
	if (k == N * N) {
	    T++;
	    if (verbose) { printBoard(); StdOut.println(); }
	    board[i][j] = 0;
	    return;
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
	verbose = args.length > 1;
	findTours();
	StdOut.println(T + " tours");
    }
}
