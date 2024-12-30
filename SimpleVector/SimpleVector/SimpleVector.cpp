#include <iostream>
#include <Vector> 

template <typename T>
class SimpleVector {
private:
    T* data;              // 데이터 배열
    int currentSize;      // 현재 데이터 개수
    int currentCapacity;  // 현재 배열 용량

    void reallocate(int newCapacity) {
        if (newCapacity <= currentCapacity) {
            return; // 새로운 용량이 기존보다 작거나 같으면 아무것도 하지 않음
        }
        T* newData = new T[newCapacity]; // 새로운 배열 할당
        for (int i = 0; i < currentSize; ++i) { // 현재 데이터 개수만큼 복사
            newData[i] = data[i];
        }
        delete[] data; // 기존 배열 메모리 해제
        data = newData; // 새 배열로 교체
        currentCapacity = newCapacity; // 용량 갱신
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
            reallocate(newCapacity); // 새 용량이 더 크면 재할당
        }
    }

    void push_back(const T& value) {
        if (currentSize >= currentCapacity) {
            reallocate(currentCapacity + 5); // 용량을 5 증가
        }
        data[currentSize] = value; // 새 데이터를 현재 위치에 추가
        ++currentSize; // 데이터 개수 증가
    }

    void pop_back() {
        if (currentSize > 0) {
            --currentSize; // 크기 감소
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

    // 데이터 추가 테스트
    for (int i = 1; i <= 15; ++i) {
        vec.push_back(i);
        std::cout << "Added: " << i << ", Size: " << vec.size()
            << ", Capacity: " << vec.capacity() << std::endl;
        vec.print(); // 현재 상태 출력
    }
       

    // 용량 확장 테스트
    vec.resize(30);
    std::cout << "Capacity after resize: " << vec.capacity() << std::endl;

    // 다시 데이터 추가
    for (int i = 16; i <= 25; ++i) {
        vec.push_back(i);
        std::cout << "Added: " << i << ", Size: " << vec.size()
            << ", Capacity: " << vec.capacity() << std::endl;
        vec.print(); // 현재 상태 출력
    }    

    // 데이터 제거 테스트
    std::cout << "\nRemoving data:" << std::endl;
    for (int i = 25; i > 0; --i) { // 역순으로 제거
        std::cout << "Subtract: " << i << ", Size: " << vec.size()
            << ", Capacity: " << vec.capacity() << std::endl;
        vec.print(); // 현재 상태 출력
        vec.pop_back(); // 데이터를 제거
    }

    return 0;
}
