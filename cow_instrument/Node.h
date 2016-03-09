#ifndef NODE_H
#define NODE_H

#include "cow_ptr.h"
#include <memory>
#include <tuple>

class Component;
class Command;

/**
 * To give us a way of reusing components, and simply updating the association
 *without having
 * to deepcopy the components.
 *
 * Components do not know about Nodes
 */

class Node {
public:
  Node(std::shared_ptr<Node> previous, std::shared_ptr<Node> next,
       CowPtr<Component> contents);

  Node(std::shared_ptr<Node> previous, CowPtr<Component> contents);

  Node(CowPtr<Component> contents);

  ~Node();

  // What this will return is the new root node (instrument) with the command applied.
  std::shared_ptr<Node> modify(const Command &command);

  bool hasParent() const;

  bool hasChild() const;

  void addChild(std::shared_ptr<Node> child);

  std::shared_ptr< Node>  child();
  std::shared_ptr< Node>  parent();
  CowPtr<Component> contents();

private:
  Node *  parentPtr();

  void doModify(const Command &command);

  std::shared_ptr<Node> smartCopy(const Command &command,
                                                                          const Component &component,
                                                                          std::shared_ptr<Node> &newPrevious) const;

  std::shared_ptr<Node> m_previous; // parent
  std::shared_ptr<Node> m_next;     // Child
  CowPtr<Component> m_contents;
};

using Node_sptr = std::shared_ptr<Node>;
using Node_const_sptr = std::shared_ptr<const Node>;

#endif
