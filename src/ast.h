#ifndef ast_h
#define ast_h


#endif

struct Expression {
public:
  virtual ~Expression () {}
    virtual std::string toString () = 0;
    virtual int evaluate () = 0;

};

// For numbers
class Number : public Expression {
    int m_val;

public:
   
    Number (int val): m_val (val) {}

    virtual std::string toString () { return std::to_string(m_val); }
    virtual int evaluate () {return m_val;};
    
};

// For identifiers
class Ident : public Expression {
    std::string *m_val;

public:
   
    Ident (std::string *val): m_val (val) {
        //std::cout << *val << std::endl;
        //std::cout << *m_val;
    }

    virtual std::string toString () { return *m_val;}
    virtual int evaluate () {return 0;};
};


// For binary expressions
class Binary : public Expression {
    Expression *m_left, *m_right;
    char m_oper;

public:
   
    Binary (Expression *left, char oper, Expression *right): m_left (left), m_oper (oper), m_right (right) {}


    virtual std::string toString () {
        if (m_oper == '+') {
            return m_left->toString () + "+" + m_right->toString ();
        } else if (m_oper == '*') {
            return m_left->toString () + "*" + m_right->toString ();
        } else if (m_oper == '-') {
            return m_left->toString () + "-" + m_right->toString ();
        } else {
            return m_left->toString () + "/" + m_right->toString ();
        }
        
    }
    virtual int evaluate () {
        if (m_oper == '+') {
            return m_right->evaluate() + m_left->evaluate();
        } else if (m_oper == '*') {
            return m_right->evaluate() * m_left->evaluate();
        } else if (m_oper == '-') {
            return m_right->evaluate() - m_left->evaluate();
        } else {
            return m_right->evaluate() / m_left->evaluate();
        }
        
    };
    
};
//unary expressions
class Unary : public Expression {
    Expression *m_right;
    char m_oper;

public:
   
    Unary (Expression *right, char oper): m_oper (oper), m_right (right) {}


    virtual std::string toString () {
        if (m_oper == '+') {
            return m_right->toString ();
        } else {
            return "-" + m_right->toString ();
        }
        
    }
    virtual int evaluate () {
        if (m_oper == '+') {
            return m_right->evaluate();
        } else {
            return  0 - + m_right->evaluate ();
        }
        
    };
    
};

class Assign : public Expression {
    std::string *m_var;
    Expression *m_right;

public:
   
    Assign (std::string *var, Expression *right): m_var (var), m_right (right)  {
        }


    virtual std::string toString () {
        return *m_var + "=" + m_right->toString();
        
    }
    virtual int evaluate () {return 0;};
    
};
