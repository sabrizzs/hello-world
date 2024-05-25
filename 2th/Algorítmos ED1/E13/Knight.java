/* 
 * From S&W
 * 
 * $ java-introcs Knight 5 0 0 
 * 304 tours
 * $ java-introcs Knight 5 0 1 
 * 0 tours
 * $ java-introcs Knight 5 0 2 
 * 56 tours
 * $ java-introcs Knight 5 1 1 
 * 56 tours
 * $ java-introcs Knight 5 1 2 
 * 0 tours
 * $ java-introcs Knight 5 2 2 
 * 64 tours
 */ 

public class Knight {

    static int[][] board;
    static int N;

    static int[] iMove = {2, 1, -1, -2, -2, -1, 1, 2};
    static int[] jMove = {1, 2, 2, 1, -1, -2, -2, -1};

    static boolean verbose = false;
    static int T;
    
    private static void initialize(int N) {
	board = new int[N][N];
    }

    private static void findTours(int i, int j) {
	initialize(N);
	findTours(i, j, 1);
    }

    private static void findTours(int i, int j, int k) {
	board[i][j] = k;
	if (k == N * N) {
	    T++;
	    if (verbose)
		printBoard();
	    board[i][j] = 0;
	    return;
	} 
	for (int t = 0; t < 8; t++) {
	    int ii = i + iMove[t];
	    int jj = j + jMove[t];
	    if (valid(ii, jj) && board[ii][jj] == 0)
		findTours(ii, jj, k + 1);
	}
	board[i][j] = 0;
    }

    private static void printBoard() {
	for (int i = 0; i < N; i++) {
	    for (int j = 0; j < N; j++) 
		StdOut.printf("%2d ", board[i][j]);
	    StdOut.println();
	}
	StdOut.println();
    }

    private static boolean valid(int i, int j) {
	return 0 <= i && i < N && 0 <= j && j < N;
    }

    public static void main(String[] args) {
	N = Integer.parseInt(args[0]);
	int i = Integer.parseInt(args[1]);
	int j = Integer.parseInt(args[2]);
	verbose = args.length > 3;
	findTours(i, j);
	StdOut.println(T + " tours");
    }
    
}
