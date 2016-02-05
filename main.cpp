
//#include "stdafx.h"
//Nick Townsend. CSC 330 Final Project - Data Structures.
//This program is menu-driven, it reads text files of random numbers and puts them in order
//Using the different sorting algorithms, then searches for a number using binary search or sequential search. 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <assert.h>
using namespace std;
int *entry;      // array name for dynamic array
int array_size;  // for array size
int counter = 0;

class List {
public:  // sort declarations
	void bubble_sort();
	void insertion_sort();
	void selection_sort();
	void shell_sort();
	void shiftright(int[], int, int);
	void heapify(int[], int, int);
	void heap_sort(int[], int);
	void sequential_search(int[], int, int);
	void binary_search(int[], int, int, int);
	void quick_sort(int[], int, int);
	void read_data();
	void print_data();		
};

void List::bubble_sort()
{
	int counter = 0;
	for (int pass = 0; pass < array_size - 1; pass++)
	for (int i = 0; i < array_size - 1; i++)
	{
		counter++;
		if (entry[i] > entry[i + 1])
		{
			int temp = entry[i];              // swap
			entry[i] = entry[i + 1];
			entry[i + 1] = temp;
		}
	}
	cout << "Bubble_Sort: Total number of comparisons = " << counter << endl;
}

void List::insertion_sort()
{
	int counter = 0;
	int j;
	int temp;
	for (int i = 1; i < array_size; i++)
	if (entry[i] < entry[i - 1])
	{
		counter++;
		j = i;
		temp = entry[i];
		do
		{
			entry[j] = entry[j - 1];
			j--;
			counter++;
		} while (j > 0 && entry[j - 1] > temp);
		entry[j] = temp;		
	}
		cout << "Insertion_Sort: Total number of comparisons = " << counter << endl;
}

void List::selection_sort()
{
	int counter = 0;
	int pos_min, temp;
	for (int i = 0; i < array_size - 1; i++)
	{
		counter++;
		pos_min = i;
		for (int j = i + 1; j < array_size; j++)
		{
			if (entry[j] < entry[pos_min])
				pos_min = j;
			counter++;
		}
		if (pos_min != i)
		{
			temp = entry[i];
			entry[i] = entry[pos_min];
			entry[pos_min] = temp;
			counter++;
		}
	}
	cout << "Selection_Sort: Total number of comparisons = " << counter << endl;

}

void List::shell_sort()
{
	int counter = 0;
	int i, j, increment, temp;
	for (increment = array_size / 2; increment > 0; increment /= 2)
	{
		for (i = increment; i < array_size; i++)
		{
			temp = entry[i];
			counter++;

			for (j = i; j >= increment; j -= increment)
			{
				if (temp < entry[j - increment])
				{
					entry[j] = entry[j - increment];
					counter++;
				}
				else
				{
					break;
				}
			}
			entry[j] = temp;			
		}
	}
	cout << "Shell_Sort: Total number of comparisons = " << counter << endl;
}

void quick_sort(int entry[], int left, int right)
{	
	{
		int i = left, j = right;
		int temp;
		int pivot = entry[(left + right) / 2];

		while (i <= j)
		{
			counter++;
			while (entry[i] < pivot)
				i++;
			    counter++;
			while (entry[j] > pivot)
				j--;
			    counter++;
			if (i <= j)
			{
				temp = entry[i];
				entry[i] = entry[j];
				entry[j] = temp;
				i++;
				j--;
				counter++;
			}
		}
		if (left < j)
			quick_sort(entry, left, j);
			counter++;
		if (i < right)
			quick_sort(entry, i, right);
			counter++;
	}	
}

void shiftright(int entry[], int low, int high)
{
	int root = low;
	while ((root * 2) + 1 <= high)
	{
		int leftchild = (root * 2) + 1;
		int rightchild = leftchild + 1;
		int swapIdx = root;
		if (entry[swapIdx] < entry[leftchild])
		{
			counter++;
			swapIdx = leftchild;
		}
		if ((rightchild <= high) && (entry[swapIdx] < entry[rightchild]))
		{
			counter++;
			swapIdx = rightchild;
		}
		if (swapIdx != root)
		{
			counter++;
			int tmp = entry[root];
			entry[root] = entry[swapIdx];
			entry[swapIdx] = tmp;
			root = swapIdx;
		}
		else
		{
			break;
		}
	}
	return;
}

void heapify(int entry[], int low, int high)
{
	int midIdx = (high - low - 1) / 2;
	while (midIdx >= 0)
	{
		counter++;
		shiftright(entry, midIdx, high);
		--midIdx;
	}
	return;
}

void heap_sort(int entry[], int array_size)
{
	assert(entry);
	assert(array_size > 0);
	heapify(entry, 0, array_size - 1);
	int high = array_size - 1;
	while (high > 0)
	{
		counter++;
		int tmp = entry[high];
		entry[high] = entry[0];
		entry[0] = tmp;
		--high;
		shiftright(entry, 0, high);
	}
	return;
}
	
void sequential_search(int entry[], int array_size, int value)
{
	int index = 0, comparison = 0;
	
	bool found = false;

	while (index < array_size && !found)
	{
		comparison++;
		if (entry[index] == value)
		{
			found = true;
		}
		index++;
	}

	if (found)
	{
		cout << "The sequential search found the number after " << comparison << " comparisons.\n";
	}
	else
	{
		cout << value << "  not found in this array." << endl;
		cout << "The sequential search made " << comparison << " comparisons." << endl << endl;
	}
}

void binary_search(int entry[], int first, int array_size, int value)
{
	int comparison = 1,
		position = 0;

	position = (first + array_size) / 2;

	while ((entry[position] != value) && (first <= array_size))
	{
		comparison++;
		if (entry[position] > value)
		{
			array_size = position - 1;
		}
		else
		{
			first = position + 1;
		}
		position = (first + array_size) / 2;
	}
	if (first <= array_size)
	{
		cout << "The binary search found the number after " << comparison << " comparisons.\n";
	}
	else
		cout << value << " not found in this array!  The binary search made " << comparison << " comparisons.";
	cout << endl << endl;
}
void List::read_data()
{
	int i;
	char filename[30];
	ifstream fin;
	cout << "Start by selecting a file and an amount of data to input\n";
	cout << "Enter the name of input file => ";
	cin >> filename;
	cout << "Enter the size of input data => ";
	cin >> array_size;
	entry = new int[array_size];        // create a dynamic array 
	fin.open(filename, ios::in);   // for "filename" input file
	if (fin.fail())	  // if "filename" doesn't exist, open fails
	{
		cout << "\nOpening file was not successful => <Enter> to Exit.";
		cin.get(); cin.get();
		exit(1);
	}
	for (i = 0; i < array_size; i++)    // read in data from a file
		fin >> entry[i];
	cout << "\nUnsorted data:\n\n";
	for (i = 1; i <= array_size; i++)    // print the unsorted array
	{
		cout << setw(7) << entry[i - 1];
		if (i % 10 == 0) cout << endl;
	}
	cout << endl;
	fin.close();
}


void List::print_data()
{
	ofstream fout;
	fout.open("out.txt", ios::out);   // for output file
	cout << "\n<ENTER> to see sorted array ... \n";
	cin.get(); cin.get();
	cout << "\nSorted data:\n";
	for (int i = 1; i <= array_size; i++)     // print the sorted array
	{
		cout << setw(7) << entry[i - 1];
		if (i % 10 == 0) cout << endl;
		fout << setw(7) << entry[i - 1];
		if (i % 10 == 0) fout << endl;
	}
	fout.close();  // close file
}


void main()
{
	int value;
	char g;
	List x;  // declare object x
	cout << "Welcome to the sorting program.\n";
	x.read_data();   // to read data from a file and store them to array entry[]
	_sleep(1000);	 // pausing for aesthetics sake
	cout << "Do you want to sort the list?\n"; 
	cout << "<y,n>?\n";
	cin >> g;
	while (g == 'y')  // Starting the menu
	{	
		char g;
			cout << "Press a key to choose a type of sorting:\n";  // Listing all choices
			cout << "1: Bubble Sort\n";
			cout << "2: Insertion Sort\n";
			cout << "3: Selection Sort\n";
			cout << "4: Shell Sort\n";
			cout << "5: Quick Sort\n";
			cout << "6: Heap Sort\n";
			cout << "Q: to exit program\n";
			cin >> g ;
			if (g == '1')  // bubble
			{
				char s;
				x.bubble_sort();
				x.print_data();
				cout << "             \n";
				cout << "Would you like to search the data for a specific number?\n";
				cout << "<y,n>?\n";
				cin >> s;
				if (s == 'y' || s == 'Y')
				{
					char ss;
					cout << "How would you like to search the data?\n";
					cout << "1: Sequential Search\n";
					cout << "2: Binary Search\n";
					cin >> ss;
					if (ss == '1')
					{
						cout << "Enter a number you wish to search for: ";
						cin >> value;
						cout << endl;
						cout << "For sequential search: \n";
						sequential_search(entry, array_size, value);
					}
					else if (ss == '2')
					{
						cout << "Enter a number you wish to search for: ";
						cin >> value;
						cout << "\n";
						cout << "For binary search: \n";
						binary_search(entry, 0, array_size, value);
					}
					else
					{
						cout << "Invalid Entry\n";
						cout << "Exiting program.\n";
						_sleep(2000);
						exit(0);
					}
				}
				else
				{
					cout << "You don't want to search.\n";
					cout << "Exiting program...\n";
					_sleep(2000);
					exit(0);
				}
				
			}
			else if (g == '2')  //insertion
			{	
				char s;
				x.insertion_sort();
				x.print_data();
				cout << "             \n";
				cout << "Would you like to search the data for a specific number?\n";
				cout << "<y,n>?\n";
				cin >> s;
				if (s == 'y' || s == 'Y')
				{
					char ss;
					cout << "How would you like to search the data?\n";
					cout << "1: Sequential Search\n";
					cout << "2: Binary Search\n";
					cin >> ss;
					if (ss == '1')
					{
						cout << "Enter a number you wish to search for: ";
						cin >> value;
						cout << endl;
						cout << "For sequential search: \n";
						sequential_search(entry, array_size, value);
					}
					else if (ss == '2')
					{
						cout << "Enter a number you wish to search for: ";
						cin >> value;
						cout << "\n";
						cout << "For binary search: \n";
						binary_search(entry, 0, array_size, value);
					}
					else
					{
						cout << "Invalid Entry\n";
						cout << "Exiting program.\n";
						_sleep(2000);
						exit(0);
					}
				}
				else
				{	
					cout << "You don't want to search.\n";
					cout << "Exiting program...\n";
					_sleep(2000);
					exit(0);
				}
			}
			else if (g == '3')  //selection
			{
				char s;
				x.selection_sort();
				x.print_data();
				cout << "             \n";
				cout << "Would you like to search the data for a specific number?\n";
				cout << "<y,n>?\n";
				cin >> s;
				if (s == 'y' || s == 'Y')
				{
					char ss;
					cout << "How would you like to search the data?\n";
					cout << "1: Sequential Search\n";
					cout << "2: Binary Search\n";
					cin >> ss;
					if (ss == '1')
					{
						cout << "Enter a number you wish to search for: ";
						cin >> value;
						cout << endl;
						cout << "For sequential search: \n";
						sequential_search(entry, array_size, value);
					}
					else if (ss == '2')
					{
						cout << "Enter a number you wish to search for: ";
						cin >> value;
						cout << "\n";
						cout << "For binary search: \n";
						binary_search(entry, 0, array_size, value);
					}
					else
					{
						cout << "Invalid Entry\n";
						cout << "Exiting program.\n";
						_sleep(2000);
						exit(0);
					}
				}
				else
				{
					cout << "You don't want to search.\n";
					cout << "Exiting program...\n";
					_sleep(2000);
					exit(0);
				}
			} 
			else if (g == '4')  //shell
			{
				char s;
				x.shell_sort();
				x.print_data();
				cout << "             \n";
				cout << "Would you like to search the data for a specific number?\n";
				cout << "<y,n>?\n";
				cin >> s;
				if (s == 'y' || s == 'Y')
				{
					char ss;
					cout << "How would you like to search the data?\n";
					cout << "1: Sequential Search\n";
					cout << "2: Binary Search\n";
					cin >> ss;
					if (ss == '1')
					{
						cout << "Enter a number you wish to search for: ";
						cin >> value;
						cout << endl;
						cout << "For sequential search: \n";
						sequential_search(entry, array_size, value);
					}
					else if (ss == '2')
					{
						cout << "Enter a number you wish to search for: ";
						cin >> value;
						cout << "\n";
						cout << "For binary search: \n";
						binary_search(entry, 0, array_size, value);
					}
					else
					{
						cout << "Invalid Entry\n";
						cout << "Exiting program.\n";
						_sleep(2000);
						exit(0);
					}
				}
				else
				{
					cout << "You don't want to search.\n";
					cout << "Exiting program...\n";
					_sleep(2000);
					exit(0);
				}
			}
			else if (g == '5')  //quick
			{
				char s;
				quick_sort(entry, 0, array_size);
				cout << "quick_sort: Total number of comparisons = " << counter << endl;
				x.print_data();
				cout << "             \n";
				cout << "Would you like to search the data for a specific number?\n";
				cout << "<y,n>?\n";
				cin >> s;
				if (s == 'y' || s == 'Y')
				{
					char ss;
					cout << "How would you like to search the data?\n";
					cout << "1: Sequential Search\n";
					cout << "2: Binary Search\n";
					cin >> ss;
					if (ss == '1')
					{
						cout << "Enter a number you wish to search for: ";
						cin >> value;
						cout << endl;
						cout << "For sequential search: \n";
						sequential_search(entry, array_size, value);
					}
					else if (ss == '2')
					{
						cout << "Enter a number you wish to search for: ";
						cin >> value;
						cout << "\n";
						cout << "For binary search: \n";
						binary_search(entry, 0, array_size, value);
					}
					else
					{
						cout << "Invalid Entry\n";
						cout << "Exiting program.\n";
						_sleep(2000);
						exit(0);
					}
				}
				else
				{
					cout << "You don't want to search.\n";
					cout << "Exiting program...\n";
					_sleep(2000);
					exit(0);
				}
			}
			else if (g == '6')  //heap
			{
				char s;
				shiftright(entry, 0, array_size);
				heapify(entry, 0, array_size);
				heap_sort(entry, array_size);	
				cout << "heap_sort: Total number of comparisons = " << counter << endl;
				x.print_data();
				cout << "             \n";
				cout << "Would you like to search the data for a specific number?\n";
				cout << "<y,n>?\n";
				cin >> s;
				if (s == 'y' || s == 'Y')
				{
					char ss;
					cout << "How would you like to search the data?\n";
					cout << "1: Sequential Search\n";
					cout << "2: Binary Search\n";
					cin >> ss;
					if (ss == '1')
					{
						cout << "Enter a number you wish to search for: ";
						cin >> value;
						cout << endl;
						cout << "For sequential search: \n";
						sequential_search(entry, array_size, value);
					}
					else if (ss == '2')
					{
						cout << "Enter a number you wish to search for: ";
						cin >> value;
						cout << "\n";
						cout << "For binary search: \n";
						binary_search(entry, 0, array_size, value);
					}
					else
					{
						cout << "Invalid Entry\n";
						cout << "Exiting program.\n";
						_sleep(2000);
						exit(0);
					}
				}
				else
				{
					cout << "You don't want to search.\n";
					cout << "Exiting program...\n";
					_sleep(2000);
					exit(0);
				}
			}
			else if (g == 'q' || g == 'Q')
			{
				cout << "exiting program";
				_sleep(1000);
				exit(0);
			}
			else
			{
				cout << "Invalid input\n";
				cout << "Exiting program...\n";
				_sleep(3000);
				exit(0);
			}
			
	}
	cout << "You don't want to sort.\n";
	cout << "Exiting program...\n";
	_sleep(2000);
	exit(0);
}
