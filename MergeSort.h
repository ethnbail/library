#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include "Book.h"

using namespace std;

void merge(vector<Book>& books, int left, int mid, int right);
void mergeSort(vector<Book>& books, int left, int right);

#endif
