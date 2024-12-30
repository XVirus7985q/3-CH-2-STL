#include <iostream>
#include <Vector> 

template <typename T>
class SimpleVector {
private:
    T* data;              // ������ �迭
    int currentSize;      // ���� ������ ����
    int currentCapacity;  // ���� �迭 �뷮

    void reallocate(int newCapacity) {
        if (newCapacity <= currentCapacity) {
            return; // ���ο� �뷮�� �������� �۰ų� ������ �ƹ��͵� ���� ����
        }
        T* newData = new T[newCapacity]; // ���ο� �迭 �Ҵ�
        for (int i = 0; i < currentSize; ++i) { // ���� ������ ������ŭ ����
            newData[i] = data[i];
        }
        delete[] data; // ���� �迭 �޸� ����
        data = newData; // �� �迭�� ��ü
        currentCapacity = newCapacity; // �뷮 ����
    }

public:
    SimpleVector() : SimpleVector(10) {}

    SimpleVector(int capacity)
        : currentSize(0), currentCapacity(capacity) {
        data = new T[currentCapacity];
    }

    SimpleVector(const SimpleVector& other)
        : currentSize(other.currentSize), currentCapacity(other.currentCapacity) {
        data = new T[currentCapacity];
        for (int i = 0; i < currentSize; ++i) {
            data[i] = other.data[i];
        }
    }

    ~SimpleVector() {
        delete[] data;
    }

    void resize(int newCapacity) {
        if (newCapacity > currentCapacity) {
            reallocate(newCapacity); // �� �뷮�� �� ũ�� ���Ҵ�
        }
    }

    void push_back(const T& value) {
        if (currentSize >= currentCapacity) {
            reallocate(currentCapacity + 5); // �뷮�� 5 ����
        }
        data[currentSize] = value; // �� �����͸� ���� ��ġ�� �߰�
        ++currentSize; // ������ ���� ����
    }

    void pop_back() {
        if (currentSize > 0) {
            --currentSize; // ũ�� ����
        }
    }

    int size() const {
        return currentSize;
    }

    int capacity() const {
        return currentCapacity;
    }

    void print() const {
        for (int i = 0; i < currentSize; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    SimpleVector<int> vec;

    // ������ �߰� �׽�Ʈ
    for (int i = 1; i <= 15; ++i) {
        vec.push_back(i);
        std::cout << "Added: " << i << ", Size: " << vec.size()
            << ", Capacity: " << vec.capacity() << std::endl;
        vec.print(); // ���� ���� ���
    }
       

    // �뷮 Ȯ�� �׽�Ʈ
    vec.resize(30);
    std::cout << "Capacity after resize: " << vec.capacity() << std::endl;

    // �ٽ� ������ �߰�
    for (int i = 16; i <= 25; ++i) {
        vec.push_back(i);
        std::cout << "Added: " << i << ", Size: " << vec.size()
            << ", Capacity: " << vec.capacity() << std::endl;
        vec.print(); // ���� ���� ���
    }    

    // ������ ���� �׽�Ʈ
    std::cout << "\nRemoving data:" << std::endl;
    for (int i = 25; i > 0; --i) { // �������� ����
        std::cout << "Subtract: " << i << ", Size: " << vec.size()
            << ", Capacity: " << vec.capacity() << std::endl;
        vec.print(); // ���� ���� ���
        vec.pop_back(); // �����͸� ����
    }

    return 0;
}
