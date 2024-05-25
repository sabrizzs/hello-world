/*	javac NutsAndBoltsMatch.java
 *  java-introcs NutsAndBoltsMatch
 */

// Java program to solve nut and bolt problem using Quick Sort
public class NutsAndBoltsMatch {

    public static int indicebolts[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    public static int indicenuts[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    //Driver method
    public static void main(String[] args) {
        // Nuts and bolts are represented as array of characters
        String nuts[] = {"93", "82", "05", "80", "96", "73", "47", "77", "99", "0"};

        String bolts[] = {"99", "77", "73", "80", "47", "0", "96", "82", "05", "93"};
        //String indicebolts[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

        //int p[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int[] p = new int[nuts.length];
        System.out.println("print " + p[4]);
        //boolean[] hit = new boolean[N];

        // Method based on quick sort which matches nuts and bolts
        matchPairs(nuts, bolts, 0, nuts.length - 1, p);

        System.out.println("Matched nuts and bolts are: ");
        printArray(nuts);
        System.out.println("Com indices nuts: ");
        printArrayint(indicenuts);
        printArray(bolts);
        System.out.println("Com indices bolts: ");
        printArrayint(indicebolts);

        System.out.println("Array p: ");
        printArrayint(p);

    }

    // Method to print the array
    private static void printArray(String[] arr) {
        for (String ch : arr) {
            System.out.print(ch + " ");
        }
        System.out.print("\n");
    }

    // Method to print the array
    private static void printArrayint(int[] arr) {
        for (int ch : arr) {
            System.out.print(ch + " ");
        }
        System.out.print("\n");
    }

    // Method which works just like quick sort
    private static void matchPairs(String[] nuts, String[] bolts, int low, int high, int[] p) {
        if (low < high) {
            int temp[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
            // Choose last character of bolts array for nuts partition.
            int pivot = partition(nuts, indicenuts, low, high, bolts[high], temp);

            // Now using the partition of nuts choose that for bolts
            // partition.
            partition(bolts, indicebolts, low, high, nuts[pivot], p);
            // Recur for [low...pivot-1] & [pivot+1...high] for nuts and
            // bolts array.
            matchPairs(nuts, bolts, low, pivot - 1, p);
            matchPairs(nuts, bolts, pivot + 1, high, p);
        }
    }

    // Similar to standard partition method. Here we pass the pivot element
    // too instead of choosing it inside the method.
    private static int partition(String[] arr, int[] indice, int low, int high, String pivot, int[] p) {
        int i = low;
        String temp1, temp2;
        int indice1, indice2;
        for (int j = low; j < high; j++) {

            if (arr[j].compareTo(pivot) < 0) {
                temp1 = arr[i];
                indice1 = indice[i];
                arr[i] = arr[j];
                indice[i] = indice[j]; //
                p[indicenuts[i]] = indice[j];
                arr[j] = temp1;
                indice[j] = indice1; //
                p[indicenuts[j]] = indice1;
                i++;

            } else if (arr[j] == pivot) {
                temp1 = arr[j];
                indice1 = indice[j];
                arr[j] = arr[high];
                indice[j] = indice[high]; //
                p[indicenuts[j]] = indice[high];
                arr[high] = temp1;
                indice[high] = indice1; //
                p[indicenuts[high]] = indice1;
                j--;
            }
        }
        temp2 = arr[i];
        indice2 = indice[i];
        arr[i] = arr[high];
        indice[i] = indice[high]; //
        p[indicenuts[i]] = indice[high];
        arr[high] = temp2;
        indice[high] = indice2; //
        p[indicenuts[high]] = indice2;
        // Return the partition index of an array based on the pivot
        // element of other array.
        //        if (bool == true)
        //            System.out.println(indicenuts[i] + " B tem que estar no indice = " + high);
        return i;
    }
}
