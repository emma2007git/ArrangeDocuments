#include <stdio.h>
#include "quickSort.h"
#include "keywordList.h"

void Swap(Keyword arr[], int idx1, int idx2)
{
	Keyword temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}

int Partition(Keyword arr[], int left, int right)
{
	int pivot = arr[left].frequency;
	int low = left + 1;
	int high = right;

	while (low <= high)
	{
		while (pivot <= arr[low].frequency)
			low++;

		while (pivot > arr[high].frequency)
			high--;

		if (low <= high)
			Swap(arr, low, high);
	}
	Swap(arr, left, high);
	return high;
}

void QuickSort(Keyword arr[], int left, int right)
{
	if (left <= right)
	{
		int pivot = Partition(arr, left, right);
		QuickSort(arr, left, pivot - 1);
		QuickSort(arr, pivot + 1, right);
	}
}