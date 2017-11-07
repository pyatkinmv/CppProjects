package com.pyatkinmv;

import java.util.Arrays;
import java.util.Random;

public class Main{

    static int numOfCompars;

    public static void main(String[] args) {
        Random rand = new Random();
        Integer[] arr1 = new Integer[100000];
        for(int i=0;i<100000;++i)
            arr1[i] = rand.nextInt(100000);

        Integer[] arr2 = Arrays.copyOf(arr1,100000);

        QuickSort<Integer> quickSort = new QuickSort<>();
        quickSort.sort(arr1,0,99999, (o1, o2)-> {
                numOfCompars++;
                return ((Integer) o1).compareTo((Integer) o2);
            }
        );

//        for(Integer value: arr1){
//            System.out.print(value.intValue()+" ");
//        }
//        System.out.println();
        System.out.println("Number of comparisons in my method: " + numOfCompars);

        numOfCompars = 0;

        Arrays.sort(arr2, (o1, o2)-> {
            numOfCompars++;
            return o1.compareTo(o2);
        });

//        for(Integer value: arr2){
//            System.out.print(value.intValue()+" ");
//        }
//        System.out.println();
        System.out.println("Number of comparisons in standard method: " + numOfCompars);
    }
}
