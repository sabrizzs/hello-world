/******************************************************************************
 *  Compilation:  javac teste.java
 *  Execution:    java-algs4 teste
 *
 *  A program with n^2 log n running time. Read in n integers
 *  and counts the number of triples that sum to exactly 0.
 *
 *  Limitations
 *  -----------
 *     - we ignore integer overflow
 *     - doesn't handle case when input has duplicates
 *
 ******************************************************************************/

import java.util.*;

public class teste {
    public static int count = 0;

    public static List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> res = new ArrayList<List<Integer>>();
        Arrays.sort(nums);
        Map<Integer, LinkedList<Integer>> map = new HashMap<Integer, LinkedList<Integer>>();

        for (int i = 0; i < nums.length; ++i) {
            if (!map.containsKey(nums[i])) map.put(nums[i], new LinkedList<Integer>());
            map.get(nums[i]).add(i);
        }

        for (int i = 0; i < nums.length - 2; ++i) {
            map.get(nums[i]).poll();
            for (int j = i + 1; j < nums.length - 1; ++j) {
                map.get(nums[j]).poll();
                int search_value = -(nums[i] + nums[j]);
                if (map.containsKey(search_value) && map.get(search_value).size() > 0) {
                    int start_index = map.get(search_value).peek();
                    int end_index = map.get(search_value).peekLast();
                    for (int k = start_index; k <= end_index; ++k) {
                        res.add(Arrays.asList(nums[i], nums[j], nums[k])); // add all triplets
                        count++;
                    }
                }
            }

            // restore all popped items
            for (int j = nums.length - 2; j > i; --j) {
                map.get(nums[j]).addFirst(j);
            }

            if (map.get(nums[i]).size() == 0) map.remove(nums[i]);
        }

        return res;
    }

    public static void main(String[] args) {
        List<List<Integer>> triplets = threeSum(new int[]{-10, -10, 2, 2, 2, 2, 8, 8});
        for (int i = 0; i < triplets.size(); ++i) System.out.println(triplets.get(i).toString());
        System.out.println(count);
    }

}
