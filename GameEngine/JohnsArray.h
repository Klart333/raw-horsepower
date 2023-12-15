#pragma once

template<typename T>
struct JohnsArray
{
    JohnsArray();
    JohnsArray(int capacity);

private:
    int capacity;
    
public:
    int count;
    T** Array;

    bool Contains(T* object);
    void SetTo(T* object);
    JohnsArray<T> ShallowCopy();
    
    void Add(T* object);
    void AddAt(T* object, int index);
    
    void RemoveAt(int index);
    void RemoveAtButIDontCareAboutOrder(int index);
};


template <typename T>
JohnsArray<T>::JohnsArray()
{
    Array = new T*[4];
    capacity = 4;
    count = 0;
}

template <typename T>
void JohnsArray<T>::SetTo(T* object)
{
    delete [] Array;

    Array = new T*[1];
    Array[0] = object;
    count = 1;
    capacity = 1;
}

template <typename T>
JohnsArray<T> JohnsArray<T>::ShallowCopy()
{
    JohnsArray array = JohnsArray(count);
    for (int i = 0; i < count; i++)
    {
        array.Add(Array[i]);
    }

    return array;
}

template <typename T>
JohnsArray<T>::JohnsArray(const int cap)
{
    Array = new T*[cap];
    capacity = cap;
    count = 0;
}

template <typename T>
bool JohnsArray<T>::Contains(T* object)
{
    for (int i = 0; i < count; i++)
    {
        if (*Array[i] == *object)
        {
            return true;
        }
    }

    return false;
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



template <typename T>
void JohnsArray<T>::AddAt(T* object, int index) // OK ONLY USE IF YOU KNOW WHAT YOURE DOING IT PROBABLY WONT WORK AS YOU WANT IT TO!
{
    if (index < 0 || index >= capacity)
    {
        return;
    }

    Array[index] = object;
    count++;
}

template <typename T>
void JohnsArray<T>::RemoveAt(int index)
{
    Array[index] = nullptr; // Yeah... its not super advanced, basically we lost some memory...
}

template <typename T>
void JohnsArray<T>::RemoveAtButIDontCareAboutOrder(int index)
{
    Array[index] = Array[count - 1]; // looooool
    count--; // jokes on me this didnt work, dont really know why...
}
