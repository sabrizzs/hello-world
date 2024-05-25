package pieces;

public final class Bolt {
    final int d;

    public Bolt(int d) { this.d = d; }

    public int compareTo(Nut n) {
	if (this.d - n.d < 0) return -1;	
	if (this.d - n.d > 0) return  1;	
	return 0;
    }

    // public String toString() { return String.format("%3d", d); }

} 
