#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <string>

class LinkedList {
  private:
    struct Link {
        unsigned m_uiData;
        Link *m_pNext;
        Link(unsigned uiData, Link *pNext = nullptr);
    } *m_pHead;

  public:
    LinkedList(Link *pHead = nullptr);
    ~LinkedList();
    std::string getDataString() const;
    bool insert(unsigned uiData);
    bool remove(unsigned &pData);
    void makeEmpty();
    // I left this function declaration here for grading
    // void print(std::ostream &out = std::cout) const;
};

std::ostream &operator<<(std::ostream &, const LinkedList &);

#endif /* LINKED_LIST_H */ 
