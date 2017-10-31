package com.pyatkinmv;

import java.util.*;

public class QuickSort {

    static int numOfCompars = 0;

    static void quickSort(Integer[] arr, int first, int last, Comparator c) {
        if (first < last) {
            int p = partition(arr, first, last, c);
            quickSort(arr, first,p - 1, c);
            quickSort(arr, p, last, c);
        }
    }

    static int  partition(Integer[] arr, int first, int  last, Comparator c)  {
        Integer pivot = getPivot(arr, first, last, c);
        int i = first;
        int j = last;
        while (i <= j) {
            while (c.compare(arr[i], pivot) < 0) {
                i++;
            }
            while (c.compare(arr[j], pivot) > 0) {
                j--;
            }
            if (i <= j) {
                Integer temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }
        return i;
    }

    static Integer getPivot(Integer[] arr, int first, int last, Comparator c) {
        int middle;
        Integer x = arr[first];
        Integer y = arr[first + (last-first)/2];
        Integer z = arr[last];
        if(c.compare(x, z) < 0) {
            if (c.compare(y, x) < 0) {
                middle = x;
            }
            else if(c.compare(y, z) < 0) {
                middle = y;
            }
            else {
                middle = z;
            }
        }
        else {
            if(c.compare(y, x) > 0)
                middle = x;
            else if(c.compare(y, z) > 0) {
                middle = y;
            }
            else {
                middle = z;
            }
        }
        return middle;
    }

    static Integer getMiddlePivot(Integer[] arr, int first, int last) {
        return arr[first+(last-first)/2];
    }

    public static void main(String[] args) {
        Random rand = new Random();
        Integer[] arr1 = new Integer[100];
        for(int i=0;i<100;++i)
            arr1[i] = rand.nextInt(100);

        Integer[] arr2 = Arrays.copyOf(arr1,100);

        quickSort(arr1,0,99, (o1, o2)-> {
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
