#include <iostream>
#include <vector>
#include <time.h> 
#include <cstdlib>
#include <chrono> 
using namespace std;
using namespace std::chrono;

void quickSort(int[], int, int, bool);
int partition(int[], int, int, bool);

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
	srand(time(0));

	// array of array sizes
	int inputSize[] = { 100, 200, 300, 400, 500, 1000, 4000, 10000 };
	int* A;	// array used for quick sort
	int* B;	// array used for randomized quick sort

	// loop through every input size
	for (int i = 0; i < 8; i++) {
		int n = inputSize[i];
		cout << "***Input Size: " << n << "\n\nSorted input\n";

		// sorted input
		A = makeSorted(n);	// input for quick sort
		B = makeSorted(n);	// input for randomized quick sort

		NUM_STEPS = 0;
		auto start = high_resolution_clock::now();
		quickSort(A, 0, n-1, false);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Quick Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl;

		NUM_STEPS = 0;
		start = high_resolution_clock::now();
		quickSort(B, 0, n-1, true);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Randomized Quick Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl << endl;

		delete[] A;
		delete[] B;

		// reverse input 
		A = makeReverselySorted(n);	// input for quick sort
		B = makeReverselySorted(n);	// input for randomized quick sort

		cout << "Reversely Sorted input\n";

		NUM_STEPS = 0;
		start = high_resolution_clock::now();
		quickSort(A, 0, n-1, false);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Quick Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl;

		NUM_STEPS = 0;
		start = high_resolution_clock::now();
		quickSort(B, 0, n-1, true);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Randomized Quick Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl << endl;

		delete[] A;
		delete[] B;

		// random permutation input 
		A = makeRandomPermutation(n);	// input for quick sort
		B = copy(A, n);					// input for randomized quick sort

		cout << "Random Permutation input\n";

		NUM_STEPS = 0;
		start = high_resolution_clock::now();
		quickSort(A, 0, n-1, false);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Quick Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl;

		NUM_STEPS = 0;
		start = high_resolution_clock::now();
		quickSort(B, 0, n-1, true);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);

		// output
		cout << "Randomized Quick Sort: " << duration.count() << " microseconds";
		cout << " | " << NUM_STEPS << " steps" << endl << endl;

		delete[] A;
		delete[] B;

		// 50 inputs - random numbers [1, n] input 
		double totalQuickTime = 0;
		double totalRandomizedQuickTime = 0;

		int totalQuickSteps = 0, totalRandomizedQuickSteps = 0;
		cout << "50 inputs - Random numbers [1, n] input\n";

		for (int j = 0; j < 50; j++) {
			A = makeRandomNumbers(n);	// input for quick sort
			B = copy(A, n);				// input for randomized quick sort

			NUM_STEPS = 0;
			start = high_resolution_clock::now();
			quickSort(A, 0, n-1, false);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);

			totalQuickTime += duration.count();
			totalQuickSteps += NUM_STEPS;

			NUM_STEPS = 0;
			start = high_resolution_clock::now();
			quickSort(B, 0, n-1, true);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);

			totalRandomizedQuickTime += duration.count();
			totalRandomizedQuickSteps += NUM_STEPS;

			delete[] A;
			delete[] B;
		}

		// output (average)
		cout << "Quick Sort (average): " << totalQuickTime / 50.0 << " microseconds";
		cout << " | " << totalQuickSteps / 50.0 << " steps" << endl;

		// output (average)
		cout << "Randomized Quick Sort (average): " << totalRandomizedQuickTime / 50.0 << " microseconds";
		cout << " | " << totalRandomizedQuickSteps / 50.0 << " steps" << endl << endl;
		cout << "___________________________________________" << endl;
	}

	system("pause");
	return 0;
}

// used this iterative version to prevent stack overflow
// stack overflow happened at input 10,000
void quickSort(int A[], int l, int r, bool randomized) {
	NUM_STEPS += 1;
	if (l < r) {
		int pivot = partition(A, l, r, randomized);
		quickSort(A, l, pivot - 1, randomized);
		quickSort(A, pivot + 1, r, randomized);

		NUM_STEPS += 3;
	}
}

int partition(int A[], int l, int r, bool randomized) {
	if (randomized) {
		int randomIndex = rand() % (r - l + 1) + l;
		swap(A[randomIndex], A[r]);

		NUM_STEPS += 2;
	}

	int pivot = A[r];
	int i = l - 1;
	int j;

	NUM_STEPS += 4;

	for (j = l; j < r; j++) {
		if (A[j] < pivot) {
			i++;
			swap(A[j], A[i]);

			NUM_STEPS += 2;
		}

		NUM_STEPS += 3;
	}
	NUM_STEPS += 3;

	swap(A[i + 1], A[j]);
	return i + 1;
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

// swap using reference parameters
void swap(int & a, int & b) {
	int temp = a;
	a = b;
	b = temp;

	NUM_STEPS += 3;
}