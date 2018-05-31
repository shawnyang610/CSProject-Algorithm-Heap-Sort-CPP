// CSCI700-34 Proj.4 Heap Sort (C++)
// Prof. Tsaiyun Phillips
// Student: Shawn Yang

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class HeapSort {
public:
	int rootIndex;
	int fatherIndex;
	int kidIndex;
	int leftKidIndex;
	int rightKidIndex;
	int minIndex;
	int arraySize;
	int *heapAry;
	int inData;
	int temp;
	ifstream inFile;
	ofstream outFile1;
	ofstream outFile2;


	HeapSort(int numElement, string nameInFile, string nameOutFile1, string nameOutFile2) {
		inFile.open(nameInFile.c_str());
		outFile1.open(nameOutFile1.c_str());
		outFile2.open(nameOutFile2.c_str());
		arraySize = numElement++;
		heapAry = new int[arraySize];
		heapAry[0] = 0;
	}

	void buildHeap() {
		rootIndex = 1;
		while (inFile >> inData) {
			insertOneDataItem(inData);
			kidIndex = heapAry[0];
			bubbleUp(kidIndex);
			printHeap();
		}
		inFile.close();
	};

	void deleteHeap() {
		while (!isHeapEmpty()) {
			deleteRoot();
			fatherIndex = 1;
			bubbleDown(fatherIndex);
			printHeap();
		}
		outFile1.close();
		outFile2.close();
	}

	void insertOneDataItem(int inData) {
		heapAry[0]++;
		heapAry[heapAry[0]] = inData;
	}
	int getRoot() {
		return heapAry[1];
	}
	void deleteRoot() {
		outFile2 << heapAry[1] << " ";
		heapAry[1] = heapAry[heapAry[0]];
		heapAry[0]--;
	}
	void bubbleUp(int kidIndex) {
		if (isRoot(kidIndex)) {
			return;
		} else {
			fatherIndex = kidIndex / 2;
			int temp;
			if (heapAry[kidIndex]<heapAry[fatherIndex]) {
				temp = heapAry[kidIndex];
				heapAry[kidIndex] = heapAry[fatherIndex];
				heapAry[fatherIndex] = temp;
			}
			bubbleUp(fatherIndex);
		}
	}
	void bubbleDown(int inFatherIndex) {
		if (isLeaf(inFatherIndex)) {
			return;
		} else {
			leftKidIndex = inFatherIndex * 2;
			rightKidIndex = inFatherIndex * 2 + 1;
			if (rightKidIndex>heapAry[0]) {
				minIndex = leftKidIndex;
			} else {
				minIndex = findMinKidIndex(leftKidIndex, rightKidIndex);
			}
			if (heapAry[minIndex]<heapAry[inFatherIndex]) {
				temp = heapAry[inFatherIndex];
				heapAry[inFatherIndex] = heapAry[minIndex];
				heapAry[minIndex] = temp;
				bubbleDown(minIndex);
			}
		}
	}
	bool isLeaf(int index) {
		return (index * 2 > heapAry[0]);
	};
	bool isRoot(int index) {
		return (index == 1);
	}
	int findMinKidIndex(int inLeftKidIndex, int inRightKidIndex) {
		if (heapAry[inLeftKidIndex] > heapAry[inRightKidIndex]) {
			return inRightKidIndex;
		} else
			return inLeftKidIndex;
	}
	bool isHeapEmpty() {
		return (heapAry[0] == 0);
	}
	bool isHeapFull() {
		return (heapAry[0] == arraySize);
	}
	void printHeap() {
		if (heapAry[0] == 0) {} else {
			outFile1 << "heapAry:";
			for (int i = 0; i < heapAry[0] + 1; i++) {
				outFile1 << " " << heapAry[i];
			}
			outFile1 << endl;
		}
	}
};


int main(int argc, char *argv[]) {
	//initialise vars.
	ifstream inFile;
	ofstream outFile1;
	ofstream outFile2;
	int dataCount = 0;
	int temp;
	HeapSort* heapSort;

	try {
		if (argc < 3) {
			//cout <<"Please provide the following 3 arguments: input.txt output.txt log.txt" << endl;
			cout << argc;
			return 0;
		}
		cout << argv[1] << argv[2] << argv[3];
		inFile.open(argv[1]);
		outFile1.open(argv[2]);
		outFile2.open(argv[3]);
		while (inFile >> temp) {
			dataCount++;
		}
		cout << "total data count is:" << dataCount << endl;
		inFile.close();
		outFile1.close();
		outFile2.close();

	} catch (const std::exception&) {}

	heapSort = new HeapSort(dataCount, argv[1], argv[2], argv[3]);
	(*heapSort).buildHeap();
	(*heapSort).deleteHeap();
	return 0;
}