#ifndef ast_h
#define ast_h
#include <map>
#include <variant>
#include <regex>


#endif

class VariableStorage {

private:
    std::map<std::string, int> m;
    
public:
    
    VariableStorage() {m = std::map<std::string, int>();}
    
    VariableStorage(std::map<std::string, int> map): m (map){}
    
    bool doesVariableExist(std::string var) {
        if(m.find(var) != m.end()) {
            return true;
        }
        return false;
    }
    
    int findVariableValue(std::string variable) {
        return m[variable];
    }
    
    void assignVariable(std::string var, int val) {
        m[var] = val;
    }
    
    bool isExpAVariable(std::string s) {
        for(int i = 0; i < s.length(); i++) {
            if (isdigit(s[i]) == true){
                return false;
            }
        }
        
        if(doesVariableExist(s)) {
            return true;
        }
        return false;
    }

};

struct Expression {
public:
  virtual ~Expression () {}
    virtual std::string toString () = 0;
    bool shouldPrint = true;
    virtual int evaluate (VariableStorage& manager) = 0;

};

// For numbers
class Number : public Expression {
    int m_val;
    bool shouldPrint = false;

public:
   
    Number (int val): m_val (val) {}

    virtual std::string toString () { return std::to_string(m_val); }
    virtual int evaluate (VariableStorage& manager) {
        return m_val;
        
    };
    
};

// For identifiers
class Ident : public Expression {
    std::string *m_val;
    bool shouldPrint = false;

public:
   
    Ident (std::string *val): m_val (val) {
        //std::cout << *val << std::endl;
        //std::cout << *m_val;
    }

    virtual std::string toString () { return *m_val;}
    virtual int evaluate (VariableStorage& manager) {
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
    bool shouldPrint = true;
    
private:
    
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
    virtual int evaluate (VariableStorage& manager) {
        int left;
        int right;
        
        
        if(manager.isExpAVariable(m_left->toString())) {
            left = manager.findVariableValue(m_left->toString());
        } else {
            left = m_left->evaluate(manager);
        }
        
        if(manager.isExpAVariable(m_right->toString())) {
            right = manager.findVariableValue(m_right->toString());
        }else {
            right = m_right->evaluate(manager);
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
    bool shouldPrint = true;
    
public:
   
    Unary (Expression *right, char oper): m_oper (oper), m_right (right) {}


    virtual std::string toString () {
        if (m_oper == '+') {
            return m_right->toString ();
        } else {
            return "-" + m_right->toString ();
        }
        
    }
    
    
    virtual int evaluate (VariableStorage& manager) {
        
        int right;
        
        if(manager.isExpAVariable(m_right->toString())) {
            right = manager.findVariableValue(m_right->toString());
        }else {
            right = m_right->evaluate(manager);
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
    bool shouldPrint = false;

public:
   
    Assign (std::string *var, Expression *right): m_var (var), m_right (right)  {
        }


    virtual std::string toString () {
        return *m_var + "=" + m_right->toString();
        
    }
    virtual int evaluate (VariableStorage& manager) {
        int h = m_right->evaluate(manager);
        manager.assignVariable(*m_var, h);
        return 0;
        
    };
    
    
    
};
