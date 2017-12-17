#pragma once
// Higher-Order Divide and Conquer

template <typename T1, typename T2>
T2 divideAndConquer(bool (*trivial)(T1), T2 (*solve)(T1), std::pair<T1, T1> (*divide)(T1), T2 (*combine)(T2, T2), T1 input)
{
	if (trivial(input))
		return solve(input);
	else
	{
		std::pair<T1, T1> division = divide(input);
		return combine( divideAndConquer(trivial, solve, divide, combine, std::get<0>(division)), divideAndConquer(trivial, solve, divide, combine, std::get<1>(division)));
	}
}

#pragma region QUICKSORT
// quicksort functions
template <typename T>
bool qs_trivial_checkIdentical(std::vector<T> x, T val)
{
	if (x.front() != val)
		return false;
	else if (x.size() <= 1)
		return true;
	else
	{
		return qs_trivial_checkIdentical(std::vector<T>(x.begin() + 1, x.end()), val);
	}
}

template <typename T>
bool qs_trivial(std::vector<T> x)
{
	if (x.size() <= 1)
		return true;
	else
		return qs_trivial_checkIdentical(x, x.front());

}

template <typename T>
std::vector<T> qs_solve(std::vector<T> x) {	return x; }

template <typename T>
std::pair<std::vector<T>, std::vector<T>> qs_recursiveSplit(std::vector<T> left, std::vector<T> right, std::vector<T> pivotVals, T pivot, std::vector<T> x)
{
	if (x.front() < pivot)
		left.push_back(x.front());
	else if (x.front() > pivot)
		right.push_back(x.front());
	else
		pivotVals.push_back(x.front());

	if (x.size() > 1)
	{
		return qs_recursiveSplit(left, right, pivotVals, pivot, std::vector<T>(x.begin() + 1, x.end()));
	}
	else
	{
		right.insert(right.begin(), pivotVals.begin(), pivotVals.end());
		return std::make_pair(left, right);
	}

}

template <typename T>
std::pair<std::vector<int>, std::vector<T>> qs_divide(std::vector<T> x)
{
	T pivot = x.back();
	return qs_recursiveSplit(std::vector<T>(), std::vector<T>(), std::vector<T>(), pivot, x);
}

template <typename T>
std::vector<int> qs_combine(std::vector<T> x, std::vector<T> y)
{
	x.insert(x.end(), y.begin(), y.end());
	return x;
}
#pragma endregion

