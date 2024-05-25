/*
 * javac-introcs TwoColoredBallsOO.java
 * java-introcs TwoColoredBallsOO
 */

import java.awt.Color;

public class TwoColoredBallsOO {

    public static void main(String[] args) {
	int SIZE = 512;
	double dt = 1.0;

	double[] p = {16 + 480 * Math.random(), 16 + 480 * Math.random()};
	double[] v = {30 * Math.random() - 15, 30 * Math.random() - 15};
        ColoredBallOO b1
	    = new ColoredBallOO(new Vector(p), new Vector(v),
				StdRandom.uniform(5, 40),
				Color.getHSBColor((float) Math.random(), 1.0f, 1.0f));
	double[] pp = {16 + 480 * Math.random(), 16 + 480 * Math.random()};
	double[] vv = {30 * Math.random() - 15, 30 * Math.random() - 15};
        ColoredBallOO b2
	    = new ColoredBallOO(new Vector(pp), new Vector(vv),
				StdRandom.uniform(5, 40),
				Color.getHSBColor((float) Math.random(), 1.0f, 1.0f));

        StdDraw.setXscale(0, SIZE);
        StdDraw.setYscale(0, SIZE);
        StdDraw.enableDoubleBuffering();

        while (true) {
            b1.move(SIZE, dt);
            b2.move(SIZE, dt);
            StdDraw.clear(StdDraw.GRAY);
            b1.draw();
            b2.draw();
            StdDraw.show();
            StdDraw.pause(20);
        }
    }
}
