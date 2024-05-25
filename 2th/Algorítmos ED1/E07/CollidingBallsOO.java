/******************************************************************************
 *
 *  Dependencies: StdDraw.java, Vector.java, ColoredBallOO
 *    javac-introcs CollidingBallsOO.java
 *  % java-introcs CollidingBallsOO 10
 *
 *  Limitations
 *  -----------
 *   - Inefficient since it performs N^2 collision checks per dt.
 *
 *   - Can miss collisions. Use event-based simulation and a priority
 *     queue instead of time-based simulation to fix.
 *
 *   - physics not correct (and you can notice; easier to see with more balls)
 *
 ******************************************************************************/

import java.awt.Color;

public class CollidingBallsOO {

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        double dt = 1.0;

        // initialize positions and velocities at random
	ColoredBallOO[] b = new ColoredBallOO[N];

	for (int i = 0; i < N; i++) {
	    double[] p = {16 + 480 * Math.random(), 16 + 480 * Math.random()};
	    double[] v = {10 * Math.random() - 5, 10 * Math.random() - 5};
	    b[i] = new ColoredBallOO(new Vector(p), new Vector(v), StdRandom.uniform(3, 10),
				     Color.getHSBColor((float) Math.random(), 1.0f, 1.0f));
	}

        int SIZE = 512;
        StdDraw.setXscale(0, SIZE);
        StdDraw.setYscale(0, SIZE);
        StdDraw.enableDoubleBuffering();

        while (true) {
            StdDraw.clear(Color.BLACK);

            for (int i = 0; i < N; i++)
		b[i].treatWalls(SIZE, dt);

            // detect collision with other particles
            for (int i = 0; i < N; i++)
                for (int j = i + 1; j < N; j++) {
                    // if collision swap velocities
                    if (b[i].pos().distanceTo(b[j].pos()) <= b[i].radius() + b[j].radius()) {
			Vector t = b[i].vel();
			b[i].setVel(b[j].vel());
			b[j].setVel(t);
                        break;               // only pairwise collisions
                    }
                }

            for (int i = 0; i < N; i++)
		b[i].updatePosition(dt);

            for (int i = 0; i < N; i++)
		b[i].draw();

	    StdDraw.show();
            StdDraw.pause(50);
	}
    }
}
