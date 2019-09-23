%skeleton "lalr1.cc"
%define parser_class_name {parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define parse.error verbose
%locations   // <--

%code requires
{
#include <iostream>
#include <fstream>

struct lexcontext;
}//%code requires

%param { lexcontext& ctx }

%code
{
struct lexcontext
{
	const char* cursor;
	yy::location loc;
	int condition;
	unsigned int comment_scope = 0;
};

namespace yy { parser::symbol_type yylex(lexcontext& ctx); }
}//%code

%token             ATTRIBUTE "attribute" UNIFORM "uniform" SAMPLER "sampler"
%token             IMPORT "import"
%token             CONST "const" EXTERN "extern" TYPEDEF "typedef" OPERATOR "operator"
%token             STRUCT "struct" ENUM "enum" FLOAT "float" INT "int" DOUBLE "double" UINT "uint"
%token             RETURN "return" DISCARD "discard"
%token             IF "if" ELSE "else"  SWITCH "switch" CASE "case"
%token             FOR "for" DO "do" WHILE "while" BREAK "break" CONTINUE "continue"
%token             FLOAT_LITERAL INTEGER_LITERAL IDENTIFIER
%token             ARROW "->" OR "||" AND "&&" EQ "==" NE "!=" PP "++" MM "--" PL_EQ "+=" MI_EQ "-=" MU_EQ "*=" DI_EQ "/=" MO_EQ "%=" BOR_EQ "|=" BAND_EQ "&=" BXOR_EQ "^=" BLS_EQ "<<=" BRS_EQ ">>=" BLS "<<" BRS ">>" LT_EQ "<=" GT_EQ ">="

%left  ','
%right '?' ':' '=' "+=" "-=" "*=" "/=" "%="
%left  "||"
%left  "&&"
%left  "==" "!="
%left  '+' '-'
%left  '*'
%right "++" "--"
%left  '(' '[' '{'

%type<float>       FLOAT_LITERAL
%type<int>         INTEGER_LITERAL
%type<std::string> IDENTIFIER

%%

identifier_list
	: identifier_list1
	{

	}
	| %empty
	;

identifier_list1
	: identifier_list1 ',' IDENTIFIER
	{

	}
	| IDENTIFIER
	{

	}
	;

%%

/*!types:re2c*/

yy::parser::symbol_type yy::yylex(lexcontext& ctx)
{
    const char* anchor = ctx.cursor;
    ctx.loc.step();
	auto ws = [&]() { ctx.loc.columns(ctx.cursor - anchor); };
    auto s  = [&](auto func, auto&&... params) { ctx.loc.columns(ctx.cursor - anchor); return func(params..., ctx.loc); };
#define r(label) { anchor = ctx.cursor; goto label; }
start:
	%{ /* Begin re2c lexer */
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE  = "char";
	re2c:define:YYCURSOR = "ctx.cursor";
	re2c:define:YYGETCONDITION = "ctx.condition";
	re2c:define:YYGETCONDITION:naked = 1;
	re2c:define:YYSETCONDITION = "ctx.condition = @@;";
	re2c:define:YYSETCONDITION:naked = 1;

	// Keywords
	<init> "typedef"               { return s(parser::make_TYPEDEF); }
	<init> "if"                    { return s(parser::make_IF); }
	<init> "else"                  { return s(parser::make_ELSE); }
	<init> "switch"                { return s(parser::make_SWITCH); }
	<init> "case"                  { return s(parser::make_CASE); }
	<init> "for"                   { return s(parser::make_FOR); }
	<init> "do"                    { return s(parser::make_DO); }
	<init> "while"                 { return s(parser::make_WHILE); }
	<init> "break"                 { return s(parser::make_BREAK); }
	<init> "continue"              { return s(parser::make_CONTINUE); }
	<init> "struct"                { return s(parser::make_STRUCT); }
	<init> "import"                { return s(parser::make_IMPORT); }
	<init> "extern"                { return s(parser::make_EXTERN); }
	<init> "const"                 { return s(parser::make_CONST); }
	<init> "return"                { return s(parser::make_RETURN); }
	<init> "enum"                  { return s(parser::make_ENUM); }
	<init> "discard"               { return s(parser::make_DISCARD); }
	<init> "attribute"             { return s(parser::make_ATTRIBUTE); }
	<init> "uniform"               { return s(parser::make_UNIFORM); }
	<init> "sampler"               { return s(parser::make_SAMPLER); }
	<init> "operator"              { return s(parser::make_OPERATOR); }
	<init> "float"                 { return s(parser::make_FLOAT); }
	<init> "double"                { return s(parser::make_DOUBLE); }
	<init> "int"                   { return s(parser::make_INT); }
	<init> "uint"                  { return s(parser::make_UINT); }

	// Whitespace
	<*> "\r\n" | [\r\n]            { ctx.loc.lines();   r(start); }
	<*> [\t\v\b\f ]                { ctx.loc.columns(); r(start); }

	// Identifiers
	<init> [a-zA-Z_] [a-zA-Z_0-9]* { return s(parser::make_IDENTIFIER, std::string(anchor, ctx.cursor)); }

	// Literals
	<init> [0-9]+ [f]              { return s(parser::make_FLOAT_LITERAL, std::stof(std::string(anchor, ctx.cursor))); }
	<init> [0-9]+                  { return s(parser::make_INTEGER_LITERAL, std::stoi(std::string(anchor, ctx.cursor))); }

	// Comments
	<init> "//" [^\r\n]*           { ws(); r(yyc_init); }
	<*> "/*"                       { ws(); ctx.comment_scope++; r(yyc_block_comment); }
	<block_comment> "*/"           { ws(); ctx.comment_scope--; if(!ctx.comment_scope) r(yyc_init); }
	<block_comment> *              { ctx.loc.columns(); r(yyc_block_comment); }

	// Multi-char operators and any other character (either an operator or an invalid symbol)
	<init> "->"                    { return s(parser::make_ARROW); }
	<init> "&&"                    { return s(parser::make_AND); }
	<init> "||"                    { return s(parser::make_OR); }
	<init> "++"                    { return s(parser::make_PP); }
	<init> "--"                    { return s(parser::make_MM); }
	<init> "!="                    { return s(parser::make_NE); }
	<init> "=="                    { return s(parser::make_EQ); }
	<init> "+="                    { return s(parser::make_PL_EQ); }
	<init> "-="                    { return s(parser::make_MI_EQ); }
	<init> "*="                    { return s(parser::make_MU_EQ); }
	<init> "/="                    { return s(parser::make_DI_EQ); }
	<init> "%="                    { return s(parser::make_MO_EQ); }
	<init> "|="                    { return s(parser::make_BOR_EQ); }
	<init> "&="                    { return s(parser::make_BAND_EQ); }
	<init> "^="                    { return s(parser::make_BXOR_EQ); }
	<init> "<<="                   { return s(parser::make_BLS_EQ); }
	<init> ">>="                   { return s(parser::make_BRS_EQ); }
	<init> "<<"                    { return s(parser::make_BLS); }
	<init> ">>"                    { return s(parser::make_BRS); }
	<init> "<="                    { return s(parser::make_LT_EQ); }
	<init> ">="                    { return s(parser::make_GT_EQ); }
	<init> *                       { return s([](auto...s){return parser::symbol_type(s...);}, parser::token_type(ctx.cursor[-1]&0xFF)); }
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
