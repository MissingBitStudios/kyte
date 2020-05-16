#include <gtest/gtest.h>

#include <kyte/kyte.hpp>

#include <unordered_map>

namespace {

class TestCompiler : public kyte::Compiler
{
public:
	TestCompiler(std::unordered_map<std::string, std::string> sources)
		: sources(sources) {}

	virtual std::string resolve(const std::string& module)
	{
		return sources.at(module);
	}
private:
	std::unordered_map<std::string, std::string> sources;
};

TEST(Compile, Simple)
{
	std::string stl_ky = R"STL(
	const ping_pong : = (value : int) $ int {
		return value;
	}

	const dead: = () $ {

	}
	)STL";

	std::string simple_ky = R"SIMPLE(
	import stl;
	
	@vertex
	const main := () $ int {
		dead();
		return ping_pong(0);
	}
	)SIMPLE";
	
	TestCompiler c({
		{ "stl", stl_ky }
	});

	kyte::Options o;
	o.debugInfo = true;
	c.setOptions(o);

	EXPECT_NO_THROW({
		c.compile(simple_ky);
	});
}
} // end namespace
