/*

  From S & W

 */

public class GrayCode {

    static int[] a;
    static int N;

    private static void print(int[] a) {
	for (int i = 0; i < a.length; i++) 
	    StdOut.print(a[i] + " ");
	StdOut.println();
    }

    private static void enumerate(int k) {
	if (k == N) {
	    print(a);
	    return;
	}
	enumerate(k + 1);
	a[k] = 1 - a[k];
	enumerate(k + 1);
    }

    public static void enumerate() {
	a = new int[N];
	enumerate(0);
    }

    public static void main(String[] args) {
	N = Integer.parseInt(args[0]);
	enumerate();
    }
    
}
