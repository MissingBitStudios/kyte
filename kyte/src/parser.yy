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
};

namespace yy { parser::symbol_type yylex(lexcontext& ctx); }
}//%code

%token             END 0
%token             BLOCK_COMMENT_ERROR
%token             ATTRIBUTE "attribute" UNIFORM "uniform" SAMPLER "sampler"
%token             IMPORT "import"
%token             CONST "const" EXTERN "extern" TYPEDEF "typedef" OPERATOR "operator"
%token             STRUCT "struct" ENUM "enum"
%token             RETURN "return" DISCARD "discard"
%token             IF "if" ELSE "else"  SWITCH "switch" CASE "case"
%token             FOR "for" DO "do" WHILE "while" BREAK "break" CONTINUE "continue"
%token             FLOAT_LITERAL INTEGER_LITERAL IDENTIFIER
%token             ARROW "->"
%token             PL_EQ "+=" MI_EQ "-=" MU_EQ "*=" DI_EQ "/=" MO_EQ "%=" PP "++" MM "--"
%token             OR "||" AND "&&" EQ "==" NE "!=" LT_EQ "<=" GT_EQ ">="
%token             BOR_EQ "|=" BAND_EQ "&=" BXOR_EQ "^=" BLS_EQ "<<=" BRS_EQ ">>=" BLS "<<" BRS ">>"

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

program
	: program1
	| %empty
	;

program1
	: program1 function
	| function
	| program1 statement
	| statement
	| program1 type_definition
	| type_definition
	;

op
	: "+="
	| "-="
	| "*="
	| "/="
	| "%="
	| "++"
	| "--"
	| "||"
	| "&&"
	| "=="
	| "!="
	| "<="
	| ">="
	| "|="
	| "&="
	| "^="
	| "<<="
	| ">>="
	| "<<"
	| ">>"
	| '+'
	| '-'
	| '*'
	| '/'
	| '%'
	;

expression
	: FLOAT_LITERAL
	| INTEGER_LITERAL
	| IDENTIFIER
	| '(' expression ')'
	| '(' expression ')' expression
	;

statement
	: expression ';'
	| "return" expression ';'
	| ';'
	;

statements
	: statements1
	| %empty
	;

statements1
	: statements1 statement
	| statement
	;

subscript
	: '[' IDENTIFIER ']'
	| '[' INTEGER_LITERAL ']'
	;

subscripts
	: subscripts1
	| %empty
	;

subscripts1
	: subscripts1 subscript
	| subscript
	;

type
	: IDENTIFIER subscripts
	;

compound_type
	: '<' compound_type1 '>'
	;

compound_type1
	: compound_type1 ',' type
	| type
	;

formal_paramater
	: type
	| compound_type
	| IDENTIFIER ':' type
	| IDENTIFIER ':' IDENTIFIER compound_type
	;

formal_paramaters
	: formal_paramaters1
	| %empty
	;

formal_paramaters1
	: formal_paramaters1 ',' formal_paramater
	| formal_paramater
	;

formal_returns
	: formal_returns ',' type
	| type
	;

function
	: IDENTIFIER '(' formal_paramaters ')' "->" formal_returns '{' statements '}'
	| "extern" IDENTIFIER '(' formal_paramaters ')' "->" formal_returns ';'
	| "operator" op '(' formal_paramaters ')' "->" formal_returns ';'
	| "extern" "operator" op '(' formal_paramaters ')' "->" formal_returns ';'
	;

type_definition
	: "typedef" IDENTIFIER type ';'
	| "typedef" IDENTIFIER compound_type ';'
	;

%%

/*!types:re2c*/

yy::parser::symbol_type yy::yylex(lexcontext& ctx)
{
    const char* anchor = ctx.cursor;
    ctx.loc.step();
	unsigned int comment_scope = 0;
	int condition = yycinit;
#define walk() { ctx.loc.columns(ctx.cursor - anchor); }
#define advance(label) { anchor = ctx.cursor; ctx.loc.step(); goto label; }
#define token(name) { walk(); return parser::make_##name(ctx.loc); }
#define tokenv(name, ...) { walk(); return parser::make_##name(__VA_ARGS__, ctx.loc); }
	%{ /* Begin re2c lexer */
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE  = "char";
	re2c:define:YYCURSOR = "ctx.cursor";
	re2c:define:YYGETCONDITION = "condition";
	re2c:define:YYGETCONDITION:naked = 1;
	re2c:define:YYSETCONDITION = "condition = @@;";
	re2c:define:YYSETCONDITION:naked = 1;

	// Keywords
	<init> "typedef"               { token(TYPEDEF); }
	<init> "if"                    { token(IF); }
	<init> "else"                  { token(ELSE); }
	<init> "switch"                { token(SWITCH); }
	<init> "case"                  { token(CASE); }
	<init> "for"                   { token(FOR); }
	<init> "do"                    { token(DO); }
	<init> "while"                 { token(WHILE); }
	<init> "break"                 { token(BREAK); }
	<init> "continue"              { token(CONTINUE); }
	<init> "struct"                { token(STRUCT); }
	<init> "import"                { token(IMPORT); }
	<init> "extern"                { token(EXTERN); }
	<init> "const"                 { token(CONST); }
	<init> "return"                { token(RETURN); }
	<init> "enum"                  { token(ENUM); }
	<init> "discard"               { token(DISCARD); }
	<init> "attribute"             { token(ATTRIBUTE); }
	<init> "uniform"               { token(UNIFORM); }
	<init> "sampler"               { token(SAMPLER); }
	<init> "operator"              { token(OPERATOR); }

	// Whitespace
	<init> "\r\n" | [\r\n]         { ctx.loc.lines();   advance(yyc_init); }
	<init> [\t\v\b\f ]             { ctx.loc.columns(); advance(yyc_init); }
	<init> [\x00]                  { token(END); }

	// Identifiers
	<init> [a-zA-Z_] [a-zA-Z_0-9]* { tokenv(IDENTIFIER, std::string(anchor, ctx.cursor)); }

	// Literals
	<init> [0-9]+ [f]              { tokenv(FLOAT_LITERAL, std::stof(std::string(anchor, ctx.cursor))); }
	<init> [0-9]+                  { tokenv(INTEGER_LITERAL, std::stoi(std::string(anchor, ctx.cursor))); }

	// Comments
	<init> "//" [^\r\n]*           { walk(); advance(yyc_init); }
	<*> "/*"                       { comment_scope++; goto yyc_block_comment; }
	<block_comment> "*/"           { walk(); comment_scope--; if(!comment_scope) advance(yyc_init); goto yyc_block_comment; }
	<block_comment> "\r\n" | [\r\n]{ ctx.loc.lines();   advance(yyc_block_comment); }
	<block_comment> [\t\v\b\f ]    { ctx.loc.columns(); advance(yyc_block_comment); }
	<block_comment> [\x00]         { token(BLOCK_COMMENT_ERROR); }
	<block_comment> *              { goto yyc_block_comment; }

	// Multi-char operators and any other character (either an operator or an invalid symbol)
	<init> "->"                    { token(ARROW); }
	<init> "&&"                    { token(AND); }
	<init> "||"                    { token(OR); }
	<init> "++"                    { token(PP); }
	<init> "--"                    { token(MM); }
	<init> "!="                    { token(NE); }
	<init> "=="                    { token(EQ); }
	<init> "+="                    { token(PL_EQ); }
	<init> "-="                    { token(MI_EQ); }
	<init> "*="                    { token(MU_EQ); }
	<init> "/="                    { token(DI_EQ); }
	<init> "%="                    { token(MO_EQ); }
	<init> "|="                    { token(BOR_EQ); }
	<init> "&="                    { token(BAND_EQ); }
	<init> "^="                    { token(BXOR_EQ); }
	<init> "<<="                   { token(BLS_EQ); }
	<init> ">>="                   { token(BRS_EQ); }
	<init> "<<"                    { token(BLS); }
	<init> ">>"                    { token(BRS); }
	<init> "<="                    { token(LT_EQ); }
	<init> ">="                    { token(GT_EQ); }
	<init> *                       { walk(); return parser::symbol_type(parser::token_type(ctx.cursor[-1]&0xFF), ctx.loc); }
	%} /* End lexer */
}

void yy::parser::error(const location_type& l, const std::string& message)
{
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
