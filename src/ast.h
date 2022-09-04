#ifndef ast_h
#define ast_h


#endif

struct Expression {
public:
  virtual ~Expression () {}
    virtual std::string evaluate () = 0;

  // The value represented by the expression

    //virtual std::string repeat () = "";
};

// For numbers
class Number : public Expression {
    int m_val;

public:
   
    Number (int val): m_val (val) {}

    virtual  std::string evaluate () { return std::to_string(m_val); }
};

// For identifiers
class Ident : public Expression {
    std::string *m_val;

public:
   
    Ident (std::string *val): m_val (val) {
        //std::cout << *val << std::endl;
        //std::cout << *m_val;
    }

    virtual std::string evaluate () { return *m_val;}
};


// For binary expressions
class Binary : public Expression {
    Expression *m_left, *m_right;
    char m_oper;

public:
   
    Binary (Expression *left, char oper, Expression *right): m_left (left), m_oper (oper), m_right (right) {}


    virtual std::string evaluate () {
        if (m_oper == '+') {
            return m_left->evaluate () + "+" + m_right->evaluate ();
        } else if (m_oper == '*') {
            return m_left->evaluate () + "*" + m_right->evaluate ();
        } else if (m_oper == '-') {
            return m_left->evaluate () + "-" + m_right->evaluate ();
        } else {
            return m_left->evaluate () + "/" + m_right->evaluate ();
        }
        
    }
    
};
//unary expressions
class Unary : public Expression {
    Expression *m_right;
    char m_oper;

public:
   
    Unary (Expression *right, char oper): m_oper (oper), m_right (right) {}


    virtual std::string evaluate () {
        if (m_oper == '+') {
            return m_right->evaluate ();
        } else {
            return "-" + m_right->evaluate ();
        }
        
    }
    
};
