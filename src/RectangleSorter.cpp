#include "RectangleSorter.h"

int RectangleSorter::comparisons;
int RectangleSorter::arrayAccesses;

void RectangleSorter::Merge(std::vector<RectangleDrawing*> rectangles, int start, int mid, int end)
{
	wxColour lastColor;

	RectangleDrawing* leftRects = new RectangleDrawing[mid - start + 1];
	RectangleDrawing* rightRects = new RectangleDrawing[end - mid];

	int k{ start };
	int i{ 0 };
	int j{ 0 };

	for (i; i < mid - start + 1; ++i, ++k)
	{
		++comparisons;
		arrayAccesses += 2;
		leftRects[i] = *rectangles[k];
	}

	for (j; j < end - mid; ++j, ++k)
	{
		++comparisons;
		arrayAccesses += 2;
		rightRects[j] = *rectangles[k];
	}

	k = start;
	i = 0;
	j = 0;

	while (i < mid - start + 1 && j < end - mid)
	{
		comparisons += 2;
		arrayAccesses += 4;
		if (leftRects[i].height < rightRects[j].height)
		{
			*rectangles[k] = leftRects[i];
			lastColor = rectangles[start + i]->color;
			rectangles[start + i]->Recolor(wxBROWSER_COLOR);
			wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
			wxMilliSleep(SORT_DELAY);
			rectangles[start + i]->Recolor(lastColor);
			rectangles[k]->Redraw(leftRects[i].position, leftRects[i].size, leftRects[i].height, leftRects[i].color);

			++i;
		}
		else
		{
			*rectangles[k] = rightRects[j];
			lastColor = rectangles[mid + 1 + j]->color;
			rectangles[mid + 1 + j]->Recolor(wxBROWSER_COLOR);
			wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
			wxMilliSleep(SORT_DELAY);
			rectangles[mid + 1 + j]->Recolor(lastColor);
			rectangles[k]->Redraw(rightRects[j].position, rightRects[j].size, rightRects[j].height, rightRects[j].color);

			++j;
		}
		++k;
	}

	while (i < mid - start + 1)
	{
		++comparisons;
		arrayAccesses += 2;
		*rectangles[k] = leftRects[i];
		rectangles[k]->Recolor(wxBROWSER_COLOR);
		wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
		wxMilliSleep(SORT_DELAY);
		rectangles[k]->Redraw(leftRects[i].position, leftRects[i].size, leftRects[i].height, leftRects[i].color);
		++i;
		++k;
	}
	while (j < end - mid)
	{
		++comparisons;
		arrayAccesses += 2;
		*rectangles[k] = rightRects[j];
		rectangles[k]->Recolor(wxBROWSER_COLOR);
		wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
		wxMilliSleep(SORT_DELAY);
		rectangles[k]->Redraw(rightRects[j].position, rightRects[j].size, rightRects[j].height, rightRects[j].color);
		++j;
		++k;
	}

	wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
	delete[] leftRects;
	delete[] rightRects;
}

int RectangleSorter::Partition(std::vector<RectangleDrawing*> rectangles, int start, int end)
{
	int l{ start };

	wxColour lastColor;
	wxColour currentColor;
	RectangleDrawing rectTemp;

	lastColor = rectangles[end]->color;
	rectangles[end]->Recolor(wxBROWSER_COLOR);
	wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible

	for (int u{ start }; u < end; ++u)
	{
		currentColor = rectangles[u]->color;
		rectangles[u]->Recolor(wxBROWSER_COLOR);
		wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
		wxMilliSleep(SORT_DELAY);

		++comparisons;
		arrayAccesses += 2;
		if (rectangles[u]->height < rectangles[end]->height)
		{

			rectTemp = *rectangles[l];
			rectangles[l]->Redraw(rectangles[u]->position, rectangles[u]->size, rectangles[u]->height, currentColor);
			rectangles[u]->Redraw(rectTemp.position, rectTemp.size, rectTemp.height, rectTemp.color);
			if (l != u)
				currentColor = rectangles[u]->color;
			arrayAccesses += 4;
			wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible

			++l;
		}

		rectangles[u]->Recolor(currentColor);
		wxYield();
	}

	rectTemp = *rectangles[l];
	rectangles[l]->Redraw(rectangles[end]->position, rectangles[end]->size, rectangles[end]->height, lastColor);
	if (l != end)
		rectangles[end]->Redraw(rectTemp.position, rectTemp.size, rectTemp.height, rectTemp.color);
	arrayAccesses += 4;
	wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible

	return l;
}

void RectangleSorter::BubbleSort(std::vector<RectangleDrawing*> rectangles)
{
	wxLogStatus(""); // clears the status bar
	comparisons = 0;
	arrayAccesses = 0;

	wxColour lastColor;
	RectangleDrawing tempRect;

	for (int i{ 1 }; i < rectangles.size(); ++i)
	{
		lastColor = rectangles[0]->color;
		rectangles[0]->Recolor(wxBROWSER_COLOR);
		wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
		for (int j{ 0 }; j < rectangles.size() - i; ++j)
		{
			++comparisons;
			arrayAccesses += 2;
			if (rectangles[j]->height > rectangles[j + 1]->height)
			{
				tempRect = *rectangles[j];
				rectangles[j]->Redraw(rectangles[j + 1]->position, rectangles[j + 1]->size, rectangles[j + 1]->height, rectangles[j + 1]->color);
				rectangles[j + 1]->Redraw(tempRect.position, tempRect.size, tempRect.height, wxBROWSER_COLOR);
				arrayAccesses += 4;
				wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
			}
			else
			{
				rectangles[j]->Recolor(lastColor);
				lastColor = rectangles[j + 1]->color;
				rectangles[j + 1]->Recolor(wxBROWSER_COLOR);
				wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
			}
			wxMilliSleep(SORT_DELAY);
		}
		rectangles[rectangles.size() - i]->Recolor(lastColor);
		wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
	}

	wxString comparisonsWXString = wxString::Format(wxT("%i"), comparisons);
	wxString arrayAccessesWXString = wxString::Format(wxT("%i"), arrayAccesses);
	wxString sortDelayWXString = wxString::Format(wxT("%i"), SORT_DELAY);
	wxLogStatus("Bubble Sort - " + comparisonsWXString + " comparisons, " + arrayAccessesWXString + " array accesses, " + sortDelayWXString + " ms delay");
}

void RectangleSorter::SelectionSort(std::vector<RectangleDrawing*> rectangles)
{
	wxLogStatus(""); // clears the status bar
	comparisons = 0;
	arrayAccesses = 0;

	int smallest;
	wxColour lastColor;
	wxColour currentColor;
	RectangleDrawing rectTemp;

	for (int i{ 0 }; i < rectangles.size(); ++i)
	{
		smallest = i;
		lastColor = rectangles[smallest]->color;
		rectangles[smallest]->Recolor(wxBROWSER_COLOR);
		wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible

		for (int j{ i + 1 }; j < rectangles.size(); ++j)
		{
			++comparisons;
			arrayAccesses += 2;
			if (rectangles[j]->height < rectangles[smallest]->height)
			{
				rectangles[smallest]->Recolor(lastColor);

				smallest = j;

				lastColor = rectangles[smallest]->color;
				rectangles[smallest]->Recolor(wxBROWSER_COLOR);
				wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
				wxMilliSleep(SORT_DELAY);
			}
			else
			{
				currentColor = rectangles[j]->color;
				rectangles[j]->Recolor(wxBROWSER_COLOR);
				wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
				wxMilliSleep(SORT_DELAY);
				rectangles[j]->Recolor(currentColor);
			}
		}

		rectTemp = *rectangles[smallest];
		rectangles[smallest]->Redraw(rectangles[i]->position, rectangles[i]->size, rectangles[i]->height,  rectangles[i]->color);
		rectangles[i]->Redraw(rectTemp.position, rectTemp.size, rectTemp.height, lastColor);
		arrayAccesses += 4;
		wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
	}

	wxString comparisonsWXString = wxString::Format(wxT("%i"), comparisons);
	wxString arrayAccessesWXString = wxString::Format(wxT("%i"), arrayAccesses);
	wxString sortDelayWXString = wxString::Format(wxT("%i"), SORT_DELAY);
	wxLogStatus("Selection Sort - " + comparisonsWXString + " comparisons, " + arrayAccessesWXString + " array accesses, " + sortDelayWXString + " ms delay");
}

void RectangleSorter::InsertionSort(std::vector<RectangleDrawing*> rectangles)
{
	wxLogStatus(""); // clears the status bar
	comparisons = 0;
	arrayAccesses = 0;

	int key;
	int j;
	wxColour lastColor;
	wxColour currentColor;
	RectangleDrawing rectTemp;

	for (int i{ 1 }; i < rectangles.size(); ++i)
	{
		++arrayAccesses;
		key = rectangles[i]->height;
		rectTemp = *rectangles[i];

		j = i;

		++arrayAccesses;
		while (j > 0 && key < rectangles[j - 1]->height)
		{
			currentColor = rectangles[j - 1]->color;
			rectangles[j]->Redraw(rectangles[j - 1]->position, rectangles[j - 1]->size, rectangles[j - 1]->height, currentColor);
			wxYield();
			rectangles[j - 1]->Recolor(wxBROWSER_COLOR);
			++comparisons;
			arrayAccesses += 2;
			wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
			--j;

			wxMilliSleep(SORT_DELAY);
		}

		rectangles[j]->height = key;
		rectangles[j]->Redraw(rectTemp.position, rectTemp.size, rectTemp.height, rectTemp.color);
		++arrayAccesses;
		wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
	}

	wxString comparisonsWXString = wxString::Format(wxT("%i"), comparisons);
	wxString arrayAccessesWXString = wxString::Format(wxT("%i"), arrayAccesses);
	wxString sortDelayWXString = wxString::Format(wxT("%i"), SORT_DELAY);
	wxLogStatus("Insertion Sort - " + comparisonsWXString + " comparisons, " + arrayAccessesWXString + " array accesses, " + sortDelayWXString + " ms delay");
}

void RectangleSorter::MergeSortRecursive(std::vector<RectangleDrawing*> rectangles, int start, int end)
{
	if (start >= end)
		return;

	int mid = (start + end) / 2;

	MergeSortRecursive(rectangles, start, mid);
	MergeSortRecursive(rectangles, mid + 1, end);

	Merge(rectangles, start, mid, end);
}

void RectangleSorter::MergeSortIterative(std::vector<RectangleDrawing*> rectangles)
{
	wxLogStatus(""); // clears the status bar
	comparisons = 0;
	arrayAccesses = 0;

	wxColour lastColor;

	for (int currSize{ 1 }; currSize < rectangles.size() - 1; currSize *= 2)
	{
		for (int start{ 0 }; start < rectangles.size() - 1; start += currSize * 2)
		{
			int mid = std::min(start + currSize - 1, (int)rectangles.size() - 1);
			int end = std::min(start + (currSize * 2) - 1, (int)rectangles.size() - 1);

			Merge(rectangles, start, mid, end);
		}
	}

	wxString comparisonsWXString = wxString::Format(wxT("%i"), comparisons);
	wxString arrayAccessesWXString = wxString::Format(wxT("%i"), arrayAccesses);
	wxString sortDelayWXString = wxString::Format(wxT("%i"), SORT_DELAY);
	wxLogStatus("Merge Sort (Iterative) - " + comparisonsWXString + " comparisons, " + arrayAccessesWXString + " array accesses, " + sortDelayWXString + " ms delay");
}

void RectangleSorter::QuickSort(std::vector<RectangleDrawing*> rectangles, int start, int end)
{
	if (start >= end)
		return;

	int pivot = Partition(rectangles, start, end);

	QuickSort(rectangles, start, pivot - 1);
	QuickSort(rectangles, pivot + 1, end);
}

void RectangleSorter::PigeonholeSort(std::vector<RectangleDrawing*>& rectangles)
{
	wxLogStatus(""); // clears the status bar
	comparisons = 0;
	arrayAccesses = 0;

	int min = rectangles[0]->height;
	int	max = rectangles[0]->height;

	wxColour lastColor;

	for (int i{ 1 }; i < rectangles.size(); i++)
	{
		comparisons += 2;
		arrayAccesses += 3;
		if (rectangles[i]->height < min)
			min = rectangles[i]->height;
		if (rectangles[i]->height > max)
			max = rectangles[i]->height;

		lastColor = rectangles[i]->color;
		rectangles[i]->Recolor(wxBROWSER_COLOR);
		wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
		wxMilliSleep(SORT_DELAY);
		rectangles[i]->Recolor(lastColor);
		wxYield(); // clears/updates the DC buffer, without this, changes in rectangle's color, height or position would not be visible
	}
	int range = max - min + 1;


	std::vector<RectangleDrawing*>* pigeonholes = new std::vector<RectangleDrawing*>[range];

	for (int i{ 0 }; i < rectangles.size(); ++i)
	{
		arrayAccesses += 2;
		pigeonholes[rectangles[i]->height - min].push_back(rectangles[i]);
	}

	int index = 0;
	for (int i{ 0 }; i < range; ++i)
	{
		++arrayAccesses;
		for (int j{ 0 }; j < pigeonholes[i].size(); ++j)
		{
			arrayAccesses += 3;
			rectangles[index] = new RectangleDrawing((wxPanel*)rectangles[index]->GetParent(), rectangles[index]->position, pigeonholes[i][j]->height, pigeonholes[i][j]->color);
			index++;

			wxMilliSleep(SORT_DELAY);
		}
	}

	wxString comparisonsWXString = wxString::Format(wxT("%i"), comparisons);
	wxString arrayAccessesWXString = wxString::Format(wxT("%i"), arrayAccesses);
	wxString sortDelayWXString = wxString::Format(wxT("%i"), SORT_DELAY);
	wxLogStatus("Pigeonhole Sort - " + comparisonsWXString + " comparisons, " + arrayAccessesWXString + " array accesses, " + sortDelayWXString + " ms delay");
}

