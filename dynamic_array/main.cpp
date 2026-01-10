#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class MyLinkedList 
{
    private:
        T *data;
        int size;
        int capacity;
        static const int init_capacity = 1;
    public:
        MyLinkedList() {
            this->data = new T[init_capacity];
            this->size = 0;
            this->capacity = init_capacity;
        }

        MyLinkedList(int capacity) {
            this->data = new T[capacity];
            this->size = 0;
            this->capacity = capacity;
        }

        ~MyLinkedList() {
            delete []data;
        }

        bool isElementIndex(int index) {
            return index >= 0 && index < size;
        }

        bool isPositionIndex(int index) {
            return index >= 0 && index <=size;
        }

        void resize(int newCap) {
            T *temp = new T[newCap];

            for (int i = 0; i < size; i ++) {
                temp[i] = data[i];
            }

            delete []data;
            data = temp;
            capacity = newCap;
        }
        
        T get(int index) {
            if (!isElementIndex(index)) {
                return -1;
            }
            return data[index];
        }

        void add(int index, T val) {
            if (!isPositionIndex(index)) 
            { 
                throw out_of_range("Index out of bounds");
            }
            
            if (size == capacity) {
                resize(capacity * 2);
            }
            
            for (int i = size - 1; i >= index; i --)
            {
                data[i + 1] = data[i];
            }

            data[index] = val;
            size ++;
            
        }

        T remove(int index) {
            if (!isElementIndex(index)) { 
                throw out_of_range("Index out of bounds");
            }

            T deleteVal = data[index];

            if (index == size - 1) 
            {
                size --;
            } 
            else {
                for (int i = index; i < size - 1; i ++) 
                {
                    data[i] = data[i + 1];
                }
                size --;
            }

            if (size == capacity / 4) 
            {
                resize(capacity / 2);
            }

            return deleteVal;
        }
        
        void addAtHead(T val) {
            add(0, val);
        }
        
        void addAtTail(T val) {
            add(size, val);
        }
        
        void addAtIndex(int index, T val) {
            add(index, val);
        }
        
        void deleteAtIndex(int index) {
            remove(index);
        }

        T deleteTail() {
            return remove(size - 1);
        }

        int getSize() {
            return size;
        }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */

 int main() {
    // 初始容量设置为 3
    MyLinkedList<int> arr(3);

    // 添加 5 个元素
    for (int i = 1; i <= 5; i++) {
        arr.addAtTail(i);
    }

    arr.deleteAtIndex(3);
    arr.add(1, 9);
    arr.addAtHead(100);
    int val = arr.deleteTail();

    // 100 1 9 2 3
    for (int i = 0; i < arr.getSize(); i++) {
        cout << arr.get(i) << endl;
    }

    return 0;
}
