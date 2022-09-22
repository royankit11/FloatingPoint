%{
  #include <iostream>
  #include <cctype>
  #include <cstring>
  #include <vector>
  #include <stack>

  #include "ast.h"

  // Bring the standard library into the
  // global namespace
  using namespace std;

  // Prototypes to keep the compiler happy
  void yyerror (const char *error);
  int  yylex ();
  void clear_stack ();
  
  // Variables
  int vars ['Z'- 'A' + 1];

  // stack class that takes care of all the nodes that were allocated
  //stack <Expression *> nodes;
  vector<Expression *> nodes;
%}

%token IDENT NUMBER

%union {
  Expression *exp;  /* For the expressions. Since it is a pointer, no problem. */
  int       value;  /* For the lexical analyser. NUMBER tokens */
  std::string     *ident;  /* For the lexical analyser. IDENT tokens */
}

/* Lets inform Bison about the type of each terminal and non-terminal */
%type <exp>   exp
%type <value> NUMBER
%type <ident> IDENT

/* Precedence information to resolve ambiguity */
%left '+' '-'
%left '*' '/'
%%

prompt : exp  '\n'              {
                                  }
        |  prompt  exp  '\n'    {
                                }
       | error '\n'            { clear_stack (); }
       ;

exp : IDENT                    {
                                $$ = new Ident($1);
                                nodes.push_back($$);
                                }
    | NUMBER                   { $$ = new Number ($1);
                                
                                }
    | exp '+' exp              {
                                 $$ = new Binary ($1, '+', $3);
                                 nodes.push_back ($$);
                               }
    | exp '*' exp              {
                                 $$ = new Binary ($1, '*', $3);
                                 nodes.push_back ($$);
                                }
    | exp '-' exp              {
                                  $$ = new Binary ($1, '-', $3);
                                  nodes.push_back ($$);
                               }
    | exp '/' exp              {
                                  $$ = new Binary ($1, '/', $3);
                                  nodes.push_back ($$);
                               }
    | '+' exp                  {
                                  $$ = new Unary ($2, '+');
                                  nodes.push_back ($$);
                               }
    | '-' exp                  {
                                  $$ = new Unary ($2, '-');
                                  nodes.push_back ($$);
                               }
    | IDENT '=' exp            {
                                  $$ = new Assign ($1, $3);
                                  nodes.push_back ($$);
                               }
    ;
%%

// we need to provid the following functions
int main ()
{
  memset (vars, 0, sizeof (vars));
  return yyparse ();


}

void yyerror (const char *error)
{
  cout << error << endl;
}

int yylex ()
{
  char ch;

  do {
      
   ch = cin.peek ();
   if (isalpha (ch)) {
       std::string identifier = "";
       while (!cin.eof () && isalpha (ch)) {
         cin.get ();

         identifier = identifier + std::string(1, ch);
         ch = cin.peek ();
       }
       
     yylval.ident = &identifier;

     return IDENT;
   }
   else if (isdigit (ch)) {
     int value = 0;
     while (!cin.eof () && isdigit (ch)) {
       cin.get ();

       value = value * 10 + ch - '0';
       ch = cin.peek ();
     }

     yylval.value = value;
     return NUMBER;
  }
  else if (ch == '+' || ch == '\n' || ch == '-' || ch == '/' ||ch == '*' || ch == '=') {
     cin.get ();
 
     return ch;
  } else if (cin.eof()) {
      for(int i = 0; i < nodes.size(); i++) {
          cout << nodes.at(i) -> evaluate() << endl;
      }
      nodes.clear();
      return YYEOF;
   }
  else
    cin.get ();

 } while (!cin.eof ());

 return -1;
}


// Deletes all the nodes that were allocated
void clear_stack ()
{
    nodes.clear();
}
