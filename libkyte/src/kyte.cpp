#include "kyte_p.hpp"

#include <sstream>

#define callback(method, param) if (compilerCallback) { param = compilerCallback->method(param); }

namespace kyte
{
	Function::Function(float f)
	{

	}

	Function::Function()
	{

	}

	CompilerCallback::CompilerCallback(BackendType backendType, unsigned int languageVersion)
		: backend(backendType), version(languageVersion)
	{

	}

	CompilerCallback::~CompilerCallback()
	{

	}

	std::string CompilerCallback::BeforeParse(const std::string& sourceCode)
	{
		return sourceCode;
	}

	AST CompilerCallback::AfterParse(const AST& ast)
	{
		return ast;
	}

	std::string CompilerCallback::AfterCompile(const std::string& sourceCode)
	{
		return sourceCode;
	}

	std::string preprocess(const std::string& sourceCode, BackendType backendType, unsigned int languageVersion)
	{
		return sourceCode;
	}

	std::string compileSource(std::string sourceCode, BackendType backendType, unsigned int languageVersion, CompilerCallback* compilerCallback)
	{
		Backend* backend = nullptr;
		switch (backendType)
		{
		case GLSL:
			backend = new GLSLBackend(languageVersion);
			break;
		case HLSL:
			break;
		case METAL:
			break;
		case SPIRV:
			break;
		default:
			break;
		}

		if (!backend)
		{
			// error
		}

		callback(BeforeParse, sourceCode);

		sourceCode = preprocess(sourceCode, backendType, languageVersion);

		AST ast = parse(sourceCode);

		callback(AfterParse, ast);

		std::string output = backend->compile(ast);

		callback(AfterCompile, output);

		return output;
	}


	std::string toHex(unsigned char c)
	{
		const char* keys = "0123456789ABCDEF";
		std::string result = "0x";
		result += keys[c / 16];
		result += keys[c % 16];
		return result;
	}

	void replace(std::string& str, const std::string& oldStr, const std::string& newStr)
	{
		size_t pos = 0;
		while ((pos = str.find(oldStr, pos)) != std::string::npos)
		{
			str.replace(pos, oldStr.length(), newStr);
			pos += newStr.length();
		}
	}

	std::string formatString(std::string format, ShaderData shaderData)
	{
		const char* t[SHADER_TYPE_COUNT] = { "fs", "vs" };
		const char* b[BACKEND_TYPE_COUNT] = { "glsl", "hlsl", "metal", "spirv" };
		
		replace(format, "%t", t[shaderData.type]);
		replace(format, "%b", b[shaderData.backend]);
		replace(format, "%n", shaderData.programName);
	}

	std::string header(std::string outputFormat, std::vector<ShaderData> shaderDatas)
	{
		std::ostringstream out;

		for (ShaderData data : shaderDatas)
		{
			std::string name = formatString(outputFormat, data);
			out << "static const int " + name + "_len = " << data.binarySize << ";\n";
			out << "static const unsigned char " + name + "[] = {\n\t";
			for (size_t j = 0; j < data.binarySize; ++j)
			{
				out << toHex((unsigned char)data.binary[j]);
				if (j == data.binarySize - 1)
				{
					out << "\n";
				}
				else
				{
					out << ",";
					if ((j + 1) % 25 == 0)
					{
						out << "\n\t";
					}
				}
			}
			out << "};\n\n";
		}

		return out.str();
	}
}
