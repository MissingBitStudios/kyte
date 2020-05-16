#include <kyte/kyte.hpp>

#include <argparse.hpp>

#include <fstream>

enum StatusCode
{
    SUCCESS,
    ARGUMENT_PARSE_ERROR,
    COMPILER_OPTIONS_ERROR,
    COMPILER_ERROR
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
        .help("optimization level")
        .default_value(0);

    program.add_argument("-v")
        .help("increase output verbosity")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-g")
        .help("include debug information")
        .default_value(false)
        .implicit_value(true);

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err)
    {
        std::cout << err.what() << std::endl;
        std::cout << program;
        return ARGUMENT_PARSE_ERROR;
    }

    kyte::Compiler c;
    kyte::Options o;
    o.debugInfo = program.get<bool>("-g");
    o.optimizationLevel = program.get<int>("-o");
    try
    {
        c.setOptions(o);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return COMPILER_OPTIONS_ERROR;
    }

    std::vector<std::string> sources = program.get<std::vector<std::string>>("-k");
    for (std::string source : sources)
    {
        std::ifstream f(source + ".ky");
        std::string s;

        f.seekg(0, std::ios::end);
        s.reserve(f.tellg());
        f.seekg(0, std::ios::beg);

        s.assign((std::istreambuf_iterator<char>(f)),
            std::istreambuf_iterator<char>());
  
        std::vector<uint32_t> binary;

        try
        {
            binary = c.compile(s);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return COMPILER_ERROR;
        }

        std::ofstream b(source + ".spv", std::ios::binary);
        b.write((const char*)binary.data(), sizeof(uint32_t) * binary.size());
    }

	return SUCCESS;
}
