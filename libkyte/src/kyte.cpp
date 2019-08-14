#include "kyte_p.hpp"

#define callback(method, param) if (compilerCallback) { param = compilerCallback->method(param); }

namespace kyte
{
	CompilerCallback::CompilerCallback(BackendType backendType, unsigned int languageVersion)
		: backend(backendType), version(languageVersion)
	{

	}

	CompilerCallback::~CompilerCallback()
	{

	}

	std::string CompilerCallback::BeforePreprocess(const std::string& sourceCode)
	{
		return sourceCode;
	}

	std::string CompilerCallback::AfterPreprocess(const std::string& sourceCode)
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

		callback(BeforePreprocess, sourceCode);

		sourceCode = preprocess(sourceCode, backendType, languageVersion);

		callback(AfterPreprocess, sourceCode);

		AST ast = parse(sourceCode);

		callback(AfterParse, ast);

		std::string output = backend->compile(ast);

		callback(AfterCompile, output);

		return output;
	}
}
