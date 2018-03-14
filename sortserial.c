// hugher8 - 15325303

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.c"

// https://en.wikipedia.org/wiki/Quicksort#Hoare_partition_scheme
int partition(int *nums, int lo, int hi)
{
  int tmp, pivot_value = nums[lo], i = lo - 1, j = hi + 1;
  while (1) { // forever until return
    do { i++; } while(nums[i] < pivot_value); // find element larger on left
    do { j--; } while(nums[j] > pivot_value); // find element lower on right
    if (i >= j) { return j; } // quit when correctly split
    tmp = nums[i]; // swap otherwise
    nums[i] = nums[j];
    nums[j] = tmp;
  }
}

void quicksort(int *nums, int lo, int hi)
{
  int pivot_index;
  if(lo < hi)
  {
    pivot_index = partition(nums, lo, hi); // choose pivot (lo) and partition smaller and larger elements
    quicksort(nums, lo, pivot_index);      // sort to the left of pivot
    quicksort(nums, pivot_index + 1, hi);  // sort to the right of pivot
  }
}

int main(void)
{
  srand(time(NULL));
  double start_time, end_time;
  int* nums = shuffled_array(SIZE);

  start_time = omp_get_wtime();
  quicksort(nums, 0, SIZE - 1);
  end_time = omp_get_wtime();

  printf(
    "Took %f seconds to %s sort %d random elements.\n",
    end_time - start_time,
    is_sorted(nums, SIZE) ? "correctly" : "INCORRECTLY",
    SIZE
  );
}
