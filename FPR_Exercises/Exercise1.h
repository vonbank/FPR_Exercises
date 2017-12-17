#pragma once
// Pure Polymorphic Map
// map :: (a -> b) -> [a] -> [b]
template<typename T>
std::vector<T> map(T(*f)(T), std::vector<T> input)
{
	if (input.size() > 1)
	{
		std::vector<T> tmp = map(f, std::vector<T>(input.begin() + 1, input.end()) );
		std::vector<T> output = { f(input.front()) };
		output.insert(output.end(), tmp.begin(), tmp.end());
		return output;
	}
	else
		return std::vector<T> { f(input.front()) };
}
