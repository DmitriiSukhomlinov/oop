#pragma once

#include <stdexcept>
#include <string>

namespace oop {

template <typename Type>
class Container {
public:
    Container();
    Container(const Container& other);
    ~Container();
    Container& operator=(const Container& other);
    bool operator==(const Container& other);

    void addNew(const Type& newElement);
    void deleteLast();
    Type getByIndex(const int index) const;
    int getSize() const;
    bool isEmpty() const;
    void clean();

private:
    void setDefault();
    void reallocateMemory();
    void initThis(const Container<Type>& other);
    void cleanOnly();

    int arraySize;
    int indexNextToAdd;

    Type* values;

    static const int MINIMAL_ARRAY_NUMBER;
};


template<typename Type>
const int Container<Type>::MINIMAL_ARRAY_NUMBER = 10;

template<typename Type>
Container<Type>::Container() {
    setDefault();
}

template<typename Type>
Container<Type>::Container(const Container& other) {
    initThis(other);
}

template<typename Type>
Container<Type>::~Container() {
    cleanOnly();
}

template<typename Type>
Container<Type>& Container<Type>::operator=(const Container& other) {
    if (*this == other) {
        return *this;
    }

    initThis(other);
    return *this;
}

template<typename Type>
bool Container<Type>::operator==(const Container& other) {
    bool result = this->arraySize == other.arraySize && 
                  this->indexNextToAdd == other.indexNextToAdd;
    if (!result) {
        return false;
    }

    for (int i = 0; i < this->arraySize; i++) {
        if (i == this->indexNextToAdd || !result) {
            break;
        }

        result = this->values[i] == other.values[i];
    }

    return result;
}

template<typename Type>
void Container<Type>::addNew(const Type& newElement) {
    new (values + indexNextToAdd) Type(newElement);
    indexNextToAdd++;
    if (indexNextToAdd == arraySize) {
        reallocateMemory();
    }
}

template<typename Type>
void Container<Type>::deleteLast() {
    int indexLast = indexNextToAdd - 1;
    values[indexLast].~Type();
    indexNextToAdd = indexLast;
}

template<typename Type>
Type Container<Type>::getByIndex(const int index) const {
    if (index < 0 || index >= indexNextToAdd) {
        if (isEmpty()) {
            throw std::runtime_error("Container is empty");
        }
        throw std::runtime_error("Container<Type>::getByIndex(const int index): incorrect index, expected: from 0 to "
            + std::to_string(indexNextToAdd - 1) + ", current: " + std::to_string(index));
    }

    return values[index];
}

template<typename Type>
int Container<Type>::getSize() const {
    return indexNextToAdd;
}

template<typename Type>
bool Container<Type>::isEmpty() const {
    return indexNextToAdd == 0;
}

template<typename Type>
void Container<Type>::clean() {
    cleanOnly();
    setDefault();
}

template<typename Type>
void Container<Type>::setDefault() {
    arraySize = MINIMAL_ARRAY_NUMBER;
    indexNextToAdd = 0;
    values = reinterpret_cast<Type*>(operator new(sizeof(Type) * arraySize));
}


template<typename Type>
void Container<Type>::reallocateMemory() {
    const int newArraySize = arraySize + MINIMAL_ARRAY_NUMBER;
    Type* tmp = reinterpret_cast<Type*>(operator new(sizeof(Type) * newArraySize));
    for (int i = 0; i < indexNextToAdd; i++) {
        new (tmp + i) Type(values[i]);
    }
    cleanOnly();
    values = tmp;
    arraySize = newArraySize;
}

template<typename Type>
void Container<Type>::initThis(const Container<Type>& other) {
    this->arraySize = other.arraySize;
    this->indexNextToAdd = other.indexNextToAdd;
    this->values = reinterpret_cast<Type*>(operator new(sizeof(Type) * this->arraySize));
    for (int i = 0; i < this->indexNextToAdd; i++) {
        new (this->values + i) Type(other.values[i]);
    }
}

template<typename Type>
void Container<Type>::cleanOnly() {
    for (int i = 0; i < indexNextToAdd; i++) {
        values[i].~Type();
    }
    operator delete(values);
}

}