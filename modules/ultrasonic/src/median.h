#ifndef _MEDIAN_H_
#define _MEDIAN_H_

#include <stdlib.h>

int partition(int *a, int p, int r);
int random_partition(int *a, int p, int r);
int random_select(int *a, int p, int r, int i);

int median(int *a, int l) {
  return random_select(a, 0, l, (l + 1) / 2);
}

int partition(int *a, int p, int r) {
  int x = a[r], t;
  int i = p - 1, j;
  for (j = p; j < r; j++) {
    if (a[j] <= x) {
      i++;
      t = a[i];
      a[i] = a[j];
      a[j] = t;
    }
  }
  t = a[i + 1];
  a[i + 1] = a[r];
  a[r] = t;
  return i + 1;
}

int random_partition(int *a, int p, int r) {
  int i = p + (int)((r - p + 1) * rand() / (RAND_MAX + 1.0));
  int t = a[i];
  a[i] = a[r];
  a[r] = t;
  return partition(a, p, r);
}

int random_select(int *a, int p, int r, int i) {
  if (p == r) {
    return a[p];
  }
  int q = random_partition(a, p, r);
  int k = q - p + 1;
  if (i == k) {
    return a[q];
  }
  else if (i < k) {
    return random_select(a, p, q - 1, i);
  }
  else {
    return random_select(a, q + 1, r, i - k);
  }
}

#endif // _MEDIAN_H_