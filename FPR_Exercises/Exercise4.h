#pragma once
// Higher-Order Divide and Conquer

template <typename T1, typename T2>
T2 divideAndConquer(
	std::function<bool(T1)> trivial, 
	std::function<T2(T1)> solve, 
	std::function<std::pair<T1, T1>(T1)> divide, 
	std::function<T2(T2, T2)> combine, 
	T1 input)
{
	// if trivial just solve it
	if (trivial(input))
		return solve(input);
	else
	{
		// use divide to make 2 lists out of 1
		std::pair<T1, T1> division = divide(input);
		// use combine to combine the results of the 2 subresults
		return combine( divideAndConquer(trivial, solve, divide, combine, division.first), divideAndConquer(trivial, solve, divide, combine, division.second));
	}
}

#pragma region QUICKSORT
/* in order to fit quicksort in this generic schema i have to use a little trick for identical values so i don't run into a infinity loop
when i split a list i remove the pivot and all identical elements from the successive recursion (added again later for the result) */

// Helper function to check if all elements in a vector are identical
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
	// x is trivial if it either has only 0 or 1 element or all elements are identical
	if (x.size() <= 1)
		return true;
	else
		return qs_trivial_checkIdentical(x, x.front());

}

// well... solve is just -> give me the item
template <typename T>
std::vector<T> qs_solve(std::vector<T> x) {	return x; }

template <typename T>
std::pair<std::vector<T>, std::vector<T>> qs_recursiveSplit(std::vector<T> left, std::vector<T> right, std::vector<T> pivotVals, T pivot, std::vector<T> x)
{
	// sort elements and remove all elements equal to the pivot to prevent infinite recursion
	if (x.front() < pivot)
		left.push_back(x.front());
	else if (x.front() > pivot)
		right.push_back(x.front());
	else
		pivotVals.push_back(x.front());

	if (x.size() > 1)
	{
		// since we are not allowed to use loops i have to order the lists recursive
		// i have to build the lists in order to preserve the order of identical elements (quicksort is funny that way)
		return qs_recursiveSplit(left, right, pivotVals, pivot, std::vector<T>(x.begin() + 1, x.end()));
	}
	else
	{
		// i'm at the end -> build the result vector pair
		right.insert(right.begin(), pivotVals.begin(), pivotVals.end());
		return std::make_pair(left, right);
	}

}

template <typename T>
std::pair<std::vector<T>, std::vector<T>> qs_divide(std::vector<T> x)
{
	// select pivot -> last item because i put all predecessor pivots at the start -> prevent loops
	T pivot = x.back();
	return qs_recursiveSplit(std::vector<T>(), std::vector<T>(), std::vector<T>(), pivot, x);
}

// simple concatination
template <typename T>
std::vector<T> qs_combine(std::vector<T> x, std::vector<T> y)
{
	x.insert(x.end(), y.begin(), y.end());
	return x;
}
#pragma endregion

#pragma region MULTIPLICATION
/* Recursive multiplication - maybe not the best example for DaC so there is a binary search after this as well */
template <typename T>
bool mult_trivial(std::vector<T> x)
{
	// stop if there is only 1 element left in the list
	if (x.size() <= 1)
		return true;
	else
		return false;
}

template <typename T>
T mult_solve(std::vector<T> x)
{
	// return 1 if the branch is empty (so it doesn't screw with the multiplication)
	if (x.size() == 0)
		return 1;
	else
		// return the element
		return x.front();
}

template <typename T>
std::pair<std::vector<T>, std::vector<T>> mult_recursiveSplit(std::vector<T> left, std::vector<T> right, std::vector<T> x)
{
	// since the element order doesn't matter for a multiplication i can just evenly divide the items in 2 new vectors
	if (left.size() > right.size())
		right.push_back(x.front());
	else
		left.push_back(x.front());

	// as before... no loops -> recursion to fill the lists
	if (x.size() > 1)
		return mult_recursiveSplit(left, right, std::vector<T>(x.begin() + 1, x.end()));
	else
		return std::make_pair(left, right);
}

template <typename T>
std::pair<std::vector<T>, std::vector<T>> mult_divide(std::vector<T> x)
{
	return mult_recursiveSplit(std::vector<T>(), std::vector<T>(), x);
}

// the real multiplication
template <typename T>
T mult_combine(T x, T y)
{	
	return x * y;
}
#pragma endregion

#pragma region BINARYSEARCH
// i need a few infos to conduct a search so i need a struct to fit them in the predefined template
template <typename T>
struct binSearchParams
{
	int l; // left search index
	int r; // right search index
	T value; // search value
	std::vector<T> input; // input vector

};

// if I can't divide 
template <typename T>
bool binsearch_trivial(binSearchParams<T> x)
{
	if (x.l == x.r)
		return  true;
	else
		return false;
}

template <typename T>
std::vector<int> binsearch_solve(binSearchParams<T> x)
{
	if (x.input[x.l] == x.value)
		return std::vector<T> { x.l };
	else
		return std::vector<T> {};
}

template <typename T>
std::pair<binSearchParams<T>, binSearchParams<T>> binsearch_divide(binSearchParams<T> x)
{
	int m = (int)((x.l + x.r) / 2);
	binSearchParams<T> newL, newR;
	if (x.value <= x.input[m])
	{
		// i have to search this side
		newL.l = x.l;
		newL.r = m;
	}
	else
	{
		// i can skip this side but i have to return something that determindes immediatly
		newL.l = m;
		newL.r = m;
	}
	newL.value = x.value;
	newL.input = x.input;

	if (x.value >= x.input[m+1])
	{
		// i have to search this side
		newR.l = m + 1;
		newR.r = x.r;
	}
	else
	{
		// i can skip this side but i have to return something that determindes immediatly
		newR.l = m+1;
		newR.r = m+1;
	}
	newR.value = x.value;
	newR.input = x.input;

	return std::make_pair(newL, newR);
}

// combine all the result elements
std::vector<int> binsearch_combine(std::vector<int> x, std::vector<int> y)
{
	x.insert(x.end(), y.begin(), y.end());
	return x;
}
#pragma endregion




