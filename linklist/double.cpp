#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class doubleLinkLish {
    struct Node
    {
        T val;
        Node *prev;
        Node *next;

        Node(T val) : val(val), prev(nullptr), next(nullptr) {} 
    };

    Node *head;
    Node *tail;
    int size;

public:
    doubleLinkLish() {
        head = new Node(T());
        tail = new Node(T());
        head->next = tail;
        tail->prev = head;
        size = 0;
    }

    ~doubleLinkLish() {
        while (size > 0) {
            removeFirst();
        }
        delete head;
        delete tail;
    }

    // ***** 增 *****

    void addLast(T val) {
        Node *p = tail->prev;
        Node *newNode = new Node(val);
        p->next = newNode;
        newNode->prev = p;
        newNode->next = tail;
        tail->prev = newNode;
        size ++;
    }

    void addFirst(T val) {
        Node *p = head->next;
        Node *newNode = new Node(val);

        p->prev = newNode;
        newNode->prev = head;
        newNode->next = p;
        head->next = newNode;
        size ++;
    }

    void add(int index, T val) {
        checkPositionIndex(index);
        if (index == size)
        {
            addLast(val);
            return;
        }

        Node *p = getNode(index);
        Node *temp = p->prev;
        
        Node *newNode = new Node(val);

        temp->next = newNode;
        newNode->prev = temp;
        newNode->next = p;
        p->prev = newNode;
        size ++;
    }

    // ***** 删 *****

    T removeFirst() {
        Node *p = head->next;
        Node *next = p->next;

        head->next = next;
        next->prev = head;

        T val = p->val;
        p->prev = nullptr;
        p->next = nullptr;

        size --;

        delete p;

        return val;
    }

    T removeLast() {
        Node *p = tail->prev;
        Node *prev = p->prev;
        prev->next = tail;
        tail->prev = prev;

        T val = p->val;
        p->prev = nullptr;
        p->next = nullptr;

        size --;

        delete p;
        
        return val;
    }

    T remove(int index) {
        checkElementIndex(index);

        Node *p = getNode(index);

        Node *prev = p->prev;
        Node *next = p->next;

        T val = p->val;
        prev->next = next;
        next->prev = prev;

        p->next = nullptr;
        p->prev = nullptr;

        size --;

        delete p;
        
        return val;
    }

    // ***** 查 *****

    T get(int index) {
       checkElementIndex(index);

       Node *p = getNode(index);
       return p->val;
    }

    T getFirst() {
        if (size < 1)
        {
            throw out_of_range("No elements in the list");
        }
        return head->next->val;
    }

    T getLast() {
        if (size < 1)
        {
            throw out_of_range("No elements in the list");
        }
        return tail->prev->val;
    }

    // ***** 改 *****

    T set(int index, T val) {
        checkElementIndex(index);
        
        Node *p = getNode(index);
        T oldVal = p->val;
        p->val = val;
        
        return oldVal;
    }

    // ***** 其他工具函数 *****

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void display() {
        cout << "size = " << size << endl;
        for (Node* p = head->next; p != tail; p = p->next) {
            cout << p->val << " <-> ";
        }
        cout << "nullptr" << endl;
        cout << endl;
    }

private:
    Node* getNode(int index) {
        checkElementIndex(index);

        Node *p = head->next;
        for (int i = 0; i < index; i ++)
        {
            p = p->next;
        }
        
        return p;
    }

    bool isElementIndex(int index) const {
        return index >= 0 && index < size;
    }

    bool isPositionIndex(int index) const {
        return index >= 0 && index <= size;
    }

    // 检查 index 索引位置是否可以存在元素
    void checkElementIndex(int index) const {
        if (!isElementIndex(index))
            throw out_of_range("Index: " + to_string(index) + ", Size: " + to_string(size));
    }

    // 检查 index 索引位置是否可以添加元素
    void checkPositionIndex(int index) const {
        if (!isPositionIndex(index))
            throw out_of_range("Index: " + to_string(index) + ", Size: " + to_string(size));
    }
};

int main() {
    doubleLinkLish<int> list;
    list.addLast(1);
    list.addLast(2);
    list.addLast(3);
    list.addFirst(0);
    list.add(2, 100);

    list.display();
    // size = 5
    // 0 <-> 1 <-> 100 <-> 2 <-> 3 <-> null

    return 0;
}