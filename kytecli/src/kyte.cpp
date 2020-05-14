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

    // get number of sources passed in cuz argparse sux
    int i, j;
    for (i = 1; i < argc && std::strcmp(argv[i], "-k"); i++);
    for (j = i + 1; j < argc && argv[j][0] != '-'; j++);
    int source_count = j - i - 1 > 1 ? j - i - 1 : 1;

    program.add_argument("-k")
        .help("list of source files")
        .nargs(source_count)
        .required();
    
    program.add_argument("-o")
        .help("output object")
        .default_value(std::string("a.spv"));

    program.add_argument("-v")
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

    std::cout << program.get<std::string>("-o") << " " << std::to_string(program["-v"] == true) << std::endl;

    auto sources = program.get<std::vector<std::string>>("-k");
    for (std::string source : sources)
    {
        std::cout << source << std::endl;
    }

	return SUCCESS;
}
