// Caesar Cipher implementation

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>


std::vector<std::string> encode(const std::vector<std::string> &str, int shift)
{
	std::vector<std::string> tempMsg;

	for (std::string lines : str)
	{
		// std::transform(lines.cbegin(), lines.cend(), std::back_inserter(tempMsg), [&](char ch) -> char
		for (char &ch : lines)
		{
			if (ch == 'z' || ch == 'Z')
			{
				ch -= 25;
			}
			else if (isspace(ch)) {
				ch = ' ';
			}
			else
			{
				ch += shift;
			}
		}
		tempMsg.push_back(lines);
	}

	return tempMsg;
}

std::vector<std::string> decode(const std::vector<std::string> &str, int shift)
{
	return encode(str, -1 * shift);
}


int main(int argc, char *argv[])
{
	int choice;
	std::cout << "What do you want to do? 1.Encrypt, 2.Decrypt: ";
	std::cin >> choice;
	
	
	int key;
	std::cout << "Enter desired shift: ";
	std::cin >> key;


	std::ifstream inFile("testfile.txt");
	if (!(inFile.is_open()))
	{
		std::cout << "There was a problem with the file!";
		std::exit(EXIT_FAILURE); // ExitProcess() if windows especific.
	}

	std::vector<std::string> finalResult;

	std::string line;
	std::vector<std::string> lines;


	while (std::getline(inFile, line))
	{
		lines.push_back(line);
	}
	inFile.close();

	if (choice == 1)
	{
		auto result = encode(lines, key);
		finalResult = result;
	}

	else if (choice == 2)
	{
		auto result = decode(lines, key);
		finalResult = result;
	}
	else
	{
		std::cout << "Wrong option, exiting!";
		std::exit(EXIT_FAILURE);
	}

	
	std::ofstream outFile("testfile.txt");
	for (auto i = finalResult.begin(); i != finalResult.end(); ++i)
	{
		outFile << *i << '\n';
	}
	outFile.close();

	std::exit(EXIT_SUCCESS);
}