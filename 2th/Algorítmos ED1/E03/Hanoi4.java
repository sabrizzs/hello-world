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
 ******************************************************************************/

public class Hanoi4 {


    //transfere o disco do topo
    private static String[] topDisc(int nDiscos, int origem, int intermed1, int destino, int intermed2, String[] moves, String[] args) {
        int k = (int) (nDiscos - Math.round(Math.sqrt(2 * nDiscos + 1)) + 1); //fórmula de k do algoritmo de Frame-Steward

        if (k == 0) {

            //se args.length > 1 guardar movimentos para depois imprimir na main
            if (args.length > 1) {
                for (int i = 0; i < moves.length; i++) {
                    if (moves[i] == null) {
                        moves[i] = 1 + " " + destino + "  ";
                        return moves;
                    }
                }
            } else {
                StdOut.print(1 + " " + destino + "  ");
                return moves;
            }
        }

        topDisc(k, origem, destino, intermed1, intermed2, moves, args);

        hanoi3(nDiscos - k, k, origem, intermed2, destino, moves, args);

        topDisc(k, intermed1, origem, destino, intermed2, moves, args);

        return moves;
    }

    //transfere os discos entre 3 torres
    private static String[] hanoi3(int nDiscos, int k, int origem, int intermed1, int destino, String[] moves, String[] args) {
        if (nDiscos == 0) return moves;

        hanoi3(nDiscos - 1, k, origem, destino, intermed1, moves, args);

        //se args.length > 1 guardar movimentos para depois imprimir na main
        if (args.length > 1) {
            for (int i = 0; i < moves.length; i++) {
                if (moves[i] == null) {
                    moves[i] = (nDiscos + k) + " " + destino + "  ";
                    break;
                }
            }
        } else {
            StdOut.print((nDiscos + k) + " " + destino + "  ");
        }

        hanoi3(nDiscos - 1, k, intermed1, origem, destino, moves, args);

        return moves;
    }

    //calcula tamanho do array com valor de movimentos esperado
    public static int n(int N) {
        int n = 0, b = 0;
        while (b < N) {
            b += n;
            n++;
        }
        return n - 1;
    }

    public static int f(int n) {
        return (n - 1) * (1 << n) + 1;
    }

    public static void main(String[] args) {
        int nDiscos = Integer.parseInt(args[0]);

        String[] moves = new String[f(n(nDiscos))];

        String[] moves1 = topDisc(nDiscos, 0, 2, 1, 3, moves, args);

        //imprimir o numero de movimentos
        if (args.length > 1) {

            int moves2 = 0;
            for (int i = 0; i < moves1.length; i++) {
                if (moves1[i] != null)
                    moves2 += 1;
            }

            if (f(n(nDiscos)) == 1) {
                StdOut.println(moves2 + " move");
            } else {
                StdOut.println(moves2 + " moves");
            }

            for (int i = 0; i < moves1.length; i++) {
                if (moves1[i] != null)
                    System.out.printf(moves1[i]);
            }
        }
    }
}

