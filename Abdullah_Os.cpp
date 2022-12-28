#include <iostream>
#include <pthread.h>
#include <time.h>
#define size 20 // Number of elements in array 
#define thread_size 2 // Number of threads according to my pc's core 
using namespace std;


int Array[size];
int temp = 0;

//
void merge_array(int first, int mid_val, int end)
{
   int* start = new int[mid_val - first + 1];
   int* last = new int[end - mid_val];
   int temp_1 = mid_val - first + 1;
   int temp_2 = end - mid_val;
   int i, j;
   int k = first;
   for(i = 0; i < temp_1; i++)
   {
      start[i] = Array[i + first];
   }
   for (i = 0; i < temp_2; i++)
   {
      last[i] = Array[i + mid_val + 1];
   }
   i = j = 0;
   while(i < temp_1 && j < temp_2)
   {
      if(start[i] <= last[j])
	  {
         Array[k++] = start[i++];
      }
      else
	  {
         Array[k++] = last[j++];
      }
   }
   while (i < temp_1)
   {
      Array[k++] = start[i++];
   }
   while (j < temp_2)
   {
      Array[k++] = last[j++];
   }
}

// MERGE FUNCTION 
void Merge_Sort(int first, int end)
{
   int mid_val = first + (end - first) / 2;
   if(first < end)
   {
      Merge_Sort(first, mid_val);
      Merge_Sort(mid_val + 1, end);
      merge_array(first, mid_val, end);
   }
}

// MERGE AND SORT FUNCTION 
void* Merge_Sort(void* arg)
{
   int set_val = temp++;
   int first = set_val * (size / 4);
   int end = (set_val + 1) * (size / 4) - 1;
   int mid_val = first + (end - first) / 2;
   if (first < end)
   {
      Merge_Sort(first, mid_val);
      Merge_Sort(mid_val + 1, end);
      merge_array(first, mid_val, end);
   }
}

// MAIN FUNCTION 
int main()
{
   for(int i = 0; i < size; i++)
   {
      Array[i] = rand() % 100;
   }
   pthread_t P_TH[thread_size];
   for(int i = 0; i < thread_size; i++)
   {
      pthread_create(&P_TH[i], NULL, Merge_Sort, (void*)NULL);
   }
   for(int i = 0; i < 4; i++)
   {
      pthread_join(P_TH[i], NULL);
   }
   merge_array(0, (size / 2 - 1) / 2, size / 2 - 1);
   merge_array(size / 2, size/2 + (size-1-size/2)/2, size - 1);
   merge_array(0, (size - 1)/2, size - 1);
   
   cout<<"Sorted Array by Multi Threading is: ";
   for (int i = 0; i < size; i++)
   {
      cout << Array[i] << " ";
   }
   return 0;
}
