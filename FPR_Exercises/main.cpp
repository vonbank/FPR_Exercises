#include "main.h"

// functions for exercise 1
int f_ex1_int(int x) { return x * x; }
std::string f_ex1_str(std::string x) { return "i am " + x; }
double f_ex1_dbl(double x) { return x + 0.5; }

// functions for exercise 2
int f_ex2_int(int x, int y) { return x + y; }
std::string f_ex2_str(std::string x, std::string y) { return x + y;  }
double f_ex2_dbl(double x, double y) { return x * y; }

// functions for exercise 3
int f_ex3_int(int x, int y) { return x + y; }
std::string f_ex3_str(std::string x, std::string y) { return x + y; }
double f_ex3_dbl(double x, double y) { return x * y; }

// functions for exercise 4
bool qs_trivial_checkIdentical(std::vector<int> x, int val)
{
	if (x.front() != val)
		return false;
	else if (x.size() <= 1)
		return true;
	else
	{
		return qs_trivial_checkIdentical(std::vector<int>(x.begin() + 1, x.end()), val);
	}
}

bool qs_trivial(std::vector<int> x) 
{
	if (x.size() <= 1)
		return true;
	else
		return qs_trivial_checkIdentical(x, x.front());
	 
}

std::vector<int> qs_solve(std::vector<int> x)
{ 
	return x;
}
std::pair<std::vector<int>, std::vector<int>> qs_recursiveSplit(std::vector<int> left, std::vector<int> right, std::vector<int> pivotVals, int pivot, std::vector<int> x)
{
	if (x.front() < pivot)
		left.push_back(x.front());
	else if (x.front() > pivot)
		right.push_back(x.front());
	else
		pivotVals.push_back(x.front());

	if (x.size() > 1)
	{
		return qs_recursiveSplit(left, right, pivotVals, pivot, std::vector<int>(x.begin() + 1, x.end()));
	}
	else
	{
		right.insert(right.begin(), pivotVals.begin(), pivotVals.end());
		return std::make_pair(left, right);
	}
			
}


std::pair<std::vector<int>, std::vector<int>> qs_divide(std::vector<int> x)
{
	int pivot = x.back();



	return qs_recursiveSplit(std::vector<int>(), std::vector<int>(), std::vector<int>(), pivot, x);
}

std::vector<int> qs_combine(std::vector<int> x, std::vector<int> y) 
{ 
	x.insert(x.end(), y.begin(), y.end());
	return x;
}

int main()
{
	std::vector<int> v_int = { 1, 2, 3, 4, 5 };
	std::vector<std::string> v_str = { "bla", "bli", "blubb" };
	std::vector<double> v_dbl = { 0.2, 1.4, 2.654 };

	// Exercise 01
	std::vector<int> v_ex1_int_out = map<int>(f_ex1_int, v_int);
	exerciseOutput<int>("Exercise 01 <int>", v_int, v_ex1_int_out);

	std::vector<std::string> v_ex1_str_out = map<std::string>(f_ex1_str, v_str);
	exerciseOutput<std::string>("Exercise 01 <string>", v_str, v_ex1_str_out);
	
	std::vector<double> v_ex1_dbl_out = map<double>(f_ex1_dbl, v_dbl);
	exerciseOutput<double>("Exercise 01 <double>", v_dbl, v_ex1_dbl_out);

	// Exercise 02
	std::vector<int> v_ex2_int_out = { fold<int>(f_ex2_int, 0, v_int) };
	exerciseOutput<int>("Exercise 02 <int>", v_int, v_ex2_int_out);

	std::vector<std::string> v_ex2_str_out = { fold<std::string>(f_ex2_str, "start:", v_str) };
	exerciseOutput<std::string>("Exercise 02 <string>", v_str, v_ex2_str_out);

	std::vector<double> v_ex2_dbl_out = { fold<double>(f_ex2_dbl, 0.1, v_dbl) };
	exerciseOutput<double>("Exercise 02 <double>", v_dbl, v_ex2_dbl_out);

	// Exercise 03
	std::vector<int> v_ex3_int_out = scan<int>(f_ex3_int, 0, v_int);
	exerciseOutput<int>("Exercise 03 <int>", v_int, v_ex3_int_out);

	std::vector<std::string> v_ex3_str_out = scan<std::string>(f_ex3_str, "init", v_str);
	exerciseOutput<std::string>("Exercise 03 <string>", v_str, v_ex3_str_out);

	std::vector<double> v_ex3_dbl_out = scan<double>(f_ex3_dbl, 0.137, v_dbl);
	exerciseOutput<double>("Exercise 03 <double>", v_dbl, v_ex3_dbl_out);

	// Exercise 04
	std::vector<int> sortMe = { 3, 5, 8, 6, 1, 5, 0, 9, 5, 3, 7, 3, 5 };
	std::vector<int> v_ex4_int_out = divideAndConquer(qs_trivial, qs_solve, qs_divide, qs_combine, sortMe);
	exerciseOutput<int>("Exercise 03 <int> Quicksort", sortMe, v_ex4_int_out);

	std::cin.get();
	return 0;
}