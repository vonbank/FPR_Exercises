#pragma once
// Pure Polymorphic Map
// map :: (a -> b) -> [a] -> [b]
template<typename T>
std::vector<T> map(T(*f)(T), std::vector<T> input)
{
	if (input.size() > 1) // stop recursion on the last element
	{
		// call f for the other elements recursive
		std::vector<T> tmp = map(f, std::vector<T>(input.begin() + 1, input.end()) );
		// calculate f for the current element
		std::vector<T> output = { f(input.front()) };
		// concatinate current element with the recursion result
		output.insert(output.end(), tmp.begin(), tmp.end());
		return output;
	}
	else
		return std::vector<T> { f(input.front()) }; // i'm on the last element -> return the value
}
