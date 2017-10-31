
package com.pyatkinmv;

import java.util.Comparator;

public class MyComparator implements Comparator {
    @Override
    public int compare(Object obj1, Object obj2) {
        Integer p1 = ((Integer) obj1);
        Integer p2 = ((Integer) obj2);

        if (p1 > p2) {
            return 1;
        } else if (p1 < p2){
            return -1;
        } else {
            return 0;
        }
    }
}
