#pragma once
// Higher-Order Divide and Conquer

template <typename T1, typename T2>
T2 divideAndConquer(bool (*trivial)(T1), T2 (*solve)(T1), std::pair<T1, T1> (*divide)(T1), T2 (*combine)(T2, T2), T1 input)
{
	if (trivial(input))
		return solve(input);
	else
	{
		std::pair<T1, T1> division = divide(input);
		return combine( divideAndConquer(trivial, solve, divide, combine, std::get<0>(division)), divideAndConquer(trivial, solve, divide, combine, std::get<1>(division)));
	}
}

