#include <gtest/gtest.h>

#include <kyte/kyte.hpp>

#include <unordered_map>

namespace {

TEST(Compile, Simple)
{
	std::string simple_ky = R"SIMPLE(
	@vertex
	const main := () $ int {
		dead();
		return ping_pong(0);
	}

	const ping_pong : = (value : int) $ int {
		return value;
	}

	const dead: = () $ {

	}
	)SIMPLE";
	
	kyte::Compiler c;

	kyte::Options o;
	o.debugInfo = true;
	o.showDisassembly = true;
	c.setOptions(o);

	EXPECT_NO_THROW({
		c.compile(simple_ky);
	});
}
} // end namespace
