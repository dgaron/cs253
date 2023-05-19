#include "ll.h" 
#include <cstdlib>


// Link constructor
LinkedList::Link::Link(unsigned uiData, Link *pNext) : m_uiData(uiData),
                                                       m_pNext(pNext) {
}

// LinkedList constructor
LinkedList::LinkedList(Link *pHead) : m_pHead(pHead) {
}

// LinkedList destructor
LinkedList::~LinkedList() {
    makeEmpty();				// Remove and free all nodes
}

std::string LinkedList::getDataString() const {
    std::string s;
    std::string separator = "";
    LinkedList::Link *current = m_pHead;
    while (current) {
        s += separator;
        s += std::to_string(current->m_uiData);
        separator = " ";
        current = current->m_pNext;
    }
    s += '\n';
    return s;
}

bool LinkedList::insert(unsigned uiData) {
    Link *new_link = new Link(uiData, m_pHead);	// Get a new node.
    m_pHead = new_link;				// Put it at the head.

    return true;				// Indicate success.
}

bool LinkedList::remove(unsigned &pData) {
    if (!m_pHead)				// Empty list?
	return false;				// Indicate failure.

    Link *temp = m_pHead;			// Point to the first node.
    m_pHead = m_pHead->m_pNext;			// Remove the first node.
    pData = temp->m_uiData;			// Obtain first node’s data.
    delete(temp);				// Free memory from removed node

    return true;				// Indicate success.
}

void LinkedList::makeEmpty() {
    while (m_pHead) {
        remove(m_pHead->m_uiData);
    }
}

/* I left the original print() method in place for grading
void LinkedList::print(std::ostream &out) const {
    std::string s;
    std::string separator = "";
    Link *current = m_pHead;
    while (current) {
        s += separator;
        s += std::to_string(current->m_uiData);
        separator = " ";
        current = current->m_pNext;
    }
    out << s << '\n';				// Newline per the instructions
}
*/

std::ostream &operator<<(std::ostream &out, const LinkedList &myList) {
    return out << myList.getDataString();  
}
