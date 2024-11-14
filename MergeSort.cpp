#include "MergeSort.h"
#include <algorithm> // For the swap function

void merge(vector<Book>& books, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Book> leftBooks(n1);
    vector<Book> rightBooks(n2);

    for (int i = 0; i < n1; ++i)
        leftBooks[i] = books[left + i];

    for (int i = 0; i < n2; ++i)
        rightBooks[i] = books[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftBooks[i].title < rightBooks[j].title) {
            books[k] = leftBooks[i];
            ++i;
        } else {
            books[k] = rightBooks[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        books[k] = leftBooks[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        books[k] = rightBooks[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<Book>& books, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(books, left, mid);
        mergeSort(books, mid + 1, right);

        merge(books, left, mid, right);
    }
}
