#include "kyte_p.hpp"

namespace kyte
{
	GLSLBackend::GLSLBackend(unsigned int languageVersion)
		: Backend(languageVersion)
	{

	}

	GLSLBackend::~GLSLBackend()
	{

	}

	std::string GLSLBackend::compile(const AST& shader)
	{
		return "";
	}

	std::string GLSLBackend::function(Function func)
	{
		return type(func.returnType) + " " + func.name + "(" + expression(func.arguments) +")\n{\n}\n\n";
	}

	std::string GLSLBackend::expression(Expression expression)
	{
		switch (expression.type)
		{
		default:
			return "";
		}
	}

	std::string GLSLBackend::type(Type t)
	{
		return "void";
	}

	// arithmatic
	std::string GLSLBackend::multiply(Expression a, Expression b)
	{
		return "(" + expression(a) + " * " + expression(b) + ")";
	}

	std::string GLSLBackend::divide(Expression a, Expression b)
	{
		return "(" + expression(a) + " / " + expression(b) + ")";
	}

	std::string GLSLBackend::addition(Expression a, Expression b)
	{
		return "(" + expression(a) + " + " + expression(b) + ")";
	}

	std::string GLSLBackend::subtract(Expression a, Expression b)
	{
		return "(" + expression(a) + " - " + expression(b) + ")";
	}

	std::string GLSLBackend::negate(Expression a)
	{
		return "-" + expression(a);
	}

	std::string GLSLBackend::power(Expression a, Expression b)
	{
		return "pow(" + expression(a) + ", " + expression(b) + ")";
	}

	std::string GLSLBackend::modulo(Expression a, Expression b)
	{
		return "mod(" + expression(a) + ", " + expression(b) + ")";
	}

	std::string GLSLBackend::number(Expression a)
	{
		return "0";
	}

	// arithmatic assignment
	std::string GLSLBackend::assignment(Expression a, Expression b)
	{
		return expression(a) + " = " + expression(b);
	}

	std::string GLSLBackend::additionAssignment(Expression a, Expression b)
	{
		return expression(a) + " += " + expression(b);
	}

	std::string GLSLBackend::subtractionAssignment(Expression a, Expression b)
	{
		return expression(a) + " -= " + expression(b);
	}

	std::string GLSLBackend::multiplicationAssignment(Expression a, Expression b)
	{
		return expression(a) + " *= " + expression(b);
	}

	std::string GLSLBackend::divisionAssignment(Expression a, Expression b)
	{
		return expression(a) + " /= " + expression(b);
	}

	std::string GLSLBackend::moduloAssignment(Expression a, Expression b)
	{
		return expression(a) + " %= " + expression(b);
	}

	// logical
	std::string GLSLBackend::equal(Expression a, Expression b)
	{
		return "(" + expression(a) + " == " + expression(b) + ")";
	}

	std::string GLSLBackend::notEqual(Expression a, Expression b)
	{
		return "(" + expression(a) + " != " + expression(b) + ")";
	}

	std::string GLSLBackend::less(Expression a, Expression b)
	{
		return "(" + expression(a) + " < " + expression(b) + ")";
	}

	std::string GLSLBackend::lessEqual(Expression a, Expression b)
	{
		return "(" + expression(a) + " <= " + expression(b) + ")";
	}

	std::string GLSLBackend::greater(Expression a, Expression b)
	{
		return "(" + expression(a) + " > " + expression(b) + ")";
	}

	std::string GLSLBackend::greaterEqual(Expression a, Expression b)
	{
		return "(" + expression(a) + " >= " + expression(b) + ")";
	}

	std::string GLSLBackend::inclusiveOr(Expression a, Expression b)
	{
		return "(" + expression(a) + " || " + expression(b) + ")";
	}

	std::string GLSLBackend::exclusiveOr(Expression a, Expression b)
	{
		return "(" + expression(a) + " ^^ " + expression(b) + ")";
	}

	std::string GLSLBackend::and(Expression a, Expression b)
	{
		return "(" + expression(a) + " && " + expression(b) + ")";
	}

	std::string GLSLBackend::not(Expression a)
	{
		return "!" + expression(a);
	}

	std::string GLSLBackend::ternary(Expression a, Expression b, Expression c)
	{
		return expression(a) + " ? " + expression(b) + " : " + expression(c);
	}

	// bitwise
	std::string GLSLBackend::bitAnd(Expression a, Expression b)
	{
		return "(" + expression(a) + " & " + expression(b) + ")";
	}

	std::string GLSLBackend::bitExclusiveOr(Expression a, Expression b)
	{
		return "(" + expression(a) + " ^ " + expression(b) + ")";
	}

	std::string GLSLBackend::bitInclusiveOr(Expression a, Expression b)
	{
		return "(" + expression(a) + " | " + expression(b) + ")";
	}

	std::string GLSLBackend::bitNot(Expression a)
	{
		return "~" + expression(a);
	}

	std::string GLSLBackend::bitLeftShift(Expression a, Expression b)
	{
		return "(" + expression(a) + " << " + expression(b) + ")";
	}

	std::string GLSLBackend::bitRightShift(Expression a, Expression b)
	{
		return "(" + expression(a) + " >> " + expression(b) + ")";
	}

	// bitwise assignemnt
	std::string GLSLBackend::bitAndAssignment(Expression a, Expression b)
	{
		return "(" + expression(a) + " &= " + expression(b) + ")";
	}

	std::string GLSLBackend::bitExclusiveOrAssignment(Expression a, Expression b)
	{
		return "(" + expression(a) + " ^= " + expression(b) + ")";
	}

	std::string GLSLBackend::bitInclusiveOrAssignment(Expression a, Expression b)
	{
		return "(" + expression(a) + " |= " + expression(b) + ")";
	}

	std::string GLSLBackend::bitNotAssignment(Expression a, Expression b)
	{
		return "(" + expression(a) + " ~= " + expression(b) + ")";
	}

	std::string GLSLBackend::bitLeftShiftAssignment(Expression a, Expression b)
	{
		return "(" + expression(a) + " <<= " + expression(b) + ")";
	}

	std::string GLSLBackend::bitRightShiftAssignment(Expression a, Expression b)
	{
		return "(" + expression(a) + " >>= " + expression(b) + ")";
	}

	// other
	std::string GLSLBackend::sequence(Expression a, Expression b)
	{
		return expression(a) + ", " + expression(b);
	}
}
