/******************************************************************************
 *
 * MAC0121 ALGORITMOS E ESTRUTURAS DE DADOS I
 * Aluno: Sabrina Araújo da Silva
 * Numero USP: 12566182
 * Tarefa: E02
 * Data: 05/09/2021
 *
 * Baseado em BouncingBall.java, OneSimpleAttractors.java, SimpleAttractor.java.
 *
 * DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA.  TODAS AS
 * PARTES DO PROGRAMA, EXCETO AS QUE SÃO BASEADAS EM MATERIAL FORNECIDO
 * PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK & WAYNE,
 * FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS
 * AS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUÍ NEM FACILITEI A DISTRIBUIÇÃO
 * DE CÓPIAS DESTA PROGRAMA.
 ******************************************************************************/

public class Billiards {
    public static void main(String[] args) {

        // coordenadas do sistema
        StdDraw.setXscale(-1.0, 1.0);
        StdDraw.setYscale(-1.0, 1.0);
        StdDraw.enableDoubleBuffering();

        // variáveis
        double rx = 0.0, ry = 0.0;        // posição
        double vx = 0.0, vy = 0.0;        // velocidade
        double radius = 0.05;             // raio da bolinha
        double mass = 0.5;                // massa da bolinha
        double dt = 0.5;
        double drag = 0.04;               // variável para desaceleração

        while (true) {

            // quando o mouse é pressionado adiciona uma velocidade à bolinha
            if (StdDraw.isMousePressed()) {

                // distância entre o mouse e a bolinha
                double x = StdDraw.mouseX();
                double y = StdDraw.mouseY();
                double distancia = Math.sqrt(Math.pow((x - rx), 2) + Math.pow((y - ry), 2));

                // força e aceleração
                double forcax = 0.01 / Math.pow(distancia, 2);
                double forcay = 0.01 / Math.pow(distancia, 2);
                double ax = forcax / mass;
                double ay = forcay / mass;

                // condição para a bolinha não estourar o limite de velocidade
                if (ax > 0.5) ax = 0.5;
                if (ay > 0.5) ay = 0.5;

                // direção da aceleração
                if (x > rx) ax = -1 * ax;
                if (y > ry) ay = -1 * ay;

                // velocidade
                vx += ax;
                vy += ay;

            }

            // paredes do sistema
            if (Math.abs(rx + vx) > 1.0 - radius) vx = -vx;
            if (Math.abs(ry + vy) > 1.0 - radius) vy = -vy;

            // desaceleração da bola
            double fx = -drag * vx;
            double fy = -drag * vy;

            // velocidade e posição
            vx += fx * dt / mass;
            vy += fy * dt / mass;
            rx += vx * dt;
            ry += vy * dt;

            // limpar o fundo
            StdDraw.clear(StdDraw.LIGHT_GRAY);

            // desenho da bolinha
            StdDraw.setPenColor(StdDraw.BLACK);
            StdDraw.filledCircle(rx, ry, radius);

            StdDraw.show();
            StdDraw.pause(20);

        }
    }
}
