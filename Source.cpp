#include <iostream>
#include <vector>
#include <time.h> 
#include <cstdlib>
#include <chrono> 
using namespace std;
using namespace std::chrono;

void insertionSort(int[], int);

void mergeSort(int[], int);
void mergeHelper(int[], int[], int, int);
void mergeHalves(int[], int[], int, int);

void print(int[], int);
void swap(int &, int &);

int* makeSorted(int);				// input type 1
int* makeReverselySorted(int);		// input type 2
int getNum(vector<int>&);
int* makeRandomPermutation(int);	// input type 3
int* makeRandomNumbers(int);		// input type 4

int* copy(int*, int);

int NUM_STEPS;	// global step counter for both algorithms
int main() {
	// array of array sizes
	int inputSize[] = { 100, 200, 300, 400, 500, 1000, 4000, 10000 };
	int* A;	// array used for insertion sort
	int* B;	// array used for merge sort
	double insertionCSum = 0;	// C constant sum for insertion sort
	double mergeCSum = 0;		// C constant sum for merge sort

	// loop through every input size
	for (int i = 0; i < 8; i++) {
		int n = inputSize[i];
		cout << "***Input Size: " << n << "\n\nSorted input\n";

		// sorted input
		A = makeSorted(n);	// input for insertion
		B = makeSorted(n);	// input for merge

		auto start = high_resolution_clock::now();
		insertionSort(A, n);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Insertion Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl;
		/*insertionCSum += static_cast<double>(NUM_STEPS) / (n * n);*/

		start = high_resolution_clock::now();
		mergeSort(B, n);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Merge Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl << endl;
		mergeCSum += static_cast<double>(NUM_STEPS) / (n * log10(n));

		delete[] A;
		delete[] B;

		// reverse input 
		A = makeReverselySorted(n);	// input for insertion
		B = makeReverselySorted(n);	// input for merge

		cout << "Reversely Sorted input\n";

		start = high_resolution_clock::now();
		insertionSort(A, n);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Insertion Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl;
		insertionCSum += static_cast<double>(NUM_STEPS) / (n * n);

		start = high_resolution_clock::now();
		mergeSort(B, n);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Merge Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl << endl;
		mergeCSum += static_cast<double>(NUM_STEPS) / (n * log10(n));

		delete[] A;
		delete[] B;

		// random permutation input 
		A = makeRandomPermutation(n);	// input for insertion
		B = copy(A, n);					// input for merge

		cout << "Random Permutation input\n";

		start = high_resolution_clock::now();
		insertionSort(A, n);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Insertion Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl;
		insertionCSum += static_cast<double>(NUM_STEPS) / (n * n);

		start = high_resolution_clock::now();
		mergeSort(B, n);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Merge Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl << endl;
		mergeCSum += static_cast<double>(NUM_STEPS) / (n * log10(n));

		delete[] A;
		delete[] B;

		// 50 inputs - random numbers [1, n] input 
		double totalInsertionTime = 0;
		double totalMergeTime = 0;

		int totalInsertionSteps = 0, totalMergeSteps = 0;
		cout << "50 inputs - Random numbers [1, n] input\n";

		for (int j = 0; j < 50; j++) {
			A = makeRandomNumbers(n);	// input for insertion
			B = copy(A, n);				// input for merge

			start = high_resolution_clock::now();
			insertionSort(A, n);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);

			totalInsertionTime += duration.count();
			totalInsertionSteps += NUM_STEPS;

			start = high_resolution_clock::now();
			mergeSort(B, n);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);

			totalMergeTime += duration.count();
			totalMergeSteps += NUM_STEPS;

			delete[] A;
			delete[] B;
		}

		// output (average)
		cout << "Insertion Sort (average): " << totalInsertionTime / 50.0 << " microseconds";
		cout << " | " << totalInsertionSteps / 50.0 << " steps" << endl;
		insertionCSum += (totalInsertionSteps / 50.0) / (n * n);

		// output (average)
		cout << "Merge Sort (average): " << totalMergeTime / 50.0 << " microseconds";
		cout << " | " << totalMergeSteps / 50.0 << " steps" << endl << endl;
		mergeCSum += (totalMergeSteps / 50.0) / (n * log10(n));
		cout << "___________________________________________" << endl;
	}

	cout << "Average C for insertion: " << insertionCSum / 24 << endl;
	cout << "Average C for merge: " << mergeCSum / 32 << endl;

	system("pause");
	return 0;
}

// returns a sorted array [1, n]
int* makeSorted(int n) {
	int* A = new int[n];
	for (int i = 0; i < n; i++) {
		A[i] = i + 1;
	}

	return A;
}

// return a reversely sorted array [1, n]
int* makeReverselySorted(int n) {
	int* A = new int[n];
	for (int i = 0; i < n; i++) {
		A[i] = n - i;
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

	int* A = new int[n];
	int i = 0;
	while (v.size()) {
		A[i++] = getNum(v);
	}


	return A;
}

int getNum(vector<int>& v) {
	int n = v.size();

	// Generate a random number 
	srand(time(0));

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
	srand(time(0));
	int* A = new int[n];

	for (int i = 0; i < n; i++) {
		int random = rand() % n + 1;	// random num [1, n]
		A[i] = random;
	}

	return A;
}

// copies the array passed as a parameter and returns it
int* copy(int* A, int n) {
	int* B = new int[n];
	for (int i = 0; i < n; i++) {
		B[i] = A[i];
	}

	return B;
}

// prints the array (for testing)
void print(int A[], int n) {
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";

	cout << endl;
}

void insertionSort(int A[], int n) {
	NUM_STEPS = 1;	// step counter
	for (int i = 1; i < n; i++) {
		int key = A[i];
		int j = i - 1;
		NUM_STEPS += 4;

		while (j >= 0 && key < A[j]) {
			A[j + 1] = A[j];
			j--;
			NUM_STEPS += 4;
		}

		A[j + 1] = key;
		NUM_STEPS += 2;
	}
	NUM_STEPS++;
}

// swap using reference parameters
void swap(int & a, int & b) {
	int temp = a;
	a = b;
	b = temp;
}

void mergeSort(int A[], int n) {
	NUM_STEPS = 1;	// step counter
	int* temp = new int[n];	// temp array to merge halves

	NUM_STEPS++;
	mergeHelper(A, temp, 0, n - 1);

	NUM_STEPS++;
	delete[] temp;
}

void mergeHelper(int A[], int temp[], int begin, int end) {
	NUM_STEPS++;
	if (begin < end) {
		int mid = (begin + end) / 2;		// midpoint
		NUM_STEPS++;

		NUM_STEPS++;
		mergeHelper(A, temp, begin, mid);	// left side

		NUM_STEPS++;
		mergeHelper(A, temp, mid + 1, end);	// right side

		NUM_STEPS++;
		mergeHalves(A, temp, begin, end);	// merge both sides
	}
}

void mergeHalves(int A[], int temp[], int begin, int end) {
	int mid = (begin + end) / 2;
	int l = begin, r = mid + 1, i = 0;
	NUM_STEPS += 4;

	while (l <= mid && r <= end) {
		NUM_STEPS += 6;
		if (A[l] <= A[r])
			temp[i++] = A[l++];

		else
			temp[i++] = A[r++];
	}
	NUM_STEPS++;

	while (l <= mid) {		// copy remaining values
		NUM_STEPS += 4;
		temp[i++] = A[l++];
	}
	NUM_STEPS++;

	while (r <= end) {		// copy remaining values
		NUM_STEPS += 4;
		temp[i++] = A[r++];
	}
	NUM_STEPS++;

	int a = begin, b = 0;
	NUM_STEPS += 2;
	while (a <= end) {		// copy values from temp back to A
		NUM_STEPS += 4;
		A[a++] = temp[b++];
	}
	NUM_STEPS++;
}