import re

def spirv():
	constant = re.compile(r"^static const unsigned int ([a-zA-Z_][a-zA-Z0-9_]*) = ([0-9a-z]+);")
	enum = re.compile(r"^enum ([a-zA-Z_][a-zA-Z0-9_]*) {")
	enum_value = re.compile(r"^    ([a-zA-Z_][a-zA-Z0-9_]*) = ([0-9a-z]+),?")
	with open("../dependencies/SPIRV-Headers/include/spirv/unified1/spirv.hpp") as c, open("modules/spirv.ky", "w") as k:
		line = c.readline()
		while line:
			rep = constant.sub("const \\1 := \\2;", line)
			if rep != line:
				k.write(rep)
			rep = enum.sub("\nconst \\1 := enum {", line)
			if rep != line:
				k.write(rep)
			rep = enum_value.sub("\t\\1 := \\2,", line)
			if rep != line:
				k.write(rep)
			if line == "};\n":
				k.write("};\n")
			line = c.readline()

def glsl():
	constant = re.compile(r"^static const int GLSLstd450([a-zA-Z_][a-zA-Z0-9_]*) = ([0-9a-z]+);")
	enum_value = re.compile(r"^    GLSLstd450([a-zA-Z_][a-zA-Z0-9_]*) = ([0-9a-z]+),?")
	with open("../dependencies/SPIRV-Headers/include/spirv/unified1/GLSL.std.450.h") as c, open("modules/glslext.ky", "w") as k:
		line = c.readline()
		while line:
			rep = constant.sub("const \\1 := \\2;", line)
			if rep != line:
				k.write(rep)
			if line == "enum GLSLstd450 {\n":
				k.write("\nconst GLSLOp := enum {\n")
			rep = enum_value.sub("\tGLSL\\1 := \\2,", line)
			if rep != line:
				k.write(rep)
			if line == "};\n":
				k.write("\tGLSLstd450Count\n};\n\n")
			line = c.readline()
		k.write(r'''const GLSL_STD_EXT_INST := __spirv_include("GLSL.std.450");

inline __spirv_glsl :: (op : GLSLOp, r : &T<any>, params : any...) $ {
	__spirv(OpExtInst, T, r, GLSL_STD_EXT_INST, op, params...);
};
''')

def ocl():
	enum_value = re.compile(r"^    OpenCLstd_([a-zA-Z_][a-zA-Z0-9_]*) = ([0-9a-z]+),?")
	with open("../dependencies/SPIRV-Headers/include/spirv/unified1/OpenCL.std.h") as c, open("modules/openclext.ky", "w") as k:
		for x in range(217):
			c.readline()
		line = c.readline()
		while line:
			if line == "enum OpenCLstd_Entrypoints {\n":
				k.write("const OpenCLOp := enum {")
			rep = enum_value.sub("\tOPENCL\\1 := \\2,", line)
			if rep != line:
				k.write(rep)
			if line.startswith("    //"):
				k.write("\n\t%s" % line.strip())
			if line == "};\n":
				k.write("};\n\n")
			line = c.readline()
		k.write('''const OPEN_CL_EXT_INST := __spirv_include("OpenCL.std");

inline __spirv_opencl :: (op : OpenCLOp, r : &T<any>, params : any...) $ {
	__spirv(OpExtInst, T, r, OPEN_CL_EXT_INST, op, params...);
};
''')

if __name__ == "__main__":
	spirv()
	glsl()
	ocl()
