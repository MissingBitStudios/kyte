%require "3.4.1"
%language "c++"

%skeleton "lalr1.cc"

%define api.parser.class { parser }
%define api.token.constructor
%define api.value.type variant
%define api.location.file none
%define parse.assert
%define parse.error verbose

%locations

%code requires
{
#include <iostream>
#include <algorithm> // max

struct lexcontext;
}//%code requires

%param { lexcontext& ctx }

%code
{
struct lexcontext
{
	const char* cursor;
	yy::location loc;
};

namespace yy { parser::symbol_type yylex(lexcontext& ctx); }
}//%code

%token END 0
%token BLOCK_COMMENT_ERROR
%token IDENTIFIER INTEGER_LITERAL
%token CONST "const"
%token RETURN "return"
%token VERTEX_TAG "@vertex"

%type<std::string> IDENTIFIER
%type<uint32_t> INTEGER_LITERAL

%start translation_unit

%%

translation_unit
	: IDENTIFIER
	| translation_unit IDENTIFIER
	;

%%

yy::parser::symbol_type yy::yylex(lexcontext& ctx)
{
	const char* YYMARKER;
	const char* anchor = ctx.cursor;
	unsigned int comment_scope = 0;
#define walk() { ctx.loc.columns(ctx.cursor - anchor); }
#define advance(label) { anchor = ctx.cursor; ctx.loc.step(); goto label; }
#define token(name) { walk(); return parser::make_##name(ctx.loc); }
#define tokenv(name, ...) { walk(); return parser::make_##name(__VA_ARGS__, ctx.loc); }

%{ /* Begin re2c lexer */
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE  = "char";
	re2c:define:YYCURSOR = "ctx.cursor";
	
	end = "\x00";
	%}

init:
	%{
	// Keywords
	"const"                  { token(CONST); }
	"return"                 { token(RETURN); }
	"@vertex"                { token(VERTEX_TAG); }

	// Identifier
	[a-zA-Z_][a-zA-Z_0-9]*   { tokenv(IDENTIFIER, std::string(anchor, ctx.cursor)); }

	// Literals
	-?[0-9]+                 { tokenv(INTEGER_LITERAL, std::stoi(std::string(anchor, ctx.cursor))); }

	// Whitespace
	"\r\n" | [\r\n]          { ctx.loc.lines();   advance(init); }
	[\t\v\b\f ]              { ctx.loc.columns(); advance(init); }
	end                      { token(END); }

	// Comment
	"//" [^\r\n]*            { walk(); advance(init); }
	"/*"                     { comment_scope++; goto block_comment; }

	// Multi-char operators and any other character (either an operator or an invalid symbol)
	*                        { walk(); return parser::symbol_type(parser::token_type(ctx.cursor[-1]&0xFF), ctx.loc); }
	%}

block_comment:
	%{
	// Block Comment
	"/*"                     { comment_scope++; goto block_comment; }
	"*/"                     { comment_scope--; if(!comment_scope) { walk(); advance(init); } goto block_comment; }
	"\r\n" | [\r\n]          { ctx.loc.lines();   advance(block_comment); }
	end                      { token(BLOCK_COMMENT_ERROR); }
	*                        { goto block_comment; }
	%} /* End lexer */
}

void yy::parser::error(const location_type& l, const std::string& message)
{
	std::cerr << message << std::endl;

	/*
	std::cerr << l.begin.filename->c_str() << ':' << l.begin.line << ':' << l.begin.column << '-' << l.end.column << ": " << message << '\n';

	// find a better way. dont open and skip for every single error
	std::ifstream f(l.begin.filename->c_str());
	std::string s;

	for (int i = 0; i < l.begin.line; i++)
	{
		std::getline(f, s);
	}

	std::cout << s << std::endl;
   f.close();

	std::cerr << std::string(l.begin.column - 1, ' ') << '^' << std::string(l.end.column - l.begin.column - 1, '~') << std::endl;
	*/
}

namespace kyte
{
	void parse(const std::string& sourceCode)
	{
		lexcontext ctx;
		ctx.cursor = sourceCode.c_str();

		yy::parser parser(ctx);
		parser.parse();
	}
}
