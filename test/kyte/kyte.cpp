#include <gtest/gtest.h>

#include <kyte/kyte.hpp>

namespace {
TEST(Compile, Simple)
{
	std::string stl_ky = R"STL(
	ping_pong : = (value : int) : int{
		return value;
	}

	dead: = (){

	}
	)STL";

	std::string simple_ky = R"SIMPLE(
	import stl;
	
	main := () : int {
		dead();
		return ping_pong(0);
	}
	)SIMPLE";

	std::vector<kyte::SourceFile> sources = {
		{ "stl", stl_ky },
		{ "simple", simple_ky }
	};
	
	EXPECT_NO_THROW({
		kyte::compile(sources);
	});
}
} // end namespace
