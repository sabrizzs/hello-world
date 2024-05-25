/******************************************************************************
 *
 * MAC0121 ALGORITMOS E ESTRUTURAS DE DADOS I
 * Aluno: Sabrina Araújo da Silva
 * Numero USP: 12566182
 * Tarefa: E03
 * Data: 12/09
 *
 * Baseado em AnimatedHanoi.java, Algoritmo de Frame-Stewart
 *
 * DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA.  TODAS AS
 * PARTES DO PROGRAMA, EXCETO AS QUE SÃO BASEADAS EM MATERIAL FORNECIDO
 * PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK & WAYNE,
 * FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS
 * AS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUÍ NEM FACILITEI A DISTRIBUIÇÃO
 * DE CÓPIAS DESTA PROGRAMA.
 *
 * javac-introcs HanoiVelho.java
 * java-introcs HanoiVelho N
 ******************************************************************************/

/******************************************************************************
 *
 * MAC0121 ALGORITMOS E ESTRUTURAS DE DADOS I
 * Aluno: Sabrina Araújo da Silva
 * Numero USP: 12566182
 * Tarefa: E03
 * Data: 12/09
 *
 * Baseado em AnimatedHanoi.java, Algoritmo de Frame-Stewart
 *
 * DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA.  TODAS AS
 * PARTES DO PROGRAMA, EXCETO AS QUE SÃO BASEADAS EM MATERIAL FORNECIDO
 * PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK & WAYNE,
 * FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS
 * AS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUÍ NEM FACILITEI A DISTRIBUIÇÃO
 * DE CÓPIAS DESTA PROGRAMA.
 *
 * javac-introcs Hanoi4.java
 * java-introcs Hanoi4 N
 ******************************************************************************/

public class HanoiVelho {


    //transfere o disco do topo
    private static void topDisc(int nDiscos, int origem, int intermed1, int destino, int intermed2) {
        int k = (int) (nDiscos - Math.round(Math.sqrt(2 * nDiscos + 1)) + 1); //fórmula de k do algoritmo de Frame-Steward

        if (k == 0) {
            StdOut.print(1 + " " + destino + "  ");
            return;
        }
        topDisc(k, origem, destino, intermed1, intermed2);

        hanoi3(nDiscos - k, k, origem, intermed2, destino);

        topDisc(k, intermed1, origem, destino, intermed2);
    }

    //transfere os discos entre 3 torres
    private static void hanoi3(int nDiscos, int k, int origem, int intermed1, int destino) {
        if (nDiscos == 0) return;

        hanoi3(nDiscos - 1, k, origem, destino, intermed1);

        StdOut.print((nDiscos + k) + " " + destino + "  ");

        hanoi3(nDiscos - 1, k, intermed1, origem, destino);
    }

    public static int n(int N) {
        int n = 0, b = 0;
        while (b < N) {
            b += n;
            n++;
        }
        return n - 1;
    }

    public static boolean special(int N) {
        int n = n(N);
        return N == (n + 1) * n / 2;
    }

    public static int f(int n) {
        return (n - 1) * (1 << n) + 1;
    }

    public static void main(String[] args) {
        int nDiscos = Integer.parseInt(args[0]);

        if (special(nDiscos) && args.length > 1) {
            if (f(n(nDiscos)) == 1) {
                StdOut.println(f(n(nDiscos)) + " move");
            } else {
                StdOut.println(f(n(nDiscos)) + " moves");
            }
        }
        topDisc(nDiscos, 0, 2, 1, 3);

    }
}
