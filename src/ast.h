//
//  ast.h
//  Parser
//
//  Created by Rik Roy on 7/29/22.
//

#ifndef ast_h
#define ast_h


#endif

class Expression {
public:
  virtual ~Expression () {}

  // The value represented by the expression
    virtual int value () = 0;
};

// For numbers
class Number : public Expression {
    int m_val;

    public:
   
        Number (int val): m_val (val) {}

        virtual int value () { return m_val; }
    };

// For identifiers
class Ident : public Expression {
    int m_val;

    public:
   
        Ident (int val): m_val (val) {}
  

        virtual int value () { return m_val; }
};


// For binary expressions
class Binary : public Expression {
    Expression *m_left, *m_right;
    char m_oper;

    public:
   
        Binary (Expression *left, char oper, Expression *right): m_left (left), m_oper (oper), m_right (right) {}

   
        virtual int value () {
            if (m_oper == '+') {
                return m_left->value () + m_right->value ();
            } else if (m_oper == '*') {
                return m_left->value () * m_right->value ();
            } else if (m_oper == '-') {
                return m_left->value () - m_right->value ();
            } else {
                return m_left->value () / m_right->value ();
            }
            
        }
    
};
//unary expressions
class Unary : public Expression {
    Expression *m_right;
    char m_oper;

    public:
   
        Unary (Expression *right, char oper): m_oper (oper), m_right (right) {}

   
        virtual int value () {
            if (m_oper == '+') {
                return m_right->value ();
            } else {
                return m_right->value ();
            }
            
        }
    
};


