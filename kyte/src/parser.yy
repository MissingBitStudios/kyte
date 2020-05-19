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
#include <fstream>
#include <algorithm>

struct lexcontext;
}//%code requires

%param { lexcontext& ctx }

%code
{
enum class IdentifierFlag
{
	TYPE_NAME,
	VARIABLE_NAME,
	FUNCTION_NAME
};

struct lexcontext
{
	const char* cursor;
	yy::location loc;
	IdentifierFlag identifierFlag;
};

namespace yy { parser::symbol_type yylex(lexcontext& ctx); }
}//%code

%token END 0
%token BLOCK_COMMENT_ERROR
%token IDENTIFIER CONSTANT TYPE_NAME FUNCTION_NAME VARIABLE_NAME
%token ATTRIBUTE "attribute" UNIFORM "uniform" SAMPLER "sampler"
%token IMPORT "import"
%token INC_OP "++" DEC_OP "--"
%token AND_OP "&&" OR_OP "||" EQ_OP "==" NE_OP "!=" LE_OP "<=" GE_OP ">="
%token MUL_ASSIGN "*=" DIV_ASSIGN "/=" MOD_ASSIGN "%=" ADD_ASSIGN "+=" SUB_ASSIGN "-="
%token LEFT_OP "<<" RIGHT_OP ">>"
%token LEFT_ASSIGN "<<=" RIGHT_ASSIGN ">>=" AND_ASSIGN "&="
%token XOR_ASSIGN "^=" OR_ASSIGN "|=" NOT_ASSIGN "~="
%token DECL_ASSIGN ":=" ASSIGN "=" SET_TYPE ":"
%token OPERATOR "operator" CONST "const"
%token INT "int" UINT "uint" FLOAT "float" DOUBLE "double" BOOL "bool"
%token STRUCT "struct" ENUM "enum"
%token ELLIPSIS "..." ARROW "->"
%token CASE "case" DEFAULT "default" IF "if" ELSE "else" SWITCH "switch"
%token WHILE "while" DO "do" FOR "for"
%token CONTINUE "continue" BREAK "break" RETURN "return" DISCARD "discard"
%type<std::string> IDENTIFIER

%start translation_unit

%%

// whole translation unit with import and functions
translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

// imports and functions
external_declaration
    : declaration
    | external_declaration declaration
    | external_declaration tag declaration
    | %empty
	;

tag
    : '@' tag_word
    | tag '@' tag_word
    ;

tag_word
    : "inline"
    | "iknowwhatiamdoing"
    | "private"
    | "vertex"
    | "fragment"
    | "geometry"
    | "compute"
    | "tesselation"
	;

// declarations for functions and variables
declaration
    : function_declaration ";"
    | declaration function_declaration ";"
    | variable_declaration
    | declaration variable_declaration
    ;

function_declaration
    : IDENTIFIER ":=" '(' function_arguments ')' compound_statement // void function declaration
    | CONST IDENTIFIER ":=" '(' function_arguments ')' compound_statement // const void function declaration
    | IDENTIFIER ":=" '(' function_arguments ')' "$" TYPE_NAME compound_statement // function declaration with return
    | CONST IDENTIFIER ":=" '(' function_arguments ')' "$" TYPE_NAME compound_statement // const function declaration with return
    ;

function_arguments
    : IDENTIFIER ":" TYPE_NAME
    | function_arguments "," IDENTIFIER ":" TYPE_NAME
    ;

variable_declaration
    : IDENTIFIER ":=" expression_statement // variable declaration
    | CONST IDENTIFIER ":=" expression_statement // const declaration
    ;

// any kind of statement
statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
    | declaration
	;

// follow switch statements
labeled_statement
	: CASE expression ':' statement
	| DEFAULT ':' statement
	;

// used for functions, if statements, loops, etc.
compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' labeled_statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	| DISCARD
	;

assignment_operator
	: ASSIGN // "="
    | DECL_ASSIGN // ":="
	| MUL_ASSIGN // "*="
	| DIV_ASSIGN // "/="
	| MOD_ASSIGN // "%="
	| ADD_ASSIGN // "+="
	| SUB_ASSIGN // "-="
	| LEFT_ASSIGN // "<<="
	| RIGHT_ASSIGN // ">>="
	| AND_ASSIGN // "&="
	| XOR_ASSIGN // "^="
	| OR_ASSIGN // "|="
	| NOT_ASSIGN // "~="
	;

// all the expression stuff below

expression
    : IDENTIFIER
    | CONSTANT
    | function_call_expression
    ;

function_call_expression
    : IDENTIFIER "(" argument_list ")"
    ;

argument_list
    : IDENTIFIER
    | CONSTANT
    | argument_list "," IDENTIFIER
    | argument_list "," CONSTANT
    ;

%%





%{ /* Begin re2c lexer */
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE  = "char";
	re2c:define:YYCURSOR = "ctx.cursor";
	
	end = "\x00";
	%}

init:
	%{
	// Keywords
	"if"                     { token(IF); }
	"else"                   { token(ELSE); }
	"switch"                 { token(SWITCH); }
	"case"                   { token(CASE); }
	"for"                    { token(FOR); }
	"do"                     { token(DO); }
	"while"                  { token(WHILE); }
	"break"                  { token(BREAK); }
	"continue"               { token(CONTINUE); }
	"struct"                 { token(STRUCT); }
	"import"                 { token(IMPORT); }
	"const"                  { token(CONST); }
	"return"                 { token(RETURN); }
	"enum"                   { token(ENUM); }
	"discard"                { token(DISCARD); }
	"attribute"              { token(ATTRIBUTE); }
	"uniform"                { token(UNIFORM); }
	"sampler"                { token(SAMPLER); }
	"operator"               { token(OPERATOR); }
	"int"                    { token(INT); }
	"uint"                   { token(UINT); }
	"float"                  { token(FLOAT); }
	"double"                 { token(DOUBLE); }
	"bool"                   { token(BOOL); }

	// Whitespace
	"\r\n" | [\r\n]          { ctx.loc.lines();   advance(init); }
	[\t\v\b\f ]              { ctx.loc.columns(); advance(init); }
	end                      { token(END); }

	// Identifiers
	[a-zA-Z_] [a-zA-Z_0-9]*  { return getIdentifier(std::string(anchor, ctx.cursor)); }

	// Literals
	[0-9]+ [f]               { token(CONSTANT); }
	[0-9]+                   { token(CONSTANT); }
    
    // Strings
    [a-zA-Z0-9_.-/\:]        { token(CONSTANT); }

	// Comment
	"//" [^\r\n]*            { walk(); advance(init); }
	"/*"                     { comment_scope++; goto block_comment; }

	// Multi-char operators and any other character (either an operator or an invalid symbol)
	"..."                    { token(ELLIPSIS); }
	"->"                     { token(ARROW); }
	"&&"                     { token(AND_OP); }
	"||"                     { token(OR_OP); }
	"++"                     { token(INC_OP); }
	"--"                     { token(DEC_OP); }
	"!="                     { token(NE_OP); }
	"=="                     { token(EQ_OP); }
	"+="                     { token(ADD_ASSIGN); }
	"-="                     { token(SUB_ASSIGN); }
	"*="                     { token(MUL_ASSIGN); }
	"/="                     { token(DIV_ASSIGN); }
	"%="                     { token(MOD_ASSIGN); }
	"|="                     { token(OR_ASSIGN); }
	"&="                     { token(AND_ASSIGN); }
	"^="                     { token(XOR_ASSIGN); }
	"~="                     { token(NOT_ASSIGN); }
	"<<="                    { token(LEFT_ASSIGN); }
	">>="                    { token(RIGHT_ASSIGN); }
	":="                     { token(DECL_ASSIGN); }
	"="                      { token(ASSIGN); }
	"<<"                     { token(LEFT_OP); }
	">>"                     { token(RIGHT_OP); }
	"<="                     { token(LE_OP); }
	">="                     { token(GE_OP); }
	*                        { walk(); return parser::symbol_type(parser::token_type(ctx.cursor[-1]&0xFF), ctx.loc); }
	%}

block_comment:
	%{
	// Block Comment
	"/*"                     { comment_scope++; goto block_comment; }
	"*/"                     { walk(); comment_scope--; if(!comment_scope) advance(init); goto block_comment; }
	"\r\n" | [\r\n]          { ctx.loc.lines();   advance(block_comment); }
	[\t\v\b\f ]              { ctx.loc.columns(); advance(block_comment); }
	end                        { token(BLOCK_COMMENT_ERROR); }
	*                        { goto block_comment; }
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
	void parse(const std::string& sourceCode, std::string debugName)
	{
		lexcontext ctx;
		ctx.cursor = sourceCode.c_str();
		ctx.loc.begin.filename = &debugName;
		ctx.loc.end.filename   = &debugName;

		yy::parser parser(ctx);
		parser.parse();
	}
}
