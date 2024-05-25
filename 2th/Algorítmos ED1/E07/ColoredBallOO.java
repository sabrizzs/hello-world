/******************************************************************************
 *
 * MAC0121 ALGORITMOS E ESTRUTURAS DE DADOS I
 * Aluno: Sabrina Araújo da Silva
 * Numero USP: 12566182
 * Tarefa: E07
 * Data: 10/10
 *
 * Baseado em ColoredBall.java
 *
 * DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA.  TODAS AS
 * PARTES DO PROGRAMA, EXCETO AS QUE SÃO BASEADAS EM MATERIAL FORNECIDO
 * PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK & WAYNE,
 * FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS
 * AS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUÍ NEM FACILITEI A DISTRIBUIÇÃO
 * DE CÓPIAS DESTA PROGRAMA.
 *
 ******************************************************************************/

import java.awt.Color;

public class ColoredBallOO {

    private Vector posicao;      // position
    private Vector velocidade;   // velocity
    private double radius;       // radius
    private Color color;         // color

    double[] val1 = new double[] {0.0,0.0};
    double[] val2 = new double[] {-0.05, 0.05};

    Vector p = new Vector(val1);
    Vector v = new Vector(val2);

    public ColoredBallOO(Vector p, Vector v, double r, Color c) {
        posicao = p;
        velocidade = v;
        radius = StdRandom.uniform(5.0, 12.0);
        color = Color.getHSBColor((float) StdRandom.uniform(0.0, 1.0), 0.8f, 0.8f);
    }

    public Vector pos(){return posicao;}                //posição
    public Vector vel(){return velocidade;}             //velocidade
    public double radius(){return radius;}              //raio da bola
    public void setVel(Vector v){velocidade = v;}       //valor v para a velocidade da bola

    public void updatePosition(double dt){              //atualiza a posição da bola para a posição p + dt * v
        posicao = posicao.plus(velocidade.scale(dt));
    }

    public void treatWalls(double size, double dt){     // colisão com a parede
        double vx = velocidade.cartesian(0);
        double vy = velocidade.cartesian(1);

        if ((posicao.cartesian(0) + velocidade.cartesian(0) * dt > size - radius) || (posicao.cartesian(0) + velocidade.cartesian(0) * dt < radius)) {
            double[] x1 = new double[] {vx*-1, vy};
            Vector vx1 = new Vector(x1);
            setVel(vx1);
        }

        if ((posicao.cartesian(1) + velocidade.cartesian(1) * dt > size - radius) || (posicao.cartesian(1) + velocidade.cartesian(1) * dt < radius)){
            double[] x2 = new double[] {vx, vy*-1};
            Vector vx2 = new Vector(x2);
            setVel(vx2);
        }
    }

    public void move(double size, double dt){
        treatWalls(size, dt);
        updatePosition(dt);
    }

    public void draw(){ //desenha a bola
        StdDraw.setPenColor(color);
        StdDraw.filledCircle(posicao.cartesian(0),posicao.cartesian(1), radius);
    }

}
