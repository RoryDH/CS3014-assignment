// hugher8 - 15325303

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_THREADS             1
#define SIZE              1000000 // SIZE of the arrays to search and sort
#define MAX_RAND        100000000 // max random number to generate
#define SEARCH_SAMPLES        100 // how many times to lookup and measure duration

// int random_int(void) // generates a random number in the range 1-max
// {
//   return (rand() % MAX_RAND) + 1;
// }

int is_sorted(int* nums, int length)
{
  for (int i = 1; i < length; ++i)
  {
    if (nums[i] < nums[i - 1])
    {
      return 0;
    }
  }
  return 1;
}

// rejection sampling method adapted from http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)Randomization.html#Issues_with_RAND_MAX
int random_int(int max)
{
  int limit, rnd;
  limit = MAX_RAND - (MAX_RAND % max);
  while ((rnd = rand()) >= limit);
  return rnd % max;
}

// fisher yates shuffle https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
void shuffle_ints(int *nums, int length)
{
  int i, j, tmp;
  for (i = length - 1; i > 0; i--) {
    j = random_int(i + 1);
    tmp = nums[j];
    nums[j] = nums[i];
    nums[i] = tmp;
  }
}

void print_nums(int* nums, int length) {
  for (int i = 0; i < length; ++i)
  {
    printf("%d ", nums[i]);
  }
  printf("\n");
}

int* shuffled_array(int length)
{ // alocates and returns a pointer to an array of indices shuffled randomly
  int* nums = malloc(length * sizeof(int));
  for (int i = 0; i < length; i++)
  {
    nums[i] = i;
  }
  // print_nums(nums, length);
  shuffle_ints(nums, length);
  // print_nums(nums, length);
  return nums;
}


// previously used random num array with non-unique elements
// int* shuffled_array(int length)
// {
//   int* arr = malloc(length * sizeof(int));
//   for (int i = 0; i < length; i++)
//   {
//     arr[i] = random_int(MAX_RAND);
//   }
//   return arr;
// }


int main(int argc, char const *argv[])
{
  // shuffled_array(5);
  // shuffled_array(10);
  // shuffled_array(50);

  for (int i = 0; i < 10; ++i)
  {
    printf("%d ", random_int(10));
  }
  return 0;
}
