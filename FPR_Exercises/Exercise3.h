#pragma once
// Pure Polymorphic Scan
// scan :: (b -> a -> b) -> b -> [a] -> [b]

template <typename T>
std::vector<T> scan(T(*f)(T, T), T initialScanValue, std::vector<T> input)
{
	if (input.size() > 1)
	{
		std::vector<T> tmp = scan(f, f(initialScanValue, input.front()), std::vector<T>(input.begin() + 1, input.end()));
		std::vector<T> output = { f(initialScanValue, input.front()) };
		output.insert(output.end(), tmp.begin(), tmp.end());
		return output;
	}
	else
		return std::vector<T> { f(initialScanValue, input.front()) };
}
