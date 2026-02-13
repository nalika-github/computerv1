#ifndef PARSETREE_H
#define PARSETREE_H

#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <sstream>
#include <map>

// Forward declarations
class Node;
using NodePtr = std::shared_ptr<Node>;
class ASTNode;
using ASTNodePtr = std::shared_ptr<ASTNode>;

//-----------------------------------------------------
// Base node class for parse tree
//-----------------------------------------------------
class Node {
public:
    virtual ~Node() = default;
    virtual std::string toString() const = 0;
};

//-----------------------------------------------------
// Enum class for node type
//-----------------------------------------------------
enum class NodeType {
    Empty,
    Operator,
    Term,
    Variable,
    Function
};

//-----------------------------------------------------
// Term structure for polynomial
//-----------------------------------------------------
struct Term {
    double coeff;
    int degree;

    Term(double c = 0.0, int d = 0) : coeff(c), degree(d) {}
};

using Polynomial = std::map<int, double>;

using NodeValue = std::variant<
    std::monostate,
    std::string,
    Term
>;

class ASTNode : public Node, public std::enable_shared_from_this<ASTNode> {
public:
    NodeType type;
    NodeValue value;
    std::vector<NodePtr> children;
    std::weak_ptr<Node> parent;

    static ASTNodePtr create(NodeType nodeType, const NodeValue& nodeValue = NodeValue{}) {
        ASTNodePtr node(new ASTNode());
        node->type = nodeType;
        node->value = nodeValue;
        return node;
    }

    void addChild(const NodePtr& child) {
        children.push_back(child);
        std::shared_ptr<ASTNode> childNode = std::dynamic_pointer_cast<ASTNode>(child);
        if (childNode) {
            childNode->parent = shared_from_this();
        }
    }

    std::string toString() const override {
        std::ostringstream oss;

        if (std::holds_alternative<std::string>(value)) {
            oss << std::get<std::string>(value);
        } else if (std::holds_alternative<Term>(value)) {
            const Term& term = std::get<Term>(value);
            oss << term.coeff << "X^" << term.degree;
        } else {
            oss << "_";
        }

        if (!children.empty()) {
            oss << "(";
            for (size_t i = 0; i < children.size(); ++i) {
                oss << children[i]->toString();
                if (i + 1 < children.size()) {
                    oss << ",";
                }
            }
            oss << ")";
        }
        return oss.str();
    }

private:
    ASTNode() : type(NodeType::Empty), value(std::monostate{}) {}
};

#endif // PARSETREE_H