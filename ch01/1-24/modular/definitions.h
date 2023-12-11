#define MAXCHARS 1000
#define MAXLINES 1000
#define MAXFILENAME 100
#define IN 0  // are we in a comment?
#define OUT 1 // are we out of a comment?
#define YES 1
#define NO 0

extern int linecountinput = 0;			// keep track of what line we are on in our string array while copying input file to it
extern int howlongisthisline[MAXLINES];		// for each line, how long is it

extern int line = 0;				// line stores what line we are on when iterating through the program
extern int column = 0;				// column stores what character we are on when iterating through the program
extern char program[MAXLINES][MAXCHARS];	// array of strings we will store the file with comments in

extern int areweinastring = OUT;		// are we in a string
extern int stringliteral = OUT;			// keep track of whether we're " " quotes
extern int charliteral = OUT;			// keep track of whether we're in ' ' quotes

extern int weare__acomment = OUT;		// keep track of whether we're in a comment
extern int weare__asinglelinecomment = OUT;	// keep track of whether we're on a single comment so we can reset it on the next line
extern int didweescapenewline = NO;		// keep track of whether someone put a \ escape character before hitting enter to escape a newline. 

/*the parenthesis[] array keeps track of whether parenthesis are balanced. let parenthesis[0] be the
first parenthesis. When an ( is found, parenthesis[0]++ will occur, which brings it to 1. If a ) shows up,
parenthesis[0]-- will happen, which brings it to a 0. If any of these is a 1, or a negative one,
it means that parenthesis is out of balance, and should be looked at. Same for arrays for other character types */

extern int parencount = 0;			// parencount stores which parenthesis we are on
extern int parenclosecount = 0;			// parencount stores which EXCESS closed parenthesis we are on
extern int maxparenthesis = 0;			// the highest number of parenthesis we opened as we count up
extern int maxextraclosedparenthesis = 0;	// the highest number of EXCESS closed parenthesis
extern int parenthesis[MAXCHARS] = {0};		// array for storing whether parenthesis are balanced - should ++ when there is an open parenthesis, and -- when there is a closed parenthesis
extern int extra_closed_parenthesis[MAXCHARS] = {0};   // array for storing how many extra closed parenthesis there are
extern int location_parenopen_column[MAXCHARS] = {0};  // array for storing column of opening parenthesis
extern int location_parenopen_line[MAXLINES] = {0};    // array for storing line of opening parenthesis
extern int location_parenclose_column[MAXCHARS] = {0}; // array for storing column of closing parenthesis
extern int location_parenclose_line[MAXLINES] = {0};   // array for storing column of closing parenthesis

extern int curlycount = 0;			// curlycount stores which curly braces we are on
extern int curlyclosecount = 0;			// curlyclosecount stores which EXCESS closed curlybraces we are on
extern int maxcurly = 0;				// the highest number of curly braces we opened as we count up
extern int maxextraclosedcurlybraces = 0;		// the highest number of EXCESS closed curly braces
extern int curlybraces[MAXCHARS] = {0};			// array for storing whether curly braces are balanced - should ++ when there is an open curly brace, and -- when there is a closed curlybrace
extern int extra_closed_curlybraces[MAXCHARS] = {0};	// array for storing how many extra closed curlybraces there are
extern int location_curlyopen_column[MAXCHARS] = {0};	// array for storing column of opening curly braces
extern int location_curlyopen_line[MAXLINES] = {0};	// array for storing line of opening curly braces
extern int location_curlyclose_column[MAXCHARS] = {0};	// array for storing column of closing curly braces
extern int location_curlyclose_line[MAXLINES] = {0};	// array for storing column of closing curly braces

extern int bracketcount = 0;				// bracketcount stores which brackets we are on
extern int bracketclosecount = 0;			// bracketclosecount stores which EXCESS closed brackets we are on
extern int maxbracket = 0;				// the highest number of brackets we opened as we count up
extern int maxextraclosedbrackets = 0;			// the highest number of EXCESS closed brackets
extern int brackets[MAXCHARS] = {0};			// array for storing whether brackets are balanced - should ++ when there is an open bracket brace, and -- when there is a closed bracketbrace
extern int extra_closed_brackets[MAXCHARS] = {0};	// array for storing how many extra closed brackets there are
extern int location_bracketopen_column[MAXCHARS] = {0};	// array for storing column of opening brackets
extern int location_bracketopen_line[MAXLINES] = {0};	// array for storing line of opening brackets
extern int location_bracketclose_column[MAXCHARS] = {0};// array for storing column of closing brackets
extern int location_bracketclose_line[MAXLINES] = {0};	// array for storing column of closing brackets

extern int quotecount = 0;				// quotecount stores which quotes we are on
extern int quoteclosecount = 0;				// quoteclosecount stores which EXCESS closed quotes we are on
extern int maxquote = 0;				// the highest number of quotes we opened as we count up
extern int maxextraclosedquotes = 0;			// the highest number of EXCESS closed quotes
extern int quotes[MAXCHARS] = {0};			// array for storing whether quotes are balanced - should ++ when there is an open quote, and -- when there is a closed quote
extern int extra_closed_quotes[MAXCHARS] = {0};		// array for storing how many extra closed quotes there are
extern int location_quoteopen_column[MAXCHARS] = {0};	// array for storing column of opening quotes
extern int location_quoteopen_line[MAXLINES] = {0};	// array for storing line of opening quotes
extern int location_quoteclose_column[MAXCHARS] = {0};	// array for storing column of closing quotes
extern int location_quoteclose_line[MAXLINES] = {0};	// array for storing column of closing quotes
