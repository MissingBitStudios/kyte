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
%token IDENTIFIER CONSTANT TYPE_NAME
%token ATTRIBUTE "attribute" UNIFORM "uniform" SAMPLER "sampler"
%token IMPORT "import"
%token INC_OP "++" DEC_OP "--"
%token AND_OP "&&" OR_OP "||" EQ_OP "==" NE_OP "!=" LE_OP "<=" GE_OP ">="
%token MUL_ASSIGN "*=" DIV_ASSIGN "/=" MOD_ASSIGN "%=" ADD_ASSIGN "+=" SUB_ASSIGN "-="
%token LEFT_OP "<<" RIGHT_OP ">>"
%token LEFT_ASSIGN "<<=" RIGHT_ASSIGN ">>=" AND_ASSIGN "&="
%token XOR_ASSIGN "^=" OR_ASSIGN "|=" NOT_ASSIGN "~="
%token TYPEDEF "typedef" EXTERN "extern" OPERATOR "operator" CONST "const"
%token INT "int" UINT "uint" FLOAT "float" DOUBLE "double" BOOL "bool" VOID "void"
%token STRUCT "struct" ENUM "enum"
%token ELLIPSIS "..." ARROW "->"
%token CASE "case" DEFAULT "default" IF "if" ELSE "else" SWITCH "switch"
%token WHILE "while" DO "do" FOR "for"
%token CONTINUE "continue" BREAK "break" RETURN "return" DISCARD "discard"

%type<std::string> IDENTIFIER

%start translation_unit

%%

primary_expression
	: IDENTIFIER
	| CONSTANT
	| '(' expression ')'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	| postfix_expression "++"
	| postfix_expression "--"
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| "++" unary_expression
	| "--" unary_expression
	| unary_operator cast_expression
	;

unary_operator
	: '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression "<<" additive_expression
	| shift_expression ">>" additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression "<=" shift_expression
	| relational_expression ">=" shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression "==" relational_expression
	| equality_expression "!=" relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression "&&" inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression "||" logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: '='
	| "*="
	| "/="
	| "%="
	| "+="
	| "-="
	| "<<="
	| ">>="
	| "&="
	| "^="
	| "|="
	| "~="
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| "const"
	| "const" declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

storage_class_specifier
	: "typedef"
	| "extern"
	;

type_list_specifier
	: '<' type_list '>'
	;

type_list
	: type_name
	| type_list ',' type_name
	;

type_specifier
	: "void"
	| "int"
	| "uint"
	| "float"
	| "double"
	| "bool"
	| struct_specifier
	| enum_specifier
	| type_list_specifier
	| IDENTIFIER
	;

struct_specifier
	: "struct" IDENTIFIER '{' struct_declaration_list '}'
	| "struct" '{' struct_declaration_list '}'
	| "struct" IDENTIFIER
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| "const" specifier_qualifier_list
	| "const"
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: "enum" '{' enumerator_list '}'
	| "enum" IDENTIFIER '{' enumerator_list '}'
	| "enum" IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

declarator
	: direct_declarator
	;

direct_declarator
	: type_specifier
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
	;

parameter_type_list
	: parameter_list
	| parameter_list ',' "..."
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: "case" constant_expression ':' statement
	| "default" ':' statement
	;

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
	: "if" '(' expression ')' statement
	| "if" '(' expression ')' statement "else" statement
	| "switch" '(' expression ')' statement
	;

iteration_statement
	: "while" '(' expression ')' statement
	| "do" statement "while" '(' expression ')' ';'
	| "for" '(' expression_statement expression_statement ')' statement
	| "for" '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: "continue" ';'
	| "break" ';'
	| "return" ';'
	| "return" expression ';'
	| "discard"
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

%%

/*!types:re2c*/

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
	"typedef"                { token(TYPEDEF); }
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
	"extern"                 { token(EXTERN); }
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
	[a-zA-Z_] [a-zA-Z_0-9]*  { tokenv(IDENTIFIER, std::string(anchor, ctx.cursor)); }

	// Literals
	[0-9]+ [f]               { token(CONSTANT); }
	[0-9]+                   { token(CONSTANT); }

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
