#pragma once

#include "kyte/kyte.hpp"

#include <string>

namespace kyte
{
	class Backend
	{
	public:
		Backend(unsigned int languageVersion = 0);
		virtual ~Backend();

		virtual std::string compile(const AST& shader) = 0;
	protected:
		unsigned int version = 0;
	};

	class GLSLBackend : public Backend
	{
	public:
		GLSLBackend(unsigned int languageVersion);
		~GLSLBackend();

		virtual std::string compile(const AST& shader);
	protected:
		std::string function(Function funct);
		std::string expression(Expression expression);
		std::string type(Type t);

		// arithmatic
		std::string multiply(Expression a, Expression b);
		std::string divide(Expression a, Expression b);
		std::string addition(Expression a, Expression b);
		std::string subtract(Expression a, Expression b);
		std::string negate(Expression a);
		std::string power(Expression a, Expression b);
		std::string modulo(Expression a, Expression b);
		std::string number(Expression a);

		// arithmatic assignment
		std::string assignment(Expression a, Expression b);
		std::string additionAssignment(Expression a, Expression b);
		std::string subtractionAssignment(Expression a, Expression b);
		std::string multiplicationAssignment(Expression a, Expression b);
		std::string divisionAssignment(Expression a, Expression b);
		std::string moduloAssignment(Expression a, Expression b);

		// logical
		std::string equal(Expression a, Expression b);
		std::string notEqual(Expression a, Expression b);
		std::string less(Expression a, Expression b);
		std::string lessEqual(Expression a, Expression b);
		std::string greater(Expression a, Expression b);
		std::string greaterEqual(Expression a, Expression b);
		std::string inclusiveOr(Expression a, Expression b);
		std::string exclusiveOr(Expression a, Expression b);
		std::string and (Expression a, Expression b);
		std::string not(Expression a);
		std::string ternary(Expression a, Expression b, Expression c);

		// bitwise
		std::string bitAnd(Expression a, Expression b);
		std::string bitExclusiveOr(Expression a, Expression b);
		std::string bitInclusiveOr(Expression a, Expression b);
		std::string bitNot(Expression a);
		std::string bitLeftShift(Expression a, Expression b);
		std::string bitRightShift(Expression a, Expression b);

		// bitwise assignemnt
		std::string bitAndAssignment(Expression a, Expression b);
		std::string bitExclusiveOrAssignment(Expression a, Expression b);
		std::string bitInclusiveOrAssignment(Expression a, Expression b);
		std::string bitNotAssignment(Expression a, Expression b);
		std::string bitLeftShiftAssignment(Expression a, Expression b);
		std::string bitRightShiftAssignment(Expression a, Expression b);

		// other
		std::string sequence(Expression a, Expression b);
	};
}
