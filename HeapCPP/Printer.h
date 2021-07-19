#pragma once
#include "Heap.h"
#include <iostream>
#include <iomanip>

class Printer
{
public:
	template<class T>
	static void PrettyPrint(const Heap<T>& heap);
private:
	template<class T>
	static void PrintLine(const std::vector<T>& arr, size_t& index, size_t lenghtSum, int leftMargin, int maxLength, int nodesGap);
	
	static void PrintDrobs(int index, int lenghtSum, int leftDobsMargin, int drobsGag, int maxLength);
	
	template<class T>
	static int GetLength(const T& data);
	static int GetLength(int data);
};

template<class T>
void Printer::PrettyPrint(const Heap<T>& heap)
{
	std::cout << "\n";

	size_t index = 0;
	// длинна максимального элемента и условная единица отступа
	int maxLength = GetLength(heap[0]);

	maxLength = (maxLength * 2 + 1) / 2;

	// высота пирамиды
	int heapHeight = std::log2(heap.Size());

	// отступ слева
	int leftMargin = maxLength;

	for (size_t i = 1; i < heapHeight; i++)
	{
		leftMargin *= 2;
		leftMargin += maxLength;
	}
	// промежуток между узлами
	int nodesGap = 0;
	// сумма длин этажецей
	size_t lenghtSum = 1;

	int leftDobsMargin = 0, drobsGag = 0;

	int leftPadding = 0, rightPadding = 0;

	for (int line = 1; line <= heapHeight; line++) {

		PrintLine(heap.GetArr(), index, lenghtSum, leftMargin, maxLength, nodesGap);

		leftDobsMargin = leftMargin;
		nodesGap = leftMargin;
		leftMargin = (leftMargin + maxLength) / 2 - maxLength;

		leftDobsMargin += leftMargin;

		leftDobsMargin /= 2;

		lenghtSum += std::pow(2, line);

		leftMargin = (leftMargin <= 0) ? ((maxLength % 2 == 1) ? 1 : 0) : leftMargin;

		PrintDrobs(index, std::min(lenghtSum, heap.Size()), leftDobsMargin, leftMargin, maxLength);
	}

	PrintLine(heap.GetArr(), index, heap.Size(), 0, maxLength, maxLength);
}

template<class T>
void Printer::PrintLine(const std::vector<T>& arr, size_t& index, size_t lenghtSum, int leftMargin, int maxLength, int nodesGap)
{
	int leftPadding = 0, rightPadding = 0;
	leftPadding = (maxLength + GetLength(arr[index])) / 2;

	std::cout << std::setw(leftMargin + leftPadding);

	for (; index < lenghtSum - 1; index++)
	{
		leftPadding = (maxLength + GetLength(arr[index])) / 2;

		rightPadding = maxLength - leftPadding;

		leftPadding = (maxLength + GetLength(arr[index + 1])) / 2;

		std::cout << arr[index] << std::setw(nodesGap + rightPadding + leftPadding);
	}

	std::cout << arr[index++] << std::endl;
}

void Printer::PrintDrobs(int index, int lenghtSum, int leftDobsMargin, int drobsGag, int maxLength)
{

	int isMod2 = (maxLength % 2 == 0) ? 1 : 0;

	std::cout << std::setw(leftDobsMargin + (maxLength - 1) / 2 + 1);

	int nextDrobPair = 2 * leftDobsMargin + maxLength + maxLength - isMod2;

	drobsGag += (maxLength + isMod2);

	bool isLeftDrob = true;

	for (; index < lenghtSum; index++)
	{
		if (isLeftDrob)
		{
			std::cout << '/' << std::setw(drobsGag);
		}
		else
		{
			std::cout << '\\' << std::setw(nextDrobPair);
		}

		isLeftDrob = !isLeftDrob;
	}

	std::cout << std::endl;
}

template<class T>
int Printer::GetLength(const T& data)
{
	return 10;
}

int Printer::GetLength(int data)
{
	if (data == 0) return 1;

	int result = 0;

	while (data != 0) {
		data /= 10;
		result++;
	}

	return result;
}