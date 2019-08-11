#pragma once

#include <string>
#include <vector>

namespace kyte
{
	void parse(std::string filename);

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

	struct Variable
	{
		Type type;
		std::string name;
	};

	struct Expression
	{

	};

	struct Function
	{
		Type returnType;
		std::string name;
		std::vector<Variable> arguments;
		Expression code;
	};

	class Shader
	{
	public:
		Shader(ShaderType shaderType);
		~Shader();

		void addAttribute(Type type, std::string name);
		void addUniform(Type type, std::string name);
		void addIn(Type type, std::string name);
		void addOut(Type type, std::string name);
		void addFunction(Function function);
		void setMain(Function mainFunction);
		void passThrough(Type type, std::string name);

		const ShaderType& getType() const;
		const std::vector<Variable>& getAttributes() const;
		const std::vector<Variable>& getIns() const;
		const std::vector<Variable>& getOuts() const;
		const std::vector<Variable>& getUniforms() const;
		const std::vector<Function>& getFunctions() const;
		const Function& getMain() const;
	private:
		ShaderType type;
		std::vector<Variable> ins;
		std::vector<Variable> outs;
		std::vector<Variable> uniforms;
		std::vector<Function> functions;
		Function main;
	};

	enum Backend
	{
		GLSL,
		BACKEND_COUNT
	};

	void compile(const Shader& shader, std::string outputFileName, Backend backend);
}
