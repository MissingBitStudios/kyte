#include <kyte/kyte.hpp>

#include <fstream>
#include <string>
#include <vector>

#include <iostream>

using namespace kyte;

int main(int argc, char** argv)
{
	std::vector<std::string> sources;
	std::string output;
	std::string header;

	int i = 1;
	while (i < argc)
	{
		std::string arg = argv[i];
		if (arg == "-o")
		{
			if (output.empty())
			{
				if (i + 1 < argc)
				{
					output = argv[i + 1];
					i += 2;
				}
				else
				{
					std::cerr << "-o: output rule must follow -o option" << std::endl;
					return 1;
				}
			}
			else
			{
				std::cerr << "-o: only one output string allowed" << std::endl;
				return 1;
			}
		}
		else if (arg == "-h")
		{
			if (header.empty())
			{
				if (i + 1 < argc)
				{
					header = argv[i + 1];
					i += 2;
				}
				else
				{
					std::cerr << "-h: header path must follow -h option" << std::endl;
					return 1;
				}
			}
			else
			{
				std::cerr << "-h: header flag may only be used once" << std::endl;
				return 1;
			}
		}
		else
		{
			sources.push_back(arg);
			i++;
		}
	}

	for (std::string source : sources)
	{
		std::cout << "source: " << source << "\n";
	}
	std::cout << "output: " << output << "\n"
	          << "header: " << header << "\n";
}
