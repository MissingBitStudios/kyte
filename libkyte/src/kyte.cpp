#include "kyte/kyte.hpp"

#include <fstream>

namespace kyte
{
	Shader::Shader(ShaderType shaderType)
		: type(shaderType)
	{
	}

	Shader::~Shader()
	{
	}

	void Shader::addAttribute(Type type, std::string name)
	{
		addIn(type, name);
	}

	void Shader::addUniform(Type type, std::string name)
	{
		uniforms.push_back({ type, name });
	}

	void Shader::addIn(Type type, std::string name)
	{
		ins.push_back({ type, name });
	}

	void Shader::addOut(Type type, std::string name)
	{
		outs.push_back({ type, name });
	}

	void Shader::addFunction(Function function)
	{
		functions.push_back(function);
	}

	void Shader::setMain(Function mainFunction)
	{
		main = mainFunction;
	}

	void Shader::passThrough(Type type, std::string name)
	{
		addIn(type, name);
		addOut(type, name);
	}

	const ShaderType& Shader::getType() const
	{
		return type;
	}

	const std::vector<Variable>& Shader::getAttributes() const
	{
		return ins;
	}

	const std::vector<Variable>& Shader::getIns() const
	{
		return ins;
	}

	const std::vector<Variable>& Shader::getOuts() const
	{
		return outs;
	}

	const std::vector<Variable>& Shader::getUniforms() const
	{
		return uniforms;
	}

	const std::vector<Function>& Shader::getFunctions() const
	{
		return functions;
	}

	const Function& Shader::getMain() const
	{
		return main;
	}

	void compileGLSL(std::ofstream& file, const Shader& shader)
	{
		const char* typeNames[TYPE_COUNT] = { "void", "float", "int" };

		if (shader.getType() == VERTEX)
		{
			for (Variable attribute : shader.getAttributes())
			{
				file << "attribute " << typeNames[attribute.type] << " " << attribute.name << ";\n";
			}

			if (shader.getAttributes().size() > 0)
			{
				file << "\n";
			}

			for (Variable out : shader.getOuts())
			{
				file << "out " << typeNames[out.type] << " " << out.name << ";\n";
			}

			if (shader.getOuts().size() > 0)
			{
				file << "\n";
			}

			for (Variable uniform : shader.getUniforms())
			{
				file << "uniform " << typeNames[uniform.type] << " " << uniform.name << ";\n";
			}

			if (shader.getUniforms().size() > 0)
			{
				file << "\n";
			}

			for (Function function : shader.getFunctions())
			{
				file << typeNames[function.returnType] << " " << function.name << "(";
				for (size_t i = 0; i < function.arguments.size(); i++)
				{
					file << typeNames[function.arguments[i].type] << " " << function.arguments[i].name << (i == function.arguments.size() - 1 ? " " : ", ");
				}
				file << ")\n{\n";
				//print function expressions
				file << "}\n\n";
			}

			file << "void main()\n{\n";
			//print main function expressions
			file << "}\n";
		}
	}

	void compile(const Shader& shader, std::string outputFileName, Backend backend)
	{
		std::ofstream file(outputFileName, std::ofstream::out);
		switch (backend)
		{
		case GLSL:
			compileGLSL(file, shader);
			break;
		default:
			break;
		}
		file.close();
	}
}
