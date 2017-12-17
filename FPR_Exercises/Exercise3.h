#pragma once
// Pure Polymorphic Scan
// scan :: (b -> a -> b) -> b -> [a] -> [b]

template <typename T1, typename T2>
std::vector<T2> scan(std::function<T2(T2, T1)> f, T2 initialScanValue, std::vector<T1> input)
{
	if (input.size() > 1) // break recursion on last element
	{
		// calculate current result value
		T1 calcValue = f(initialScanValue, input.front());

		// call scan for next element and use current result as new initialScanValue
		std::vector<T2> tmp = scan(f, calcValue, std::vector<T1>(input.begin() + 1, input.end()));

		// put current result in a vector and concatinate with recursion result
		std::vector<T2> output = { calcValue };
		output.insert(output.end(), tmp.begin(), tmp.end());
		return output;
	}
	else
		return std::vector<T2> { f(initialScanValue, input.front()) }; // last value -> return fold result
}
