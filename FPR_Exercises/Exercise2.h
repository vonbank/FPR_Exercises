#pragma once
// Pure Polymorphic Fold
// fold :: (a -> a -> a) -> a -> [a] -> a
template <typename T>
T fold(T(*f)(T, T), T initialFoldValue, std::vector<T> input)
{
	if (input.size() > 1)
		return fold(f, f(initialFoldValue, input.front()), std::vector<T>(input.begin() + 1, input.end()));
	else
		return f(initialFoldValue, input.front());
}
