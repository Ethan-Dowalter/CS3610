/**
 *        @file: main.cpp
 *      @author: Ethan Dowalter
 *        @date: November 12, 2020
 *       @brief: Project 4 - External sorting algorithm
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;


struct Element{
	int value;
	int listID;
	int listRank;
	/// Overloaded comparison operators for priority queue
	/// If I'm remembering correctly, I'm pretty sure it only uses < operator, but I did both just to be safe
	bool operator < (const Element& other) const { return value < other.value; }
	bool operator > (const Element& other) const { return value > other.value; }
};


int partition(vector<int>& list, int first, int last) {
	int pivot;				//stores pivot value which sorting is based on
	int index;				//used to count sequentially through list indexes to compare each element with pivot value
	int smallIndex;			//divides list into elements smaller than pivot and elements larger than pivot
	int median;				//the median value of the first, middle, and last elements in list

	/// Find median value of first, middle, and last in list for pivot
	median = max(list.at(first), list.at((first + last) / 2));
	median = max(median, list.at(last));
	if (median == list.at(first))
	{
		median = max(list.at((first + last) / 2), list.at(last));
	}
	else if (median == list.at((first + last) / 2))
	{
		median = max(list.at(first), list.at(last));
	}
	else
	{
		median = max(list.at(first), list.at((first + last) / 2));
	}

	/// Make sure pivot value is first in list
	if (median == list.at((first + last) / 2))
	{
		swap(list.at(first), list.at((first + last) / 2));
	}
	else if (median == list.at(last))
	{
		swap(list.at(first), list.at(last));
	}
	pivot = list.at(first);
	smallIndex = first;

	/// Sort list based on pivot value
	for (index = first + 1; index <= last; index++)
	{
		if (list.at(index) < pivot)
		{
			smallIndex++;
			swap(list.at(smallIndex), list.at(index));
		}
	}
	
	/// Settle the pivot
	swap(list.at(first), list.at(smallIndex));

	return smallIndex;
}

void quicksort(vector<int>& list, int first, int last) {
	if (first >= last)			//small size
	{			
		return;
	}
	else
	{
		int j = partition(list, first, last);		//partition into two sublists
		quicksort(list, first, j - 1);
		quicksort(list, j + 1, last);
	}
}

void multiway_merge(vector<vector<int>>& input_lists, vector<int>& output_list) {
	vector<vector<Element>> input_lists_withIDs;			//used to convert the input list to a struct which contains a listID

	/// Convert input list to a list of structs that have listIDs and listRanks along with the values
	for (size_t i = 0; i < input_lists.size(); i++)
	{
		input_lists_withIDs.push_back(vector<Element>());
		for (size_t j = 0; j < input_lists[i].size(); j++)
		{
			Element temp;
			temp.value = input_lists[i][j];
			temp.listID = i;
			temp.listRank = j;
			input_lists_withIDs[i].push_back(temp);
		}
	}
	
	/// Merge the minimum from each list into a min heap and pop the top into output_list
	priority_queue<Element, vector<Element>, greater<Element>> minHeap;
	for (size_t i = 0; i < input_lists_withIDs.size(); i++)
	{
		minHeap.push(input_lists_withIDs[i][0]);				//populates min heap with initial values from each sublist
	}
	for (size_t i = 0; minHeap.size() > 0; i++)
	{
		output_list.at(i) = (minHeap.top().value);				//put the top of the min heap into output_list
		int temp = input_lists_withIDs[0].size() - 1;			//had to use a temp int here to avoid warning of const int compared with unsigned int
		if (minHeap.top().listRank < temp)						//only look for the successor in the sublist if it exists
		{
			minHeap.push(input_lists_withIDs[minHeap.top().listID][minHeap.top().listRank + 1]);
		}
		minHeap.pop();											//pop the top so the next smallest element moves up
	}	
} 

int main(int argc, char** argv) {
	int n, m;
	cin >> n >> m;

	vector<vector<int> > input_lists(n, vector<int>(m));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> input_lists[i][j];
		}
	}

	// Quicksort k sublists
	for (size_t i = 0; i < input_lists.size(); ++i)
		quicksort(input_lists[i], 0, m-1);

	// Merge n input sublists into one sorted list
	vector<int> output_list(n * m);
	multiway_merge(input_lists, output_list);

	for (size_t i = 0; i < output_list.size(); ++i)
		cout << output_list[i] << " ";
	cout << endl;

	return 0;
}
