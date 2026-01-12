#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class CycleArray {
    vector<T> arr;
    int start;
    int end;
    int count;

    void resize(int new_cap)
    {
        vector<T> new_arr(new_cap);
        for (int i = 0; i < count; i ++)
        {
            new_arr[i] = arr[(start + i) % arr.size()];
        }
        arr = move(new_arr);
        start = 0;
        end = count;
    }

public:
    CycleArray() : CycleArray(1) {}
    explicit CycleArray(int size) : arr(size), start(0), end(0), count(0) {}

    void addFirst(T val) {
        if (isFull())
        {
            resize(arr.size() * 2);
        }

        start = (start - 1 + arr.size()) % arr.size();
        arr[start] = val;
        count ++;
    }

    void addLast(T val) {
        if (isFull())
        {
            resize(arr.size() * 2);
        }

        arr[end] = val;
        end = (end + 1) % arr.size();
        count ++;
    }

    void removeFirst() {
        if (!isEmpty())
        {
            arr[start] = T();
            start = (start + 1) % arr.size();
            count --;

            if (count > 0 && arr.size() / 4 == count)
            {
                resize(arr.size() / 2);
            }
        }
    }

    void removeLast() {
        if (!isEmpty())
        {
            end = (end - 1 + arr.size()) % arr.size();
            arr[end] = T();
            count --;
            if (count > 0 && arr.size() / 4 == count)
            {
                resize(arr.size() / 2);
            }
        }
    }

    T getFirst() const {
        if (!isEmpty())
        {
            return arr[start];
        }
    }

    T getLast() const {
        if (!isEmpty())
        {
            return arr[(end - 1 + arr.size()) % arr.size()];
        }
    }

    int getCount() const {
        return count;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == arr.size();
    }

    // 辅助函数：打印当前内部状态，方便调试
    void printDebug() {
        cout << "Count: " << count << ", Cap: " << arr.size() 
             << ", Start: " << start << ", End: " << end << endl;
        cout << "Data: [ ";
        for(int i=0; i<count; i++) {
            cout << arr[(start + i) % arr.size()] << " ";
        }
        cout << "]" << endl << endl;
    }
};

// 简单的测试例子
int main() {
    // 1. 初始化容量为 2
    CycleArray<int> dq(2);

    cout << "=== 1. 添加元素 ===" << endl;
    dq.addLast(1);
    dq.addLast(2); 
    // 此时满 [1, 2]
    dq.printDebug();

    cout << "=== 2. 触发扩容 (Capacity 2 -> 4) ===" << endl;
    dq.addFirst(0); 
    // 此时应该触发 resize，逻辑顺序应该是 0, 1, 2
    dq.printDebug();

    cout << "=== 3. 制造环绕 (Wrap Around) ===" << endl;
    // 目前 [0, 1, 2, _], start=0, end=3
    dq.removeFirst(); // 移除 0
    dq.addLast(3);    
    dq.addLast(4);    
    // 此时 capacity=4, count=4. 物理上可能已经环绕了
    dq.printDebug();

    cout << "=== 4. 再次触发扩容 (验证顺序是否乱掉) ===" << endl;
    dq.addLast(5); 
    // 此时满，触发 resize 4->8。
    // 关键点：如果 resize 写错了，这里的数据顺序就会变成乱码
    dq.printDebug();
    
    cout << "=== 5. 验证 Get 和 Remove ===" << endl;
    cout << "First: " << dq.getFirst() << endl; // 应该是 1
    cout << "Last: "  << dq.getLast() << endl;  // 应该是 5
    
    dq.removeLast();
    dq.removeFirst();
    dq.printDebug();

    return 0;
}
