#include <argparse.hpp>
#include <kyte/kyte.hpp>

enum StatusCode
{
    SUCCESS,
    ARGUMENT_PARSE_ERROR
};

int main(int argc, char** argv)
{
    argparse::ArgumentParser program("kytecli");

    program.add_argument("--source")
        .help("display the square of a given integer")
        .action([](const std::string& value) { return std::stoi(value); });

    program.add_argument("--verbose")
        .help("increase output verbosity")
        .default_value(false)
        .implicit_value(true);

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error & err)
    {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(ARGUMENT_PARSE_ERROR);
    }

	return SUCCESS;
}
