#pragma once

template<typename T>
struct JohnsArray
{
    JohnsArray(int capacity, int count, T** array)
        : capacity(capacity),
          count(count),
          Array(array)
    {
    }

    JohnsArray();
    ~JohnsArray();
    JohnsArray(int capacity);

private:
    int capacity;
    
public:
    int count;
    T** Array;

    void Add(T* object);
};

template <typename T>
JohnsArray<T>::JohnsArray()
{
    Array = new T*[4];
    capacity = 4;
    count = 0;
}

template <typename T>
JohnsArray<T>::~JohnsArray()
{
    if (Array != nullptr)
    {
        //delete[] Array;
    }
}

template <typename T>
JohnsArray<T>::JohnsArray(const int cap)
{
    Array = new T*[cap];
    capacity = cap;
    count = 0;
}

template <typename T>
void JohnsArray<T>::Add(T* object)
{
    if (count >= capacity)
    {
        T** temp = Array;
        const int oldCap = capacity;
        
        capacity *= 2;
        Array = new T*[capacity];

        for (int i = 0; i < oldCap; i++)
        {
            Array[i] = temp[i];    
        }

        delete[] temp; // ???
    }

    Array[count] = object;
    count++;
}
