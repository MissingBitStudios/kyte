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

struct lexcontext
{
	const char* cursor;
	yy::location loc;
};

namespace yy { parser::symbol_type yylex(lexcontext& ctx); }
}//%code

%token END 0
%token BLOCK_COMMENT_ERROR
%token IDENTIFIER CONSTANT
%token ATTRIBUTE "attribute" UNIFORM "uniform" SAMPLER "sampler"
%token IMPORT "import"
%token INC_OP "++" DEC_OP "--"
%token AND_OP "&&" OR_OP "||" EQ_OP "==" NE_OP "!=" LE_OP "<=" GE_OP ">="
%token MUL_ASSIGN "*=" DIV_ASSIGN "/=" MOD_ASSIGN "%=" ADD_ASSIGN "+=" SUB_ASSIGN "-="
%token LEFT_OP "<<" RIGHT_OP ">>"
%token LEFT_ASSIGN "<<=" RIGHT_ASSIGN ">>=" AND_ASSIGN "&="
%token XOR_ASSIGN "^=" OR_ASSIGN "|=" NOT_ASSIGN "~="
%token OPERATOR "operator" CONST "const"
%token INT "int" UINT "uint" FLOAT "float" DOUBLE "double" BOOL "bool" VAR "var"
%token STRUCT "struct" ENUM "enum"
%token ELLIPSIS "..."
%token CASE "case" DEFAULT "default" IF "if" ELSE "else" SWITCH "switch"
%token WHILE "while" DO "do" FOR "for"
%token CONTINUE "continue" BREAK "break" RETURN "return" DISCARD "discard"
%type<std::string> IDENTIFIER

%start translation_unit

%%

// whole translation unit with import and functions
translation_unit
	: external_declaration  // variable declaration with or without tags
	;

// variables and functions
external_declaration
    : declaration           // e.g. x := 5;   OR   getX := () $ int { return x; };
    | tag declaration       // e.g. @private setX := (n : int) { x = n; };
    | external_declaration declaration
    | external_declaration tag declaration
    | END
	;

tag
    : '@' tag_word          // e.g. @inline
    | tag '@' tag_word
    ;

tag_word
    : "inline"
    | "iknowwhatiamdoing"
    | "private"
    | "export"  // implicitly defined unless @private tag is used
    | "vertex"
    | "fragment"
    | "geometry"
    | "compute"
    | "tesselation"
	;

// declarations for functions and variables
declaration
    : IDENTIFIER ':' type ';'                           // variable declaration
    | IDENTIFIER ':' type assignment_statement          // variable declaration and assignment (type stated)
    | IDENTIFIER ':' assignment_statement               // variable declaration and assignment (type implied)
    | CONST IDENTIFIER ':' type ';'                     // const declaration and assignment
    | CONST IDENTIFIER ':' type assignment_statement    // const declaration and assignment (type stated)
    | CONST IDENTIFIER ':' assignment_statement         // const declaration and assignment (type implied)
    ;

function_arguments
    : IDENTIFIER ':' type
    | IDENTIFIER ':' type ELLIPSIS
    | CONST IDENTIFIER ':' type
    | CONST IDENTIFIER ':' type ELLIPSIS
    | function_arguments ',' IDENTIFIER ':' type
    | function_arguments ',' IDENTIFIER ':' type ELLIPSIS
    | function_arguments ',' CONST IDENTIFIER ':' type
    | function_arguments ',' CONST IDENTIFIER ':' type ELLIPSIS
    ;

// any kind of statement
statement
	: compound_statement        // e.g. { ... }
	| expression_statement      // e.g. (x && y);
	| jump_statement            // e.g. return x;
    | declaration               // e.g. x := 5;
    | assignment_statement      // e.g. x = 5;
	;

assignment_statement
    : '=' expression_statement
    ;

// used for functions, if statements, loops, etc.
compound_statement
	: '{' '}'
	| '{' statement_list '}'
	;

// filler for statements and declarations
statement_list
    : statement
    | statement_list statement
    ;

expression_statement
	: ';'
	| expression ';'
	;

jump_statement
	: RETURN expression_statement      // e.g. return x;
	;

type
    : INT
    | FLOAT
    | UINT
    | DOUBLE
    | BOOL
    | VAR
    | function_type
    ;

function_type
    : '(' ')' '$'                           // used for void function declaration (no parameters)
    | '(' ')' '$' type                      // used for function declaration with return (no parameters)
    | '(' function_arguments ')' '$'        // used for void function declaration
    | '(' function_arguments ')' '$' type   // used for function declaration with return
    ;


// all the expression stuff below
expression
    : IDENTIFIER                    // e.g. x
    | CONSTANT                      // e.g. 5
    | function_call_expression      // e.g. setX(5.0)
    | function_decl_expression      // e.g. (n : int) { x = n; };
    ;

function_call_expression
    : IDENTIFIER '(' ')'                // function call
    | IDENTIFIER '(' argument_list ')'  // function call with parameters
    ;

argument_list
    : IDENTIFIER
    | CONSTANT
    | argument_list ',' IDENTIFIER
    | argument_list ',' CONSTANT
    ;

function_decl_expression
    : function_type compound_statement
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
