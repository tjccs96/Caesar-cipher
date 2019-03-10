// Caesar Cipher implementation

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cassert>
#include <iterator>


std::string encodeStr(const std::string& str, int shift)
{
	std::string str_enc;
	std::transform(str.cbegin(), str.cend(), std::back_inserter(str_enc), [&](char ch) -> char
	{
		if (ch == 'z' || ch == 'Z')
		{
			return ch - 25;
		}
		else if (isspace(ch))
		{
			return ' ';
		}
		else
		{
			return ch + shift;
		}
	});

	return str_enc;
}

std::vector<std::string> encodeVec(const std::vector<std::string>& strVector, int shift)
{
	std::vector<std::string> tempMsg;
	tempMsg.reserve(strVector.size());

	std::transform(strVector.cbegin(), strVector.cend(), std::back_inserter(tempMsg),
		[&](const std::string& s) { return encodeStr(s, shift); });

	return tempMsg;
}

std::vector<std::string> decode(const std::vector<std::string> &str, int shift)
{
	return encodeVec(str, -1 * shift);
}

int main(int argc, char *argv[])
{
	int choice;
	std::cout << "What do you want to do? 1.Encrypt, 2.Decrypt: ";
	std::cin >> choice;

	if (!(choice == 1 || choice == 2)) {
		return EXIT_FAILURE;
	}

	int key;
	std::cout << "Enter desired shift: ";
	std::cin >> key;

	std::ifstream inFile("testfile.txt");
	if (!inFile)
	{
		// std::cout << "There was a problem with the file!";
		return EXIT_FAILURE; // ExitProcess() if windows especific.
	}

	std::string line;
	std::vector<std::string> lines;

	while (std::getline(inFile, line))
	{
		lines.push_back(line);
	}

	const std::vector<std::string> finalResult = [&]()
	{
		return choice == 1 ? encodeVec(lines, key) : decode(lines, key);
	}();

	std::ofstream outFile("testfile.txt");
	std::copy(finalResult.cbegin(), finalResult.cend(),
		std::ostream_iterator<std::string>(outFile, "\n"));

	return EXIT_SUCCESS;
}