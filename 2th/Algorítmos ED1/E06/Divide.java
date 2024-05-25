/******************************************************************************
 *
 * MAC0121 ALGORITMOS E ESTRUTURAS DE DADOS I
 * Aluno: Sabrina Araújo da Silva
 * Numero USP: 12566182
 * Tarefa: E06
 * Data: 03/10/21
 *
 * DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA.  TODAS AS
 * PARTES DO PROGRAMA, EXCETO AS QUE SÃO BASEADAS EM MATERIAL FORNECIDO
 * PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK & WAYNE,
 * FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS
 * AS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUÍ NEM FACILITEI A DISTRIBUIÇÃO
 * DE CÓPIAS DESTA PROGRAMA.
 *
 ******************************************************************************/

public class Divide {
    private static boolean verbose;
    private static int best = 0;
    private static int[] b;
    private static int lim = 0;
    private static int inf = 0;
    private static boolean ind = false;

    public static void enumerate(int[] val, int[] a, int k) {
        if (k == a.length) {
            int t = min(val, a);
            if (t > best) {
                best = t;
                if (best == inf) copy(b, a);
            }
            return;
        }

        a[k] = 0;
        if (best >= inf) return;
        if (ind == true) {
            ind = false;
            return;
        }
        enumerate(val, a, k + 1);

        a[k] = 1;
        if (best >= inf) return;
        if (ind == true) {
            ind = false;
            return;
        }
        enumerate(val, a, k + 1);

        a[k] = 2;
        if (best >= inf) return;
        if (ind == true) {
            ind = false;
            return;
        }
        enumerate(val, a, k + 1);

    }

    public static int scheduleBrute(int[] val) {
        int[] a = new int[val.length];
        a[0] = 0;
        b = new int[val.length];
        enumerate(val, a, 1);
        return best;
    }

    public static int min(int[] val, int[] a) {
        int N = a.length;
        int A = 0, B = 0, C = 0;
        for (int i = 0; i < N; i++)
            switch (a[i]) {
                case 0:
                    if (A > lim) {
                        ind = true;
                        return -1;
                    }
                    A += val[i];
                    break;
                case 1:
                    if (B > lim) {
                        ind = true;
                        return -1;
                    }
                    B += val[i];
                    break;
                case 2:
                    if (C > lim) {
                        ind = true;
                        return -1;
                    }
                    C += val[i];
                    break;
            }
        return Math.min(Math.min(A, B), C);
    }


    public static int sum(int[] val) {
        int N = val.length, S = 0;
        for (int i = 0; i < N; i++) S += val[i];
        return S;
    }

    public static void show(int[] a, int[] val) {
        for (int i = 0; i < 3; i++)
            show(a, val, i);
    }

    public static void show(int[] a, int[] val, int i) {
        int N = a.length, s;
        System.out.print(i + ": ");
        s = 0;
        for (int j = 0; j < N; j++) {
            if (a[j] == i) {
                s += val[j];
                System.out.print(val[j] + " ");
            }
        }
        System.out.println("(sum: " + s + ")");
    }

    public static void shown(int[] val) {
        int N = val.length, s;
        System.out.print(0 + ": ");
        s = 0;
        for (int j = 0; j < N; j++) {
            s += val[j];
            System.out.print(val[j] + " ");
        }
        System.out.println("(sum: " + s + ")");
    }

    public static void copy(int[] a, int[] b) {
        for (int i = 0; i < a.length; i++) a[i] = b[i];
    }

    public static void main(String[] args) {
        verbose = args.length > 0;
        int[] val = StdIn.readAllInts();

        int sum = sum(val);
        inf = sum / 3;
        lim = (sum / 3) + (sum % 3);
        int opt = scheduleBrute(val);

        if (opt >= sum / 3) {
            System.out.println("There is a solution");
            if (verbose) {
                System.out.println("Optimal value: " + opt
                        + " (sum: " + sum + " / want: " + sum / 3
                        + " / sum mod 3 = " + sum % 3 + ")");
                if (verbose) show(b, val);
            }
        } else {
            System.out.println("There is no solution");
            if (verbose) {
                shown(val);
                System.out.println("1: (sum:0)");
                System.out.println("2: (sum:0)");
            }
            System.out.println("Best I found (not necessarily optimal): " + 0
                    + " (sum: " + sum + " / want: " + sum / 3
                    + " / sum mod 3 = " + sum % 3 + ")");
        }

    }
}

