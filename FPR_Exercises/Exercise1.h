#pragma once
// Pure Polymorphic Map
// map :: (a -> b) -> [a] -> [b]
template<typename T1, typename T2>
std::vector<T2> map(std::function<T2(T1)> f, std::vector<T1> input)
{
	if (input.size() > 1) // stop recursion on the last element
	{
		// call f for the other elements recursive
		std::vector<T2> tmp = map(f, std::vector<T1>(input.begin() + 1, input.end()) );
		// calculate f for the current element
		std::vector<T2> output = { f(input.front()) };
		// concatinate current element with the recursion result
		output.insert(output.end(), tmp.begin(), tmp.end());
		return output;
	}
	else
		return std::vector<T2> { f(input.front()) }; // i'm on the last element -> return the value
}
