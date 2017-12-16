#pragma once
// Pure Polymorphic Scan
// scan :: (b -> a -> b) -> b -> [a] -> [b]

template <typename T>
std::vector<T> scan(T(*f)(T, T), T initialScanValue, std::vector<T> input)
{
	return applyScan(f, initialScanValue, input, 0);
}

template <typename T>
std::vector<T> applyScan(T(*f)(T, T), T initialScanValue, std::vector<T> input, unsigned int index)
{
	input[index] = f(initialScanValue, input[index]);
	if (index < input.size() - 1)
		return applyScan(f, input[index], input, index + 1);
	else
		return input;
}
