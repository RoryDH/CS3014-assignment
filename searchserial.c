// hugher8 - 15325303

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.c"

int linear_search(int* nums, int length, int n)
{ // returns the index of n in nums if present and -1 otherwise
  for (int i = 0; i < length; ++i)
  {
    if (nums[i] == n)
    {
      return i;
    }
  }
  return -1;
}

double measured_random_contains(int* nums, int length)
{ // measures and returns the duration of a single lookup of a random number up to max
  double start_time, end_time;
  int num_to_find = random_int(length); // choose a random int to find in the array

  start_time = omp_get_wtime();
  linear_search(nums, length, num_to_find);
  end_time = omp_get_wtime();

  return end_time - start_time;
}

int main(void)
{
  srand(time(NULL));
  int i;
  int* nums = shuffled_array(SIZE); // random numbers to insert
  double total_time = 0, avg_time;

  for (int i = 0; i < SEARCH_SAMPLES; ++i)
  { // measure <SEARCH_SAMPLES> lookups in the btree, calculating the total time spent searching
    total_time += measured_random_contains(nums, SIZE);
  }

  // get the average time spent
  avg_time = total_time / SEARCH_SAMPLES;

  printf(
    "Took %.9lfs on average to find 1 of %d shuffled elements.\n(%d samples, total time looking up: %.9lf)\n",
    avg_time,
    SIZE,
    SEARCH_SAMPLES,
    total_time
  );
}
