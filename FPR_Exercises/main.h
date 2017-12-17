#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <tuple>
#include <functional>
#include "Exercise1.h"
#include "Exercise2.h"
#include "Exercise3.h"
#include "Exercise4.h"

// function for convenient output
template <typename T>
void exerciseOutput(std::string exerciseText, std::vector<T> input, std::vector<T> output)
{
	std::cout << "===== " << exerciseText << " =====" << "\n";
	std::cout << "input: ";
	for (auto i = input.begin(); i != input.end(); ++i)
	{
		if (i != input.begin()) { std::cout << " | "; }
		std::cout << *i;
	}
	std::cout << '\n';
	std::cout << "output: ";
	for (auto i = output.begin(); i != output.end(); ++i)
	{
		if (i != output.begin()) { std::cout << " | "; }
		std::cout << *i;
	}

	std::cout << '\n';
	std::cout << '\n';
}