#pragma once
// Pure Polymorphic Fold
// fold :: (a -> a -> a) -> a -> [a] -> a
template <typename T>
T fold(std::function<T(T, T)> f, T initialFoldValue, std::vector<T> input)
{
	if (input.size() > 1) // break recursion on last element
		// call fold for the next element and use f of initialFoldValue and current value as new initialFoldValue
		return fold(f, f(initialFoldValue, input.front()), std::vector<T>(input.begin() + 1, input.end()));
	else
		return f(initialFoldValue, input.front()); // last element -> return complete fold result
}
