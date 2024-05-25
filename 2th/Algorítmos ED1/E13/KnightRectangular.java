/*

  $ java-introcs KnightRectangular 3 4 0 0 
  2 tours
  $ java-introcs KnightRectangular 3 4 0 0 .
   1  4  7 10 
  12  9  2  5 
   3  6 11  8 

   1  4  7 10 
   8 11  2  5 
   3  6  9 12 

  2 tours
  $ java-introcs KnightRectangular 3 8 0 0 
  82 tours
  $ java-introcs KnightRectangular 5 5 0 0  
  304 tours
  $ 

 */

public class KnightRectangular {

    static int[][] board;
    static int M, N;

    static int[] iMove = {2, 1, -1, -2, -2, -1, 1, 2};
    static int[] jMove = {1, 2, 2, 1, -1, -2, -2, -1};

    static boolean verbose = false;
    static int T;
    
    private static void initializeBoard() {
	board = new int[M][N];
    }

    private static void findTours(int i, int j) {
	initializeBoard();
	findTours(i, j, 1);
    }

    private static void findTours(int i, int j, int k) {
	if (!valid(i, j) || board[i][j] != 0) return;
	board[i][j] = k;
	if (k == M * N) {
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

    private static void printBoard() {
	for (int i = 0; i < M; i++) {
	    for (int j = 0; j < N; j++) 
		StdOut.printf("%2d ", board[i][j]);
	    StdOut.println();
	}
    }

    private static boolean valid(int i, int j) {
	return 0 <= i && i < M && 0 <= j && j < N;
    }

    public static void main(String[] args) {
	M = Integer.parseInt(args[0]);
	N = Integer.parseInt(args[1]);
	int i = Integer.parseInt(args[2]);
	int j = Integer.parseInt(args[3]);
	verbose = args.length > 4;
	findTours(i, j);
	StdOut.println(T + " tours");
    }
}
