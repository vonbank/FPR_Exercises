#pragma once
// Pure Polymorphic Fold
// fold :: (a -> a -> a) -> a -> [a] -> a
template <typename T>
T fold(T(*f)(T, T), T initialFoldValue, std::vector<T> input)
{
	return applyFold(f, initialFoldValue, input, 0);
}

template <typename T>
T applyFold(T(*f)(T, T), T initialFoldValue, std::vector<T> input, unsigned int index)
{
	if (index < input.size() - 1)
		return applyFold(f, f(initialFoldValue, input[index]), input, index + 1);
	else
		return f(initialFoldValue, input[index]);
}
