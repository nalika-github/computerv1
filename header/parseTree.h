#ifndef PARSETREE_H
#define PARSETREE_H

#include <string>
#include <vector>
#include <memory>

// Forward declarations
class Node;
using NodePtr = std::shared_ptr<Node>;

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
    OperatorAdd,
    OperatorSub,
    OperatorMul,
    OperatorDiv,
    OperatorPow,
    OperandNumber,
    OperandVariable,
};

//-----------------------------------------------------
// Concrete node type: Binary tree node
//-----------------------------------------------------
class treeBinaryNode 
    : public Node
    , public std::enable_shared_from_this<treeBinaryNode> {

private:
    std::weak_ptr<Node> parent;
    NodePtr left;
    NodePtr right;
    NodeType type;
    std::string value;

    // Private constructor — only callable by factory
    explicit treeBinaryNode(const std::string& val, NodeType t = NodeType::Empty)
        : parent(), left(nullptr), right(nullptr), type(t), value(val) {}

public:
    treeBinaryNode(const treeBinaryNode& other) = default;
    treeBinaryNode(treeBinaryNode&& other) noexcept = default;
    treeBinaryNode& operator=(const treeBinaryNode& other) = default;
    treeBinaryNode& operator=(treeBinaryNode&& other) noexcept = default;
    ~treeBinaryNode() override = default;

    // Factory method (safe shared_ptr creation)
    static std::shared_ptr<treeBinaryNode> create(
        const std::string& val,
        NodeType t = NodeType::Empty)
    {
        return std::shared_ptr<treeBinaryNode>(new treeBinaryNode(val, t));
    }

    // Convert tree to string (recursive)
    std::string toString() const override {
        std::ostringstream oss;
        if (left)  oss << "(" << left->toString() << ")";
        oss << value;
        if (right) oss << "(" << right->toString() << ")";
        return oss.str();
    }

    // Create child node (left/right)
    NodePtr createChild(const std::string& val, NodeType t, bool isLeft) {
        auto child = treeBinaryNode::create(val, t);
        child->parent = shared_from_this();

        if (isLeft)
            left = child;
        else
            right = child;

        return child;
    }

    // Accessors (Getter / Setter)
    NodePtr getLeft() const { return left; }
    NodePtr getRight() const { return right; }
    NodeType getType() const { return type; }
    std::string getValue() const { return value; }

    void setLeft(NodePtr node) { left = node; }
    void setRight(NodePtr node) { right = node; }
    void setType(NodeType t) { type = t; }
    void setValue(const std::string& v) { value = v; }
};

#endif // PARSETREE_H