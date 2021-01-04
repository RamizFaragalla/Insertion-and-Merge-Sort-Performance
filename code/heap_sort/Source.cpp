#include <iostream>
#include <vector>
#include <time.h> 
#include <cstdlib>
#include <chrono> 
using namespace std;
using namespace std::chrono;

void heapSort(int[], int);
void buildHeap(int[], int);
void heapify(int[], int, int);

void print(int[], int);
void swap(int &, int &);

int* makeSorted(int);				// input type 1
int* makeReverselySorted(int);		// input type 2
int getNum(vector<int>&);
int* makeRandomPermutation(int);	// input type 3
int* makeRandomNumbers(int);		// input type 4

int NUM_STEPS;	// global step counter for heap sort
int main() {
	srand(time(0));
	// array of array sizes
	int inputSize[] = { 100, 200, 300, 400, 500, 1000, 4000, 10000 };
	int* A;					// array used for heap sort
	double heapCSum = 0;	// C constant sum for heap sort

	// loop through every input size
	for (int i = 0; i < 8; i++) {
		int n = inputSize[i];
		cout << "***Input Size: " << n << "\n\nSorted input\n";

		// sorted input
		A = makeSorted(n);	// input for heap sort

		auto start = high_resolution_clock::now();
		heapSort(A, n);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Heap Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl << endl;
		heapCSum += static_cast<double>(NUM_STEPS) / (n * log10(n));

		delete[] A;

		// reverse input 
		A = makeReverselySorted(n);

		cout << "Reversely Sorted input\n";

		start = high_resolution_clock::now();
		heapSort(A, n);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Heap Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl << endl;
		heapCSum += static_cast<double>(NUM_STEPS) / (n * log10(n));

		delete[] A;

		// random permutation input 
		A = makeRandomPermutation(n);

		cout << "Random Permutation input\n";

		start = high_resolution_clock::now();
		heapSort(A, n);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Heap Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl << endl;
		heapCSum += static_cast<double>(NUM_STEPS) / (n * log10(n));

		delete[] A;

		// 50 inputs - random numbers [1, n] input 
		double totalHeapTime = 0;
		int totalHeapSteps = 0;
		cout << "50 inputs - Random numbers [1, n] input\n";

		for (int j = 0; j < 50; j++) {
			A = makeRandomNumbers(n);

			start = high_resolution_clock::now();
			heapSort(A, n);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);

			totalHeapTime += duration.count();
			totalHeapSteps += NUM_STEPS;

			delete[] A;
		}

		// output (average)
		cout << "Heap Sort (average): " << totalHeapTime / 50.0 << " microseconds";
		cout << " | " << totalHeapSteps / 50.0 << " steps" << endl;
		heapCSum += (totalHeapSteps / 50.0) / (n * log10(n));

		cout << "___________________________________________" << endl;
	}

	cout << "Average C for Heap Sort: " << heapCSum / 32 << endl;

	system("pause");
	return 0;
}

void heapSort(int A[], int n) {
	NUM_STEPS = 1;
	buildHeap(A, n);	// build the heap using array A
	// remove max from heap
	while (n >= 1) {
		swap(A[1], A[n]);	// swap left most leaf with root
		n--;				// decrement node count
		heapify(A, 1, n);	// heapify array starting at root

		NUM_STEPS += 4;
	}

	NUM_STEPS++;
}

void buildHeap(int A[], int n) {
	// start a left sub tree
	NUM_STEPS++;
	for (int i = n / 2; i >= 1; i--) {
		heapify(A, i, n);

		NUM_STEPS += 3;
	}

	NUM_STEPS++;
}

void heapify(int A[], int i, int n) {
	NUM_STEPS += 2;
	int child;
	if (2 * i <= n) {			// if left child exists
		NUM_STEPS += 2;
		child = 2 * i;	
		if (2 * i + 1 <= n) {	// if right child exits, pick child with the greater value
			child = A[2 * i] > A[2 * i + 1] ? 2 * i : 2 * i + 1;
			NUM_STEPS += 2;
		}

		NUM_STEPS++;
		if (A[i] < A[child]) {		// if parent is less than max child
			swap(A[i], A[child]);	// swap parent and max child
			heapify(A, child, n);	// heapify the subtree

			NUM_STEPS += 2;
		}
	}
}

// returns a sorted array [1, n]
int* makeSorted(int n) {
	int* A = new int[n+1];
	A[0] = 0;
	for (int i = 1; i <= n; i++) {
		A[i] = i;
	}

	return A;
}

// return a reversely sorted array [1, n]
int* makeReverselySorted(int n) {
	int* A = new int[n + 1];
	A[0] = 0;
	for (int i = 1; i <= n; i++) {
		A[i] = n - i + 1;
	}

	return A;
}

// returns a random permutation of [1, n] numbers
int* makeRandomPermutation(int n) {
	vector<int> v(n);
	// Fill the vector with the values 
	// 1, 2, 3, ..., n 
	for (int i = 0; i < n; i++)
		v[i] = i + 1;

	int* A = new int[n+1];
	A[0] = 0;
	int i = 1;
	while (v.size()) {
		A[i++] = getNum(v);
	}

	return A;
}

int getNum(vector<int>& v) {
	int n = v.size();

	// Make sure the number is within 
	// the index range 
	int index = rand() % n;

	// Get random number from the vector 
	int num = v[index];

	// Remove the number from the vector 
	swap(v[index], v[n - 1]);
	v.pop_back();

	// Return the removed number 
	return num;
}

// returns an array with n numbers, each cell is a random number [1, n]
int* makeRandomNumbers(int n) {
	int* A = new int[n+1];
	A[0] = 0;
	for (int i = 1; i <= n; i++) {
		int random = rand() % n + 1;	// random num [1, n]
		A[i] = random;
	}

	return A;
}

// prints the array (for testing)
void print(int A[], int n) {
	for (int i = 1; i <= n; i++)
		cout << A[i] << " ";

	cout << endl;
}

// swap using reference parameters
void swap(int & a, int & b) {
	NUM_STEPS += 3;

	int temp = a;
	a = b;
	b = temp;
}
