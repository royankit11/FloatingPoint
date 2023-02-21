#ifndef ast_h
#define ast_h
#include <map>
#include <variant>
#include <regex>


#endif

namespace VariableStorage {

    static std::map<std::string, int> m;

    static bool doesVariableExist(std::string var) {
        if(m.find(var) != m.end()) {
            return true;
        }
        return false;
    }
    
    static int findVariableValue(std::string variable) {
        return m[variable];
    }
    
    static void assignVariable(std::string var, int val) {
        m[var] = val;
    }
};

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
    virtual int evaluate () {
        return m_val;
        
    };
    
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
    virtual int evaluate () {
        /*if(m_map.find(*m_val) != m_map.end()) {
            return m_map[*m_val];
        } else {
            return 0;
        }*/
        return 0;
    };
};


// For binary expressions
class Binary : public Expression {
    Expression *m_left, *m_right;
    char m_oper;
    
private:
    bool isExpAVariable(std::string s) {
        for(int i = 0; i < s.length(); i++) {
            if (isdigit(s[i]) == true){
                return false;
            }
        }
        
        if(VariableStorage::doesVariableExist(s)) {
            return true;
        }
        return false;
    }

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
        int left;
        int right;
        
        
        if(isExpAVariable(m_left->toString())) {
            left = VariableStorage::findVariableValue(m_left->toString());
        } else {
            left = m_left->evaluate();
        }
        
        if(isExpAVariable(m_right->toString())) {
            right = VariableStorage::findVariableValue(m_right->toString());
        }else {
            right = m_right->evaluate();
        }
        
        
        
        
        if (m_oper == '+') {
            return left + right;
        } else if (m_oper == '*') {
            return left * right;
        } else if (m_oper == '-') {
            return left - right;
        } else {
            return left / right;
        }

    };
    
};
//unary expressions
class Unary : public Expression {
    Expression *m_right;
    char m_oper;
    
private:
    bool isExpAVariable(std::string s) {
        for(int i = 0; i < s.length(); i++) {
            if (isdigit(s[i]) == true){
                return false;
            }
        }
        
        if(VariableStorage::doesVariableExist(s)) {
            return true;
        }
        return false;
    }

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
        
        int right;
        
        if(isExpAVariable(m_right->toString())) {
            right = VariableStorage::findVariableValue(m_right->toString());
        }else {
            right = m_right->evaluate();
        }
        
        if (m_oper == '+') {
            return right;
        } else {
            return  0 - right;
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
    virtual int evaluate () {
        int h = m_right->evaluate();
        VariableStorage::assignVariable(*m_var, h);
        return 0;
        
    };
    
    
    
};
