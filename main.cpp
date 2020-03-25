#include <fstream>
#include <iostream>

using namespace std;

ifstream in("linkedlist.in");
ofstream out("linkedlist.out");

class Node {
    int info;
    Node *next, *prev;
public:
    Node() {
        next = nullptr;
        prev = nullptr;
        info = 0;
    }

    Node(int val) {
        next = nullptr;
        prev = nullptr;
        info = val;
    }

    ~Node() {}

    void setValue(int val) { info = val; }

    void setNext(Node *n) { next = n; }

    void setPrev(Node *n) { prev = n; }

    Node *getNext() { return next; }

    Node *getPrev() { return prev; }

    int getValue() { return info; }
};

class DoublyLinkedList {
    int len;
    Node *head, *tail;
public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        len = 0;
    }

    ~DoublyLinkedList() {}

    void addNode(int pos, int val) {
        Node *p = new Node;
        p->setValue(val);
        if (head == nullptr) {
            head = p;
            tail = p;
            len = 1;
            return;
        }
        if (pos > len) {
            tail->setNext(p);
            p->setPrev(tail);
            tail = p;
            len++;
            return;
        }
        if (pos <= 1) {
            head->setPrev(p);
            p->setNext(head);
            head = p;
            len++;
            return;
        } else {
            Node *prev = head;
            Node *next = head->getNext();
            for (int i = 1; i < pos - 1; i++) {
                prev = next;
                next = next->getNext();
            }
            prev->setNext(p);
            next->setPrev(p);
            p->setPrev(prev);
            p->setNext(next);
            len++;
        }
    }

    void removeNode(int pos) {
        if (head == nullptr) {
            out << "Underflow \n";
            return;
        }
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
            len = 0;
            return;
        }
        if (pos >= len) {
            Node *p = tail->getPrev();
            p->setNext(nullptr);
            tail = p;
            len--;
            return;
        }
        if (pos <= 1) {
            Node *p = head->getNext();
            p->setPrev(nullptr);
            head = p;
            len--;
            return;
        } else {
            Node *prev = head;
            Node *next = head->getNext();
            for (int i = 1; i < pos - 1; i++) {
                prev = next;
                next = next->getNext();
            }
            next = next->getNext();
            prev->setNext(next);
            next->setPrev(prev);
            len--;
        }
    }

    void displayList() {
        if (head != nullptr) {
            Node *p = new Node;
            p = head;
            while (p != nullptr) {
                int val = p->getValue();
                cout << val << " ";
                p = p->getNext();
            }
            cout << "len " << len << '\n';
        } else
            cout << "len 0 \n";
    }

    int getLen() { return len; }

    Node *getHead() { return head; }
    void setHead(Node* node){head=node;}
    Node *getTail() { return tail; };
    void setTail(Node* node){tail=node;}

    int lastVal() { return tail->getValue(); }

    friend istream &operator>>(istream &i, DoublyLinkedList &li);

    friend ostream &operator<<(istream &o, DoublyLinkedList &li);

    friend DoublyLinkedList operator+(DoublyLinkedList list1, DoublyLinkedList list2);

};

istream &operator>>(istream &i, DoublyLinkedList &li) {
    int val;
    i >> val;
    li.addNode(li.getLen() + 1, val);
    return i;
}

ostream &operator<<(ostream &o, DoublyLinkedList &li) {
    if (li.getHead() != nullptr) {
        Node *p = new Node;
        p = li.getHead();
        while (p != nullptr) {
            o << p->getValue() << " ";
            p = p->getNext();
        }
        o << "len " << li.getLen() << '\n';

        Node *p2 = new Node;
        p2 = li.getTail();
        while (p2 != nullptr) {
            o << p2->getValue() << " ";
            p2 = p2->getPrev();
        }
        o << "len " << li.getLen() << '\n';
    } else
        o << "len 0 \n";
    return o;

}

DoublyLinkedList operator+(DoublyLinkedList list1, DoublyLinkedList list2) {

    DoublyLinkedList list3;
    Node *p= new Node;

    p=list1.getHead();
    while(p!= nullptr)
    {
        list3.addNode(list3.getLen()+1,p->getValue());
        p=p->getNext();
    }
    p=list2.getHead();
    while(p!= nullptr)
    {
        list3.addNode(list3.getLen()+1,p->getValue());
        p=p->getNext();
    }
    return list3;
}

int main() {
    DoublyLinkedList lista1,lista2,lista3;
    int x = 0;

    for (int i = 1; i <= 4; i++) {
        lista1.addNode(i, i);
    }

    for (int i = 5; i <= 8; i++) {
        lista2.addNode(i, i);
    }
    lista1.displayList();
    lista2.displayList();
    lista3.displayList();

    lista3=lista2+lista1;

    lista1.displayList();
    lista2.displayList();
    lista3.displayList();


    cout << lista1;

    while (cin >> lista1 && lista1.lastVal() != 0) {
        cout << lista1;
    }
    cout << lista1;





    return 0;
}