#pragma once
#include <vector>

using std::vector;

template<class T>
class Heap
{
public:
	void Push(const T& data);
	T Top() const;
	T Pop();
	bool Empty() const { return _arr.size() == 0; }
	size_t Size() const { return _arr.size(); }

	const vector<T>& GetArr() const { return _arr; }
	const T& operator [] (size_t) const;

private:
	bool IsResonForIteration(size_t i, size_t child) const;
	inline size_t FindPerentIndex(size_t index) const { return (index - 1) / 2; }
	vector<T> _arr;
};

template<class T>
const T& Heap<T>::operator[](size_t index) const
{
	return _arr[index];
}

template<class T>
bool Heap<T>::IsResonForIteration(size_t i, size_t child) const
{ 
	return (child < _arr.size()) and (_arr[child] > _arr[i]);
}

template<class T>
void Heap<T>::Push(const T& data)
{
	size_t i = _arr.size();
	
	size_t perent_i = FindPerentIndex(i);

	_arr.push_back(data);

	while (i != 0 and _arr[i] > _arr[perent_i])
	{
		std::swap(_arr[i], _arr[perent_i]);

		i = perent_i;

		perent_i = FindPerentIndex(i);
	}
}

template<class T>
T Heap<T>::Top() const
{
	return _arr.size() ? _arr[0] : throw std::exception("Empty Heap");
}

template<class T>
T Heap<T>::Pop()
{
	if (_arr.size())
	{
		T res = _arr[0];

		_arr[0] = _arr.back();

		_arr.pop_back();

		size_t i = 0;

		size_t left_i = 1, right_i = 2;

		while (IsResonForIteration(i, left_i) or IsResonForIteration(i, right_i))
		{
			if ((right_i >= _arr.size()) or (_arr[left_i] >= _arr[right_i]))
			{
				std::swap(_arr[i], _arr[left_i]);

				i = left_i;
			}
			else
			{
				std::swap(_arr[i], _arr[right_i]);

				i = right_i;
			}

			left_i = 2 * i + 1;

			right_i = left_i + 1;
		}

		return res;
	}

	throw std::exception("Empty Heap");
}