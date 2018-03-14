// hugher8 - 15325303

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.c"

int linear_search(int* nums, int length, int n)
{ // returns the index of n in nums if present and -1 otherwise
  int i, thread_id;
  int location = -1; // shared variable to store location of n when found

  #pragma omp parallel default(none) private(i, thread_id) shared(nums, length, n, location)
  {
    thread_id = omp_get_thread_num();
    for (int i = thread_id; i < length; i += NUM_THREADS)
    {
      if (nums[i] == n)
      { // if n is found, assign the location to current index
        location = i;
        // printf("found %d at %d on thread %d\n", n, location, thread_id);
      }
      if (location != -1) { break; } // when one thread has an index > 0, stop the for loop on every thread
    }
  }

  return location;
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
  omp_set_num_threads(NUM_THREADS);

  for (int i = 0; i < SEARCH_SAMPLES; ++i)
  { // measure <SEARCH_SAMPLES> lookups in the btree, calculating the total time spent searching
    total_time += measured_random_contains(nums, SIZE);
  }

  // get the average time spent
  avg_time = total_time / SEARCH_SAMPLES;

  printf(
    "Took %.9lfs on average to find 1 of %d shuffled elements using %d threads.\n(%d samples, total time looking up: %.9lf)\n",
    avg_time,
    SIZE,
    NUM_THREADS,
    SEARCH_SAMPLES,
    total_time
  );
}
