package pieces;

public final class Nut {
    final int d;

    public Nut(int d) { this.d = d; }

    public int compareTo(Bolt b) {
	if (this.d - b.d < 0) return -1;
	if (this.d - b.d > 0) return  1;
	return 0;
    }

    // public String toString() { return String.format("%3d", d); }
    
} 
