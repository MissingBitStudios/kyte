#include <kyte/kyte.hpp>

#include <fstream>
#include <string>

int main(int argc, char** argv)
{
	kyte::Shader vertex(kyte::VERTEX);
	kyte::Shader fragment(kyte::FRAGMENT);

	vertex.addAttribute(kyte::FLOAT, "atr");

	vertex.addUniform(kyte::INT, "mvp");

	kyte::Function helperFunction = { kyte::INT, "helper", {{kyte::FLOAT, "var1"}, {kyte::INT, "var2"}}, {} };
	vertex.addFunction(helperFunction);

	kyte::Function mainFunction = { kyte::VOID, "vs_test", {}, {} };
	vertex.setMain(mainFunction);

	kyte::compile(vertex, "test.vs", kyte::GLSL);
}
