/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
  if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
    YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern YYSTYPE cool_yylval;

int nested_comment;
int str_len;
char a_string[4096];

%}

%option noyywrap

/*
 * Define names for regular expressions here.
 */

digit       [0-9]
character 	[0-9A-Z_a-z]
white_space [\f\r\t\v ]
%x COMMENT 
%x STRING

%%

 /*
  * Define regular expressions for the tokens of COOL here. Make sure, you
  * handle correctly special cases, like:
  *   - Nested comments
  *   - String constants: They use C like systax and can contain escape
  *     sequences. Escape sequence \c is accepted for all characters c. Except
  *     for \n \t \b \f, the result is c.
  *   - Keywords: They are case-insensitive except for the values true and
  *     false, which must begin with a lower-case letter.
  *   - Multiple-character operators (like <-): The scanner should produce a
  *     single token for every such operator.
  *   - Line counting: You should keep the global variable curr_lineno updated
  *     with the correct line number
  */

"(*" {
	nested_comment = 1;
	BEGIN(COMMENT);
}
<COMMENT>"(*" nested_comment++;
<COMMENT>. {}
<COMMENT>"\n" curr_lineno++;
<COMMENT><<EOF>> {
	BEGIN(INITIAL);
	cool_yylval.error_msg = "EOF in the comment";
	return(ERROR);
}
<COMMENT>"*)" {
	nested_comment--;
	if(nested_comment == 0){
		BEGIN(INITIAL);
	}
}

"*)" {
	cool_yylval.error_msg = "unmatched *)";
	return(ERROR);
}

"--".*"\n" curr_lineno++;

"\"" {
	BEGIN(STRING);
	str_len = 0;
}
<STRING>"\"" {
	BEGIN(INITIAL);
	cool_yylval.symbol = inttable.add_string(a_string, str_len);
	return(STR_CONST);
}
<STRING>\n {
	BEGIN(INITIAL);
	curr_lineno++;
	cool_yylval.error_msg = "Unterminated string constant";
	return(ERROR);
}
<STRING>EOF {
	BEGIN(INITIAL);
	cool_yylval.error_msg = "EOF in string constant";
	return(ERROR);
}
<STRING>\0 {
	BEGIN(INITIAL);
	cool_yylval.error_msg = "String contains invalid character";
	return(ERROR);
}
<STRING>\\\n {
	curr_lineno++;
	if(str_len > 1024){
		BEGIN(INITIAL);
		cool_yylval.error_msg = "String constant too long";
		return(ERROR);
	}
	a_string[str_len++] = '\n';
}
<STRING>\\n {
	if(str_len > 1024){
		BEGIN(INITIAL);
		cool_yylval.error_msg = "String constant too long";
		return(ERROR);
	}
	a_string[str_len++] = '\n';
}
<STRING>\\b {
	if(str_len > 1024){
		BEGIN(INITIAL);
		cool_yylval.error_msg = "String constant too long";
		return(ERROR);
	}
	a_string[str_len++] = '\b';
}
<STRING>\\t {
	if(str_len > 1024){
		BEGIN(INITIAL);
		cool_yylval.error_msg = "String constant too long";
		return(ERROR);
	}
	a_string[str_len++] = '\t';
}
<STRING>\\f {
	if(str_len > 1024){
		BEGIN(INITIAL);
		cool_yylval.error_msg = "String constant too long";
		return(ERROR);
	}
	a_string[str_len++] = '\f';
}
<STRING>\\. {
	if(str_len > 1024){
		BEGIN(INITIAL);
		cool_yylval.error_msg = "String constant too long";
		return(ERROR);
	}
	a_string[str_len++] = yytext[1];
}
<STRING>. {
	if(str_len > 1024){
		BEGIN(INITIAL);
		cool_yylval.error_msg = "String constant too long";
		return(ERROR);
	}
	a_string[str_len++] = yytext[0];
}



(?i:class) 		return(CLASS);
(?i:else) 		return(ELSE);
(?i:fi) 		return(FI);
(?i:if) 		return(IF);
(?i:in) 		return(IN);
(?i:inherits) 	return(INHERITS);
(?i:isvoid) 	return(ISVOID);
(?i:let) 		return(LET);
(?i:loop) 		return(LOOP);
(?i:pool) 		return(POOL);
(?i:then) 		return(THEN);
(?i:while) 		return(WHILE);
(?i:case) 		return(CASE);
(?i:esac) 		return(ESAC);
(?i:new) 		return(NEW);
(?i:of) 		return(OF);
(?i:not) 		return(NOT);

t(?i:rue) {
	cool_yylval.boolean = true;
	return(BOOL_CONST);
}

f(?i:alse) {
	cool_yylval.boolean = false;
	return(BOOL_CONST); 
}

"<-" return(ASSIGN);
"=>" return(DARROW);
"<=" return(LE);
"+" return '+';
"-" return '-';
"*" return '*';
"/" return '/';
"(" return '(';
")" return ')';
"=" return '=';
"<" return '<';
"@" return '@';
"," return ',';
"." return '.';
"~" return '~';
":" return ':';
";" return ';';
"{" return '{';
"}" return '}';


{digit}+ {
	cool_yylval.symbol = inttable.add_string(yytext, yyleng);
	return(INT_CONST);
}

[A-Z]{character}* {
	cool_yylval.symbol = inttable.add_string(yytext, yyleng);
	return(TYPEID);
}

[a-z]{character}* {
	cool_yylval.symbol = inttable.add_string(yytext, yyleng);
	return(OBJECTID);
}

"\n" {
	curr_lineno++;
}

{white_space}+ {}

. {
	cool_yylval.error_msg = "NULL character in the string";
	return(ERROR);
}

%%
