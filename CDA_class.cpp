#include <iostream>
#include <random>

using namespace std;

template <class T>
class CDA
{
    private:
        int size;
        int capacity;
        bool ordered;
        T *array;
        int frontIndex;
        T trash;
    public:
        CDA<T>();
        CDA<T>(int s);
        CDA<T>(CDA &obj);
        ~ CDA<T>();
        T& operator[](int i);
        void operator=(CDA &obj);
        void AddEnd(T elem);
        void AddFront(T elem);
        void DelEnd();
        void DelFront();
        int Length();
        int Capacity();
        void Print();
        int circIndex(unsigned long i);
        void CopyOver();
        void Downsize();
        void Clear();
        bool Ordered();
        void CheckIfOrderedFront(int index);
        void CheckIfOrderedBack(int index);
        void InsertionSort();
        void InsertionSort(int start, int localSize);
        void CountingSort(unsigned long m);
        int SetOrdered();
        int Search(T e); 
        void QuickSort();
        void QuickRecurse(int start, int end);
        int MedOfThree(int left, int right); 
        void Swap(int left, int right);
        T Select(int k);
        T QuickSelect(int start, int end, int k);
        int Partition(int start, int end);
        int BinaryRecurse(int start, int end, T elem);
};

template <class T>
CDA<T>::CDA()
{
    this->size = 0;
    this->capacity = 1;
    this->ordered = false;
    this->array = new T[capacity];
    this->frontIndex = 0;
}

template <class T>
CDA<T>::CDA(int s)
{
    this->size = s;
    this->capacity = s;
    this->ordered = false;
    this->array = new T[capacity];
    this->frontIndex = 0;
}

template <class T>
CDA<T>::~CDA()
{
    delete [] this->array;
}

template <class T>
CDA<T>::CDA(CDA &obj)
{
    this->size = obj.size;
    this->capacity = obj.capacity;
    this->frontIndex = 0;
    this->ordered = obj.ordered;

    this->array = new T[this->capacity];

    for (int i = 0; i < obj.size; i++)
    {
        this->array[i] = obj[i];
    }
}

template <class T>
void CDA<T>::AddEnd(T elem)
{
    int index = 0;

    if (this->size == this->capacity)
    {
        this->CopyOver();
        this->AddEnd(elem);
    }

    else
    {
        index = ((this->frontIndex + this->size) % this->capacity);
        this->array[index] = elem;
        this->size++;
        this->CheckIfOrderedBack(index);
    }
}

template <class T>
void CDA<T>::AddFront(T elem)
{
    int index = 0;

    if (this->size == this->capacity)
    {
        this->CopyOver();
        this->AddFront(elem);
    }

    else
    {
        index = (((this->frontIndex + this->capacity) - 1) % this->capacity);
        this->array[index] = elem;
        this->frontIndex = index;
        this->size++;
        this->CheckIfOrderedFront(index);
    }
}

template <class T>
int CDA<T>::Length()
{
    return this->size;
}

template <class T>
int CDA<T>::Capacity()
{
    return this->capacity;
}

template <class T>
void CDA<T>::Print()
{
    for (int i = 0; i < this->size; i++)
    {
        cout << this->array[this->circIndex(i)] << " ";
    }
    cout << endl;
}

template <class T>
int CDA<T>::circIndex (unsigned long i)
{
    return ((this->frontIndex + i)  % this->capacity);
}

template <class T>
void CDA<T>::CopyOver()
{
    T *newArray = new T[this->capacity * 2];

    for (int i = 0; i < this->size; i++)
    {
        newArray[i] = this->array[this->circIndex(i)];
    }

    delete [] this->array;
    this->array = newArray;
    this->capacity = this->capacity * 2;
    this->frontIndex = 0;
}

template <class T>
void CDA<T>::Clear()
{
    delete [] this->array;
    this->array = new T[1];
    this->size = 0;
    this->capacity = 1;
    this->ordered = false;
    this->frontIndex = 0;
}

template <class T>
bool CDA<T>::Ordered()
{
    return this->ordered;
}

template <class T>
T& CDA<T>::operator[](int i)
{
    if ((i < 0) || (i > this->size - 1))
    {
        cout << "Error: Position " << i << " is outside the bounds of the array." << endl;
        return trash;
    }
    
    else
    {
        return this->array[this->circIndex(i)];
    }
}

template <class T>
void CDA<T>::CheckIfOrderedFront(int index)
{
    if (this->ordered == true)
    {
        int rightIndex = 0;
        rightIndex = ((index + 1) % this->capacity);

        if (this->array[rightIndex] >= this->array[index])
        {
            this->ordered = true;
        }

        else
        {
            this->ordered = false;
        }
    }
}

template <class T>
void CDA<T>::CheckIfOrderedBack(int index)
{
    if (this->ordered == true)
    {
        int leftIndex = 0;
        leftIndex = ((index - 1) % this->capacity);

        if (this->array[leftIndex] <= this->array[index])
        {
            this->ordered = true;
        }

        else
        {
            this->ordered = false;
        }
    }
}

template <class T>
void CDA<T>::DelEnd()
{
    if (this->size == 0)
        return;
    
    if (this->size - 1 == (this->capacity / 4))
    {
        if (this->capacity == 1)
        {
            this->Clear();
            return;
        }

        this->Downsize();
        this->size--;
    }

    else
    {
        this->size--;
    }
}

template <class T>
void CDA<T>::DelFront()
{
    if (this->size == 0)
        return;

    int index = 0;

    if (this->size - 1 == (this->capacity / 4))
    {
        if (this->capacity == 1)
        {
            this->Clear();
            return;
        }

        this->Downsize();
        this->frontIndex = (((this->frontIndex + this->capacity) + 1) % this->capacity);
        this->size--;
    }

    else
    {
        this->frontIndex = (((this->frontIndex + this->capacity) + 1) % this->capacity);
        this->size--;
    }
}

template <class T>
void CDA<T>::Downsize()
{
    T *newArray = new T[this->capacity / 2];

    for (int i = 0; i < this->capacity / 2; i++)
    {
        newArray[i] = this->array[this->circIndex(i)];
    }

    delete [] this->array;
    this->array = newArray;
    this->capacity = this->capacity / 2;
    this->frontIndex = 0;
}

template <class T>
void CDA<T>::InsertionSort()
{
    for (int i = 1; i < this->size; i++)
    {
        T value = this->array[this->circIndex(i)];
        int hole = (this->circIndex(i));

        while ((((this->capacity + hole) - this->frontIndex) % this->capacity) && (this->array[((hole - 1) + this->capacity) % this->capacity] > value))
        {
            this->array[(hole + this->capacity) % this->capacity] = this->array[((hole - 1) + this->capacity) % this->capacity];
            hole --;
        }

        this->array[(hole + this->capacity) % this->capacity] = value;
    }
    this->ordered = true;
}

template <class T>
void CDA<T>::InsertionSort(int start, int localSize)
{
    // for (int i = circIndex(start); ; i++)
    int i = start;

    // cout << "START: " << circIndex(start) << endl; // GOOD
    // cout << "LOCAL SIZE: " << localSize << endl;
    // cout << "END: " << (localSize + circIndex(start)) % capacity << endl;

    int flag = 0;

    while (flag < localSize)
    {
        T value = this->array[this->circIndex(i)];
        int hole = (this->circIndex(i));

        while ((((this->capacity + hole) - this->frontIndex) % this->capacity) && (this->array[((hole - 1) + this->capacity) % this->capacity] > value))
        {
            this->array[(hole + this->capacity) % this->capacity] = this->array[((hole - 1) + this->capacity) % this->capacity];
            hole --;
        }

        this->array[(hole + this->capacity) % this->capacity] = value;
        i++;
        flag++;
    }
}

template <class T>
void CDA<T>::CountingSort(unsigned long int m)
{
    int *arrayC = new int[m + 1];
    
    for (int i = 0; i < m + 1; i++)
        arrayC[i] = 0;

    for (unsigned long int i = 0; i < this->size; i++) // COUNT ELEMENTS
        arrayC[this->array[this->circIndex(i)]]++;

    int *arrayCPrime = new int[m + 1];
    arrayCPrime[0] = 0;

    for (unsigned long int i = 1; i < m + 1; i++) // SUM PREVIOUS ELEMENTS
        arrayCPrime[i] = arrayC[i-1] + arrayCPrime[i - 1];

    T *arrayB = new T[this->capacity];

    for (unsigned long int i = 0; i < this->size; i++)
    {
        arrayB[arrayCPrime[this->array[this->circIndex(i)]]] = this->array[circIndex(i)];
        arrayCPrime[this->array[this->circIndex(i)]]++;
    }

    delete [] this->array;
    delete [] arrayCPrime;
    delete [] arrayC;
    this->array = arrayB;
    this->frontIndex = 0;
    this->ordered = true;
}

template <class T>
int CDA<T>::SetOrdered()
{
    T initialVal = this->array[this->circIndex(0)];
    int flag = 1;

    for (int i = 1; i < this->size; i++)
    {
        T value = this->array[this->circIndex(i)];
        if (value >= initialVal)
            flag++;

        else
            break;

        initialVal = this->array[this->circIndex(i)];
    }

    if (flag == this->size)
    {
        this->ordered = true;
        return 1;
    }

    else
    {
        this->ordered = false;
        return -1;
    }
}

template <class T>
int CDA<T>::BinaryRecurse(int start, int end, T elem)
{
    // cout << "PERFORMING BINARY SEARCH" << endl;
    // cout << "SEARCH FOR ELEMENT: " << elem << endl;
    // cout << "START: " << start << endl;
    // cout << "END: " << end << endl;

    int relativeStart = ((start + capacity) - frontIndex) % capacity;
    // cout << "RELATIVE START: " << relativeStart << endl;

    int relativeEnd = ((end + capacity) - frontIndex) % capacity;
    // cout << "RELATIVE END: " << relativeEnd << endl;

    int mid = this->circIndex((relativeStart + relativeEnd) / 2);
    // cout << "MID: " << mid << endl;

    if (this->array[mid] == elem)
    {
        return (((mid + capacity) - frontIndex) % capacity);
    }

    else if (elem < this->array[mid])
    {
        // cout << "RECURSING WITH LEFT HALF" << endl;
        end = ((mid - 1) + capacity) % capacity;
        // cout << "RECURSION BOUNDS: " << start << " " << end << endl;
        // end = mid - 1;
        int index = BinaryRecurse(start, end, elem);
        // return (((index + capacity) - frontIndex) % capacity);
        return index;
    }

    else
    {
        // cout << "RECURSING WITH RIGHT HALF" << endl;
        // start = this->circIndex(mid + 1);
        start = ((mid + 1) + capacity) % capacity;
        // cout << "RECURSION BOUNDS: " << start << " " << end << endl;
        int index = BinaryRecurse(start, end, elem);
        // return (((index + capacity) - frontIndex) % capacity);
        return index;
    }
        
    return -1;
}

template <class T>
int CDA<T>::Search(T elem)
{
    if (this->ordered == true)
    {
        // cout << "BINARY SEARCH" << endl;
        int index = BinaryRecurse(circIndex(0), circIndex(size - 1), elem);
        return index;
    }

    else
    {
        // cout << "LINEAR SEARCH" << endl;
        for (int i = 0; i < this->size; i++)
        {
            // cout << "I: " << i << endl;
            // cout << this->array[this->circIndex(i)] << " ";
            if (this->array[this->circIndex(i)] == elem)
            {
                return i;
            }
        }
        cout << endl;

        return -1;
    }
}

template <class T>
void CDA<T>::operator=(CDA &obj)
{
    if (this != &obj)
    {
        this->size = obj.size;
        this->capacity = obj.capacity;
        this->frontIndex = 0;
        this->ordered = obj.ordered;

        this->array = new T[this->capacity];

        for (int i = 0; i < obj.size; i++)
        {
            this->array[i] = obj[i];
        }
    }
}

template <class T>
void CDA<T>::Swap(int left, int right) // GOOD
{
    T temp;
    temp = this->array[left];
    this->array[left] = this->array[right];
    this->array[right] = temp;
}

template <class T>
int CDA<T>::MedOfThree(int left, int right) 
{
    int mid = this->circIndex((left + right) / 2);
    left = this->circIndex(left);
    right = this->circIndex(right);

    // cout << "LEFT: " << this->array[left] << endl;
    // cout << "MID: " << this->array[mid] << endl;
    // cout << "RIGHT: " << this->array[right] << endl;
    // this->Print();

    if (this->array[right] < this->array[left])
    {
        Swap(left, right);
    }
    
    if (this->array[mid] < this->array[left])
    {
        Swap(mid, left);
    }

    if (this->array[right] < this->array[mid])
    {
        Swap(right, mid);
    }

    // cout << "AFTER SWAPS" << endl;
    // this->Print();

    return mid;
}

template <class T>
void CDA<T>::QuickRecurse(int start, int end)
{
    int i = 0;
    int j = 0;
    int localFront = 0;
    int localBack = 0;

    // cout << "START: " << start << endl;
    // cout << "END: " << end << endl;

    if (start > this->frontIndex)
    {
        i = start - frontIndex;
        localFront = start - frontIndex;
    }

    else if (start < this->frontIndex)
    {
        i = ((this->capacity - frontIndex) + start);
        localFront = ((this->capacity - frontIndex) + start);
    }

    else
    {
        i = 0;
    }

    if (end > start)
    {
        j = (end - start) + i;
        localBack = ((end - start) + i);
    }

    else if (start > end)
    {
        j = ((this->capacity - start) + end) + i;
        localBack = (((this->capacity - start) + end) + i);
    }

    else
    {
        j = 0;
        localBack = 0;
    }

    if ((j - i) + 1 <= 55)
    {
        int localSize = (j - i) + 1;
        // cout << "J: " << j << endl;
        // cout << "I: " << i << endl;
        // cout << "ARRAY SIZE 10 OR LESS" << endl;
        // cout << "LOCAL SIZE: " << localSize << endl;
        this->InsertionSort(i, localSize);
        return;
    }

    // int localSize = ((((j + this->capacity) - this->size) % this->capacity) - (((i + this->capacity) - this->size) % this->capacity)) + 1;
    // cout << "LOCAL SIZE " << localSize << endl;
    int pivotIndex = MedOfThree(i, j);
    T pivot = array[pivotIndex];

    // int pivot = array[end];
    /*
    cout << "I: " << circIndex(i) << " " << array[circIndex(i)] << endl;
    cout << "J: " << circIndex(j) << " " << array[circIndex(j)] << endl;;
    cout << "LOCAL FRONT " << localFront << endl;
    cout << "LOCAL BACK " << localBack << endl;
    cout << "FRONT INDEX: " << frontIndex << endl;
    cout << "PIVOT: " << pivot << endl; 
    cout << "PIVOT INDEX: " << pivotIndex << endl;
    this->Print();
    */
    T temp;

    // while ((((i + this->capacity) - this->size) % this->capacity) <= (((j + this->capacity) - this->size) % this->capacity)) // SHOULD BE GOOD
    while (i <= j)
    {
        // cout << "FIRST WHILE LOOP TRIGGERED" << endl;

        while (array[circIndex(i)] < pivot)
        {
            // cout << array[(i + this->capacity) % this->capacity] << " IN POSITION " << (i + this->capacity) % this->capacity << " LESS THAN PIVOT." << endl;
            i++;
            // cout << "I INCREASED TO: " << i << endl;
            // cout << "I IS NOW IN POSITION " << (i + this->capacity) % this->capacity << endl;
        }

        while (array[circIndex(j)] > pivot)
        {
            // cout << array[(j + this->capacity) % this->capacity] << " IN POSITION " << (j + this->capacity) % this->capacity << " GREATER THAN PIVOT." << endl;
            j--;
            // cout << "J DECREASED TO: " << j << endl;
            // cout << "J IS NOW IN POSITION " << (j + this->capacity) % this->capacity << endl;
        }

        // cout << "AFTER FIRST LOOP" << endl;
        // cout << "I: " << i << endl;
        // cout << "J: " << j << endl;
        // this->Print();
        // cout << endl;

        /*
        cout << "I: " << i << endl;
        cout << "POSITION: " << (i + this->capacity) % this->capacity << endl;
        cout << "J: " << j << endl;
        cout << "POSITION: " << (j + this->capacity) % this->capacity << endl;
        */

        // if ((((i + this->capacity) - this->size) % this->capacity) <= (((j + this->capacity) - this->size) % this->capacity))
        if (i <= j)
        {
            /*if (pivotIndex == this->circIndex(i))
            {
                cout << "SWAPPING PIVOT WITH I" << endl;
                pivotIndex = j;
                cout << "NEW PIVOT INDEX " << circIndex(pivotIndex) << endl;
                temp = array[circIndex(i)];
                array[circIndex(i)] = array[circIndex(j)];
                array[circIndex(j)] = temp;
                i++;
                j--;
            }

            else if (pivotIndex == this->circIndex(j))
            {
                cout << "SWAPPING PIVOT WITH J" << endl;
                pivotIndex = i;
                cout << "NEW PIVOT INDEX " << circIndex(pivotIndex) << endl;
                temp = array[circIndex(i)];
                array[circIndex(i)] = array[circIndex(j)];
                array[circIndex(j)] = temp;
                i++;
                j--;
            }

            else
            {
                cout << "REGULAR SWAP, NO UPDATE TO PIVOT" << endl;
                
            } */

            temp = array[circIndex(i)];
            array[circIndex(i)] = array[circIndex(j)];
            array[circIndex(j)] = temp;
            i++;
            // cout << "I INCREASED TO: " << i << endl;
            // cout << "I IS NOW IN POSITION " << (i + this->capacity) % this->capacity << endl;
            j--;
            
            // cout << "PERFORMING SWAP" << endl;
            // cout << "I: " << (((i + this->capacity) - this->size) % this->capacity) << ", IS LESS THAN OR EQUAL TO J: " << (((j + this->capacity) - this->size) % this->capacity) << endl;
            // cout << "SWAPPING ARRAY[I] AND ARRAY [J]." << endl;
            // cout << "J DECREASED TO: " << j << endl;
            // cout << "J IS NOW IN POSITION " << (j + this->capacity) % this->capacity << endl;
            // cout << "I: " << i << endl;
            // cout << "J: " << j << endl;
            // this->Print();
            // cout << endl;
        }
    }

    // cout << "CURRENT ARRAY: ";
    // this->Print();

    // cout << "I: " << circIndex(i) << endl;
    // cout << "J: " << circIndex(j) << endl;
    // cout << endl;

    // cout << "START: " << start << endl;
    // cout << "END: " << end << endl;

    // cout << endl;

    /*

    if (((array[circIndex(pivotIndex - 1)] > array[circIndex(pivotIndex)]) || (array[circIndex(pivotIndex + 1)] < array[circIndex(pivotIndex)])) && ((pivotIndex != end) && (pivotIndex != start)))
    {
        cout << "SOMETHIN AINT RIGHT... " << endl;

        if (array[circIndex(pivotIndex + 1)] < array[circIndex(pivotIndex)])
        {
            cout << "SWAPPING WITH J" << endl;
            temp = array[circIndex(j)];
            array[circIndex(j)] = array[circIndex(pivotIndex)];
            array[circIndex(pivotIndex)] = temp;
            pivotIndex = j;
            cout << "ARRAY NOW: " << endl;
            Print();
            cout << endl;
        }

        else if (array[circIndex(pivotIndex - 1)] > array[circIndex(pivotIndex)])
        {
            cout << "SWAPPING WITH I" << endl;
            temp = array[circIndex(i)];
            array[circIndex(i)] = array[circIndex(pivotIndex)];
            array[circIndex(pivotIndex)] = temp;
            pivotIndex = i;
            cout << "ARRAY NOW: " << endl;
            Print();
            cout << endl;
        }
    }

    if ((array[circIndex(i)] > array[circIndex(pivotIndex)]) && (circIndex(pivotIndex - 1) == circIndex(i)) && (pivotIndex != frontIndex))
    {
        cout << "SWAP WITH I NECESSARY TO FORM PARTITION" << endl;
        cout << "CIRCINDEX(I): " << circIndex(i) << endl;
        cout << "CIRCINDEX(PIV): " << circIndex(pivotIndex) << endl;
        
        temp = array[circIndex(i)];
        array[circIndex(i)] = array[circIndex(pivotIndex)];
        array[circIndex(pivotIndex)] = temp;
        cout << "ARRAY NOW: " << endl;
        Print();
        cout << endl;
        
    }

    if ((array[circIndex(j)] < array[circIndex(pivotIndex)]) && (circIndex(pivotIndex + 1) == circIndex(j)) && (pivotIndex != frontIndex))
    {
        cout << "SWAP WITH J NECESSARY TO FORM PARTITION" << endl;
        cout << "CIRCINDEX(J): " << circIndex(j) << endl;
        cout << "CIRCINDEX(PIV): " << circIndex(pivotIndex) << endl;
        
        temp = array[circIndex(j)];
        array[circIndex(j)] = array[circIndex(pivotIndex)];
        array[circIndex(pivotIndex)] = temp;
        cout << "ARRAY NOW: " << endl;
        Print();
        cout << endl;
        
    }
    */

    // if ((((j + this->capacity) - this->size) % this->capacity) > (((start + this->capacity) - this->size) % this->capacity))
    if (j > localFront)
    {
        // cout << "J: " << (((j + this->capacity) - this->size) % this->capacity) << " IS GREATER THAN START: " << (((start + this->capacity) - this->size) % this->capacity) << endl;
        // cout << "RECURSING WITH START: " << start << " AND END: " << this->circIndex(j) << endl << endl;
        QuickRecurse(start, this->circIndex(j));
    }

    if (i < localBack)
    {
        // cout << "I: " << (((i + this->capacity) - this->size) % this->capacity) << " IS LESS THAN END: " << (((end + this->capacity) - this->size) % this->capacity) << endl;
        // cout << "RECURSING WITH START: " << this->circIndex(i) << " AND END: " << end << endl << endl;
        QuickRecurse(this->circIndex(i), end);
    }
}

template <class T>
void CDA<T>::QuickSort()
{
    QuickRecurse(this->frontIndex, this->circIndex(this->size - 1));
    this->ordered = true;
}

template <class T>
T CDA<T>::Select(int k)
{
    T returnVal;
    returnVal = this->QuickSelect(this->frontIndex, this->circIndex(this->size - 1), k);
    return returnVal;
}

template <class T>
T CDA<T>::QuickSelect(int start, int end, int k)
{
    if ((k < 0) || (k > (this->size)))
    {
        cout << "K out of bounds." << endl;
        return trash;
    }

    if (this->ordered == true)
    {
        return this->array[this->circIndex(k - 1)];
    }

    else
    {
        int index = Partition(start, end);
        // cout << "INDEX: " << index << endl;
        // cout << "PARTITION INDEX: " << ((index - frontIndex) + capacity) % capacity << endl;

        if (((index - frontIndex) + capacity) % capacity == k - 1)
        {
            return array[index % capacity];
        }

        else if (((index - frontIndex) + capacity) % capacity > k - 1)
        {
            return QuickSelect(start, (index - 1) % capacity, k);
        }

        else
        {
            return QuickSelect((index + 1) % capacity, end, k);
        }  
    }
}

template <class T>
int CDA<T>::Partition(int start, int end)
{
    // Print();

    if (start == end)
        return start;

    // cout << "START INDEX: " << start << endl;
    // cout << "START VAL: " << array[start] << endl;
    // cout << "END INDEX: " << end << endl;
    // cout << "END VAL: " << array[end] << endl;
    int i = 0;
    int j = 0;

    if (start > this->frontIndex)
        i = start - frontIndex;

    else if (start < this->frontIndex)
        i = ((this->capacity - frontIndex) + start);

    else
        i = frontIndex;

    if (end > start)
        j = (end - start) + i;

    else if (start > end)
        j = ((this->capacity - start) + end) + i;

    else
        j = 0;

    int localSize = (j - i) + 1;



    // int pivotIndex = circIndex(rand() % localSize);

    int pivotIndex = circIndex((rand() % ((((end - frontIndex) + capacity) % capacity) - (((start - frontIndex) + capacity) % capacity) + 1)) + (((start - frontIndex) + capacity) % capacity));

    // cout << "RELATIVE START BOUND: " << ((start - frontIndex) + capacity) % capacity << endl;
    // cout << "RELATIVE END BOUND: " << ((end - frontIndex) + capacity) % capacity << endl; 

    // int randomNumber = rand() % ((localSize - 1) - (((start - frontIndex) + capacity) % capacity) + 1) + (((start - frontIndex) + capacity) % capacity);
    // cout << "RANDOM NUMBER: " << randomNumber << endl;

    // cout << "LOCAL SIZE: " << localSize << endl;
    // cout << "PIVOT INDEX: " << pivotIndex << endl;
    // cout << "SWAPPING PIVOT VAL AND END VAL" << endl;
    T tempVal = array[end];
    array[end] = array[pivotIndex];
    array[pivotIndex] = tempVal;
    T pivot = array[end];
    // cout << "PIVOT: " << pivot << endl;
    // Print();

    int pIndex = start;
    i = start;
    int flag = 0;

    while (flag < localSize - 1)
    {
        // cout << "CURRENT VALUE: " << array[i % capacity] << endl;
        if (array[i % capacity] <= pivot)
        {
            // cout << "LESS THAN OR = TO PIVOT" << endl;
            T temp = array[i % capacity];
            array[i % capacity] = array[pIndex % capacity];
            array[pIndex % capacity] = temp;
            pIndex++;
        }
        flag++;
        i++;
        // Print();
    }
    
    T temp = array[pIndex % capacity];
    array[pIndex % capacity] = array[end];
    array[end] = temp;
    // Print();
    // cout << endl;
    return pIndex;
}