#pragma once
#include "RectangleDrawing.h"

#include <vector>

#define wxBROWSER_COLOR wxColour(100, 200, 255) // blue-ish color of the "browser", which is usually the current rectangle accessed by the sorting algorithm
#define SORT_DELAY 10 // in milliseconds

class RectangleSorter
{
public:
	static int comparisons;
	static int arrayAccesses;

private:
	static void Merge(std::vector<RectangleDrawing*> rectangles, int start, int mid, int end);
	static int Partition(std::vector<RectangleDrawing*> rectangles, int start, int end);

public:
	static void BubbleSort(std::vector<RectangleDrawing*> rectangles);
	static void SelectionSort(std::vector<RectangleDrawing*> rectangles);
	static void InsertionSort(std::vector<RectangleDrawing*> rectangles);
	static void MergeSortRecursive(std::vector<RectangleDrawing*> rectangles, int start, int end);
	static void MergeSortIterative(std::vector<RectangleDrawing*> rectangles);
	static void QuickSort(std::vector<RectangleDrawing*> rectangles, int start, int end);
	static void PigeonholeSort(std::vector<RectangleDrawing*>& rectangles);
};

