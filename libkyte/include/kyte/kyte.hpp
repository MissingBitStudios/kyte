#pragma once

#include <string>
#include <vector>

namespace kyte
{
	enum Type
	{
		VOID,
		FLOAT,
		INT,
		BOOL,
		BVEC2,
		BVEC3,
		BVEC4,
		IVEC2,
		IVEC3,
		IVEC4,
		VEC2,
		VEC3,
		VEC4,
		MAT2,
		MAT3,
		MAT4,
		SAMPLER_2D,
		SAMPLER_CUBE,
		TYPE_COUNT
	};

	enum ShaderType
	{
		FRAGMENT,
		VERTEX,
		SHADER_TYPE_COUNT
	};

	enum ExpressionType
	{

	};

	struct Variable
	{
		Type type;
		std::string name;
	};

	struct Expression
	{
		ExpressionType type;
	};

	struct Function
	{
		Function(float f);
		Function();
		Type returnType;
		std::string name;
		Expression arguments;
		Expression code;
	};

	struct AST
	{
		std::vector<Function> functions;
	};

	enum BackendType
	{
		GLSL,
		HLSL,
		METAL,
		SPIRV,
		BACKEND_TYPE_COUNT
	};

	struct ShaderData
	{
		ShaderType type;
		BackendType backend;
		std::string sourceCode;
		std::string programName;
		unsigned int binarySize;
		const unsigned char* binary;
	};

	class CompilerCallback
	{
	public:
		CompilerCallback(BackendType backendType, unsigned int languageVersion = 0);
		~CompilerCallback();

		std::string BeforePreprocess(const std::string& sourceCode);
		std::string AfterPreprocess(const std::string& sourceCode);
		AST AfterParse(const AST& ast);
		std::string AfterCompile(const std::string& sourceCode);
	protected:
		BackendType backend;
		unsigned int version;
	};

	AST parse(const std::string& sourceCode, std::string debugName = "");
	std::string preprocess(const std::string& sourceCode, BackendType backendType, unsigned int languageVersion = 0);

	std::string compileSource(std::string sourceCode, BackendType backendType, unsigned int languageVersion = 0, CompilerCallback* compilerCallback = nullptr);
}
