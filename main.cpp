#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <chrono>
#include <cstdint>
#include <cstring>

using namespace std;
typedef double* DblPtr;

void generateInputFile(const char* filename, size_t size);
DblPtr fillArray(ifstream&, size_t & size);
void bubbleSort(double sortArr[], int size);
void InsertionSort(double arr[], int numbersSize);
void Merge(double arr[], int i, int j, int k);
void MergeSort(double arr[], int i, int k);
void SelectionSort(double arr[], int numbersSize);
int Partition(double arr[], int lowIndex, int highIndex);
void Quicksort(double arr[], int lowIndex, int highIndex);

int main(int argc, const char* argv[]) {
  int userInput;
  cout << "Type how much data you want to sort: ";
  cin >> userInput;
    generateInputFile("input.txt", userInput);

    if (argc != 2) {
        cout << "Invalid number of command line arguments. Usage:" << endl;
        cout << "Argument 1: input_filename" << endl;
        return -1;
    }

    ifstream inputFile;

    inputFile.open(argv[1]);

    if (inputFile.is_open() == false) {
        cout << "Unable to open input file \"" << argv[1] << '"' << endl;
        return -2;
    }

    time_t startTime, endTime;
    double seconds;
    size_t arrSize;
    DblPtr arr = fillArray(inputFile, arrSize);
    DblPtr copy = new double[arrSize];

    for (size_t size = 1000; size <= arrSize; size *= 10) {

        cout << "---------------------------------------------" << endl << endl;
        cout << "Array size: " << size << endl << endl;

        memcpy(copy, arr, size * sizeof(double));
        time(&startTime);
        cout << "MergeSort Start Time: " << startTime << " seconds since Jan 1, 1970" << endl;
        MergeSort(copy, 0, (int)size - 1);
        time(&endTime);
        cout << "MergeSort End Time: " << endTime << " seconds since Jan 1, 1970" << endl;
        seconds = difftime(endTime, startTime);
        cout << seconds << " seconds elapsed." << endl << endl;

        memcpy(copy, arr, size * sizeof(double));
        time(&startTime);
        cout << "Quicksort Start Time: " << startTime << " seconds since Jan 1, 1970" << endl;
        Quicksort(copy, 0, (int)size - 1);
        time(&endTime);
        cout << "Quicksort End Time: " << endTime << " seconds since Jan 1, 1970" << endl;
        seconds = difftime(endTime, startTime);
        cout << seconds << " seconds elapsed." << endl << endl;

        memcpy(copy, arr, size * sizeof(double));
        time(&startTime);
        cout << "SelectionSort Start Time: " << startTime << " seconds since Jan 1, 1970" << endl;
        SelectionSort(copy, (int)size);
        time(&endTime);
        cout << "SelectionSort End Time: " << endTime << " seconds since Jan 1, 1970" << endl;
        seconds = difftime(endTime, startTime);
        cout << seconds << " seconds elapsed." << endl << endl;

        memcpy(copy, arr, size * sizeof(double));
        time(&startTime);
        cout << "InsertionSort Start Time: " << startTime << " seconds since Jan 1, 1970" << endl;
        InsertionSort(copy, (int)size);
        time(&endTime);
        cout << "InsertionSort End Time: " << endTime << " seconds since Jan 1, 1970" << endl;
        seconds = difftime(endTime, startTime);
        cout << seconds << " seconds elapsed." << endl << endl;

        memcpy(copy, arr, size * sizeof(double));
        time(&startTime);
        cout << "bubbleSort Start Time: " << startTime << " seconds since Jan 1, 1970" << endl;
        bubbleSort(copy, (int)size);
        time(&endTime);
        cout << "bubbleSort End Time: " << endTime << " seconds since Jan 1, 1970" << endl;
        seconds = difftime(endTime, startTime);
        cout << seconds << " seconds elapsed." << endl << endl;

    }

    delete[] copy;
    copy = nullptr;
    delete[] arr;
    arr = nullptr;

    return 0;
}

void generateInputFile(const char* filename, size_t size)
{
    ofstream outputFile(filename);

    outputFile << size << endl;

    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(0.0, 100.0);

    outputFile << setprecision(10);
    for (size_t i = 0; i < size; i++) {
        outputFile << distribution(generator) << endl;
    }

}

DblPtr fillArray(ifstream& fin,  size_t& size)
{
    fin >> size;
    DblPtr arr = new double[size];
    for (size_t i = 0; i < size; ++i) {
        fin >> arr[i];
    }
    return arr;
}

void bubbleSort(double sortArr[], int size) {
    while (size-- > 1){
        double temp = 0.0;
        for (int j = 0; j < size; ++j) {
            if (sortArr[j] > sortArr[j + 1]) {
                temp = sortArr[j + 1];
                sortArr[j + 1] = sortArr[j];
                sortArr[j] = temp;
            }
        }
    }
}

void Merge(double arr[], int i, int j, int k) {
    int mergedSize = k - i + 1;                // Size of merged partition
    int mergePos = 0;                          // Position to insert merged number
    int leftPos = 0;                           // Position of elements in left partition
    int rightPos = 0;
    // Position of elements in right partition
    DblPtr mergedNumbers = new double[mergedSize];   // Dynamically allocates temporary array
                                          // for merged numbers

    leftPos = i;                           // Initialize left partition position
    rightPos = j + 1;                      // Initialize right partition position

    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= j && rightPos <= k) {
        if (arr[leftPos] <= arr[rightPos]) {
            mergedNumbers[mergePos] = arr[leftPos];
            ++leftPos;
        }
        else {
            mergedNumbers[mergePos] = arr[rightPos];
            ++rightPos;

        }
        ++mergePos;
    }

    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= j) {
        mergedNumbers[mergePos] = arr[leftPos];
        ++leftPos;
        ++mergePos;
    }

    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= k) {
        mergedNumbers[mergePos] = arr[rightPos];
        ++rightPos;
        ++mergePos;
    }

    // Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        arr[i + mergePos] = mergedNumbers[mergePos];
    }
}

void MergeSort(double arr[], int i, int k) {
    int j = 0;

    if (i < k) {
        j = (i + k) / 2;  // Find the midpoint in the partition

        // Recursively sort left and right partitions
        MergeSort(arr, i, j);
        MergeSort(arr, j + 1, k);

        // Merge left and right partition in sorted order
        Merge(arr, i, j, k);
    }
}

void SelectionSort(double arr[], int numbersSize) {
    int i = 0;
    int j = 0;
    int indexSmallest = 0;
    double temp = 0;  // Temporary variable for swap

    for (i = 0; i < numbersSize - 1; ++i) {
        // Find index of smallest remaining element
        indexSmallest = i;
        for (j = i + 1; j < numbersSize; ++j) {
            if (arr[j] < arr[indexSmallest]) {
                indexSmallest = j;
            }
        }

        // Swap numbers[i] and numbers[indexSmallest]
        if (indexSmallest != i) {
            temp = arr[i];
            arr[i] = arr[indexSmallest];
            arr[indexSmallest] = temp;
        }
    }
}

int Partition(double arr[], int lowIndex, int highIndex) {
    // Pick middle element as pivot
    int midpoint = lowIndex + (highIndex - lowIndex) / 2;
    double pivot = arr[midpoint];
    double temp = 0;
    bool done = false;
    while (!done) {
        // Increment lowIndex while numbers[lowIndex] < pivot
        while (arr[lowIndex] < pivot) {
            lowIndex += 1;
        }

        // Decrement highIndex while pivot < numbers[highIndex]
        while (pivot < arr[highIndex]) {
            highIndex -= 1;
        }

        // If zero or one elements remain, then all numbers are
        // partitioned. Return highIndex.
        if (lowIndex >= highIndex) {
            done = true;
        }
        else {
            // Swap numbers[lowIndex] and numbers[highIndex]
            temp = arr[lowIndex];
            arr[lowIndex] = arr[highIndex];
            arr[highIndex] = temp;

            // Update lowIndex and highIndex
            lowIndex += 1;
            highIndex -= 1;
        }
    }

    return highIndex;
}

void Quicksort(double arr[], int lowIndex, int highIndex) {
    // Base case: If the partition size is 1 or zero
    // elements, then the partition is already sorted
    if (lowIndex >= highIndex) {
        return;
    }

    // Partition the data within the array. Value lowEndIndex
    // returned from partitioning is the index of the low
    // partition's last element.
    int lowEndIndex = Partition(arr, lowIndex, highIndex);

    // Recursively sort low partition (lowIndex to lowEndIndex)
    // and high partition (lowEndIndex + 1 to highIndex)
    Quicksort(arr, lowIndex, lowEndIndex);
    Quicksort(arr, lowEndIndex + 1, highIndex);
}

void InsertionSort(double arr[], int numbersSize) {
    int i = 0;
    int j = 0;
    double temp = 0;  // Temporary variable for swap

    for (i = 1; i < numbersSize; ++i) {
        j = i;
        // Insert numbers[i] into sorted part
        // stopping once numbers[i] in correct position
        while (j > 0 && arr[j] < arr[j - 1]) {

            // Swap numbers[j] and numbers[j - 1]
            temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
            --j;
        }
    }
}
