#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <sstream>
#include "RandomGen.hpp"

template <typename T, typename X>
void FillContainerTest(sds::RandomGen& ro, auto& outputStream, const int minLength = 10, const int maxLength = 10)
{
	using std::for_each, std::cout, std::begin, std::end;
	//filling a container T with random X
	T fillContainer{};
	const bool result = ro.FillContainerRandom<X>(fillContainer, minLength, maxLength);
	outputStream << "\nPrinting some values from a " << typeid(X).name() << '\n';
	if (result)
	{
		for (const auto elem : fillContainer)
		{
			if constexpr (std::same_as<X, signed char> || std::same_as<X, unsigned char>)
				outputStream << std::dec << "[" << static_cast<const int>(elem) << "]";
			else
				outputStream << std::dec << "[" << static_cast<X>(elem) << "]";
		}
		outputStream << "\n\n";
	}
	else
	{
		outputStream << "Error filling container in FillContainerTests() where T:" << typeid(T).name() << ", X:" << typeid(X).name() << ", strm:" << typeid(outputStream).name() << '\n';
	}
}

int main()
{
	/* Note if you run this solution with clang ASAN enabled, you will see "access violation reading location" messages as the asan expands the address space
	 * via generating exceptions.
	 * Also note that in VS 2019 having a "requires (someconcept) && (someconcept)" on a line separate from the template<typename T> declaration line
	 * would not parse! The compiler could not parse that line, it was very obviously a bug, so be aware if you use C++20 concepts in VS2019.
	 */
	using namespace std;
	constexpr size_t NumberOfItems = 10;
	constexpr size_t MaxLengthOfStrings = 10;
	constexpr size_t MinLengthOfStrings = 3;
	constexpr size_t MinLength = 10;
	constexpr size_t MaxLength = 10;
	sds::RandomGen ro;
	// can be used to delay or disable output.
	std::stringstream ss;
	std::wstringstream ws;
	//building a vector of strings
	const auto stringVec = ro.BuildRandomStringVector(NumberOfItems, MaxLengthOfStrings, MaxLengthOfStrings);
	ss << "Printing some character values, the default char type for std::string might be signed..." << endl;
	for (const auto& selem : stringVec)
	{
		for (const auto celem : selem)
			ss << std::dec << "[" << static_cast<const int>(celem) << "]";
		ss << endl;
	}
	ss << endl << endl;
	//building a vector of random size (between the arg values) with random data.
	const auto stringVec2 = ro.BuildRandomVector<unsigned char>(MinLength, MaxLength);
	ss << "Printing some unsigned character values." << endl;
	for (const auto elem : stringVec2)
		ss << std::dec << "[" << static_cast<const int>(elem) << "]";
	ss << endl << endl;
	//building a vector of wstrings (wide char)
	const auto stringVec3 = ro.BuildRandomWStringVector(NumberOfItems, MinLengthOfStrings, MaxLengthOfStrings);
	ws << "Printing some wide char values." << endl;
	for (const auto& selem : stringVec3)
	{
		for (const auto welem : selem)
			ws << std::dec << "[" << static_cast<const int>(welem) << "]";
		ws << endl;
	}
	cout << ss.str();
	wcout << ws.str();
	ss.str("");
	FillContainerTest<std::list<unsigned char>, unsigned char>(ro,ss);
	FillContainerTest<std::list<char>, char>(ro,ss);
	FillContainerTest<std::vector<int>, int>(ro, ss);
	FillContainerTest<std::vector<unsigned int>, unsigned int>(ro, ss);
	FillContainerTest<std::vector<long long>, long long>(ro, ss);
	FillContainerTest<std::vector<unsigned long long>, unsigned long long>(ro, ss);
	cout << ss.str();
	ss.str("");
	
	//building single element values
	auto PrintSingleValue = [&ss](auto val)
	{
		//ss.imbue(std::locale(""));
		ss << typeid(decltype(val)).name() << ":" << std::showpos << std::dec << val << endl;
	};
	PrintSingleValue(ro.BuildRandomSingleValue<unsigned char>());
	PrintSingleValue(ro.BuildRandomSingleValue<signed char>());
	PrintSingleValue(ro.BuildRandomSingleValue<unsigned int>());
	PrintSingleValue(ro.BuildRandomSingleValue<signed int>());
	PrintSingleValue(ro.BuildRandomSingleValue<unsigned long long>());
	PrintSingleValue(ro.BuildRandomSingleValue<signed long long>());
	cout << ss.str();
	ss.str("");

	//FillContainerTest<std::vector<bool>, bool>(ro, ss); // doesn't work for bool, constrained away

	cout << "Enter to exit." << endl;
	cin.get();
}
