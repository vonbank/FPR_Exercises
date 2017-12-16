#pragma once
// Pure Polymorphic Map
// map :: (a -> b) -> [a] -> [b]
template<typename T>
std::vector<T> applyMap(T(*f)(T), std::vector<T> input, unsigned int index)
{
	input[index] = f(input[index]);
	if (index < input.size() - 1)
		return applyMap(f, input, index + 1);
	else
		return input;
}
template<typename T>
std::vector<T> map(T(*f)(T), std::vector<T> input)
{
	return applyMap(f, input, 0);
}