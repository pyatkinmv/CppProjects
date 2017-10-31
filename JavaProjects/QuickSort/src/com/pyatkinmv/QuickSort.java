package com.pyatkinmv;

import java.util.Comparator;

public class QuickSort <T> {

    void sort(T[] arr, int first, int last, Comparator c) {
            if (first < last) {
                int p = partition(arr, first, last, c);
                sort(arr, first, p - 1, c);
                sort(arr, p, last, c);
            }
        }

    int partition(T[] arr, int first, int last, Comparator c) {
        T pivot = getPivot(arr, first, last, c);
        int i = first;
        int j = last;
        while (i <= j) {
            while (c.compare(arr[i], pivot) < 0)
                i++;
            while (c.compare(arr[j], pivot) > 0)
                j--;
            if (i <= j) {
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }
        return i;
    }
    T getPivot(T[] arr, int first, int last, Comparator c) {
        T middle;
        T x = arr[first];
        T y = arr[first + (last - first) / 2];
        T z = arr[last];
        if (c.compare(x, z) < 0) {
            if (c.compare(x, y) > 0) {
                middle = x;
            } else if (c.compare(y, z) < 0) {
                middle = y;
            } else {
                middle = z;
            }
        } else {
            if (c.compare(x, y) < 0)
                middle = x;
            else if (c.compare(y, z) > 0) {
                middle = y;
            } else {
                middle = z;
            }
        }
        return middle;
    }

        T getMiddlePivot(T[] arr, int first, int last) {
            return arr[first + (last - first) / 2];
        }
}
