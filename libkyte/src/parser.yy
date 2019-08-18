%skeleton "lalr1.cc"
%define parser_class_name {parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define parse.error verbose
%locations   // <--

%code requires
{
#include "kyte_p.hpp"

using namespace kyte;

struct lexcontext;
}//%code requires

%param { lexcontext& ctx }

%code
{

struct lexcontext
{
    const char* cursor;
    yy::location loc;

	std::vector<Function> functions;
};

namespace yy { parser::symbol_type yylex(lexcontext& ctx); }
}//%code

%token             END 0
%token             ATTRIBUTE "attribute" UNIFORM "uniform" SAMPLER "sampler"
%token             IDENTIFIER
%token             FLOAT INT
%token             TYPE
%token             ARROW "->" OR "||" AND "&&" EQ "==" NE "!=" PP "++" MM "--" PL_EQ "+=" MI_EQ "-=" MU_EQ "*=" DI_EQ "/=" MO_EQ "%="

%left  ','
%right '?' ':' '=' "+=" "-=" "*=" "/=" "%="
%left  "||"
%left  "&&"
%left  "==" "!="
%left  '+' '-'
%left  '*'
%right "++" "--"
%left  '(' '['

%type<float>       FLOAT
%type<int>         INT
%type<std::string> IDENTIFIER
%type<Function> function
%type<Type> TYPE
%type<std::vector<Type>> types

%%

program
	: program function
	{
		ctx.functions.push_back($2);
	}
	| program attribute
	| program uniform
	| program sampler
	| %empty
	;

function
	: IDENTIFIER '(' paramaters ')' "->" types '{' expressions '}'
	{
		$$ = Function($1, $3, $6, $8);
	}
	| IDENTIFIER '(' paramaters ')' '{' expressions '}'
	{
		$$ = Function($1, $3, $6);
	}
	;

paramaters
	: paramaters1
	{
		
	}
	| %empty
	{

	}
	;

paramaters1
	: paramaters1 ',' paramater
	{

	}
	| paramater
	{
		
	}
	;

paramater
	: IDENTIFIER ':' TYPE
	{

	}
	;

types
	: types ',' TYPE
	{
		$1.push_back($3);
	}
	| TYPE
	{
		$$ = { $1 };
	}
	;

expressions
	: expressions expression
	{

	}
	| %empty
	{

	}
	;

expression
	: FLOAT
	{

	}
	;

attribute
	: "attribute" IDENTIFIER ':' TYPE '$' IDENTIFIER ';'
	{

	}
	;

uniform
	: "uniform" IDENTIFIER ':' TYPE ';'
	{

	}
	;

sampler
	: "sampler" IDENTIFIER ':' TYPE '$' INT ';'
	{

	}
	;

%%

Type stot(std::string s)
{
	return VOID;
}

yy::parser::symbol_type yy::yylex(lexcontext& ctx)
{
    const char* anchor = ctx.cursor;
    ctx.loc.step();
    auto s = [&](auto func, auto&&... params) { ctx.loc.columns(ctx.cursor - anchor); return func(params..., ctx.loc); };
%{ /* Begin re2c lexer */
re2c:yyfill:enable   = 0;
re2c:define:YYCTYPE  = "char";
re2c:define:YYCURSOR = "ctx.cursor";

// Keywords
"attribute" { return s(parser::make_ATTRIBUTE); }
"uniform" { return s(parser::make_UNIFORM); }
"sampler" { return s(parser::make_SAMPLER); }

// Types:
"float" | "int" { return s(parser::make_TYPE, stot(std::string(anchor,ctx.cursor))); }

// Identifiers:
[a-zA-Z_] [a-zA-Z_0-9]* { return s(parser::make_IDENTIFIER, std::string(anchor,ctx.cursor)); }

// String and integer literals:
[0-9]+f                 { return s(parser::make_FLOAT, std::stof(std::string(anchor,ctx.cursor))); }
[0-9]+                  { return s(parser::make_INT, std::stoi(std::string(anchor,ctx.cursor))); }

// Whitespace and comments:
"\000"                  { return s(parser::make_END); }
"\r\n" | [\r\n]         { ctx.loc.lines();   return yylex(ctx); }
"//" [^\r\n]*           {                    return yylex(ctx); }
[\t\v\b\f ]             { ctx.loc.columns(); return yylex(ctx); }

// Multi-char operators and any other character (either an operator or an invalid symbol):
"->"                    { return s(parser::make_ARROW); }
"&&"                    { return s(parser::make_AND); }
"||"                    { return s(parser::make_OR); }
"++"                    { return s(parser::make_PP); }
"--"                    { return s(parser::make_MM); }
"!="                    { return s(parser::make_NE); }
"=="                    { return s(parser::make_EQ); }
"+="                    { return s(parser::make_PL_EQ); }
"-="                    { return s(parser::make_MI_EQ); }
"*="                    { return s(parser::make_MU_EQ); }
"/="                    { return s(parser::make_DI_EQ); }
"%="                    { return s(parser::make_MO_EQ); }
.                       { return s([](auto...s){return parser::symbol_type(s...);}, parser::token_type(ctx.cursor[-1]&0xFF)); } // Return that character
%} /* End lexer */
}

void yy::parser::error(const location_type& l, const std::string& m)
{
    std::cerr << (l.begin.filename ? l.begin.filename->c_str() : "(undefined)");
    std::cerr << ':' << l.begin.line << ':' << l.begin.column << '-' << l.end.column << ": " << m << '\n';
}

namespace kyte
{
	AST parse(const std::string& sourceCode, std::string debugName)
	{
		lexcontext ctx;
		ctx.cursor = sourceCode.c_str();
		ctx.loc.begin.filename = &debugName;
		ctx.loc.end.filename   = &debugName;

		yy::parser parser(ctx);
		parser.parse();

		AST ast;
		ast.functions = ctx.functions;

		return ast;
	}
}
