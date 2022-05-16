# a2g-a2-kdadkhah-shokrollahi-mlee219
a2g-a2-kdadkhah-shokrollahi-mlee219 created by GitHub Classroom  
  
# Part A: Algorithm Analysis  
This section of the assignment analyses the time complexity for several functions inside the table module.  
  
### numRecords()  
The numRecords goes through each record in the table and increments rc. This takes O(n) time to process.
```c++
template <class TYPE> int SimpleTable<TYPE>::numRecords() const {
  int rc = 0;
  for (int i = 0; records_[i] != nullptr; i++) {
    rc++; // n
  }
  return rc;
} // T(n) = O(n)
```  
### 1-Arg Constructor  
Similarly, the constructor, as well as the other functions that require looping through the entire table to perform an operation take O(n) time.
```c++
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity) : Table<TYPE>() {
  records_ = new Record *[capacity + 1];
  capacity_ = capacity;
  for (int i = 0; i < capacity_ + 1; i++) {
    records_[i] = nullptr;
  }
} // T(n) = O(n)
```
### Copy Constructor  
Copy constructor goes through the whole table, removes each index, then goes through it again to copy the incoming object. This means
that T(n) = 2n + b, which we know is just linear time. Therefore T(n) = O(n).

```c++
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE> &rhs) {
  records_ = new Record *[rhs.capacity_ + 1];
  capacity_ = rhs.capacity_;
  for (int i = 0; i < capacity_ + 1; i++) {
    records_[i] = nullptr;
  }
  for (int i = 0; i < rhs.numRecords(); i++) {
    update(rhs.records_[i]->key_, rhs.records_[i]->data_);
  }
} // T(n) = O(n)
```  
### Move Constructor  
The move constructor simply moves the pointer of the incoming object to the current object, and sets the other to nullptr.
This takes constant time, so T(n) = O(1)
```c++
template <class TYPE> SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE> &&rhs) {
  capacity_ = rhs.capacity_;
  records_ = rhs.records_;
  rhs.records_ = nullptr;
  rhs.capacity_ = 0;
} // T(n) = O(1)
```  
### update()  
The update function will in the worst case have to loop through the entire table to insert a new element.
This takes linear time to perform, therefore T(n) = O(n)
```c++
template <class TYPE>
bool SimpleTable<TYPE>::update(const std::string &key, const TYPE &value) {
  int idx = -1;
  int sz = numRecords();
  bool rc = true;
  for (int i = 0; i < sz; i++) {
    if (records_[i]->key_ == key) {
      idx = i;
    }
  } // 2n
  if (idx == -1) {
    if (sz < capacity_) {
      records_[numRecords()] = new Record(key, value);
      for (int i = numRecords() - 1;
           i > 0 && records_[i]->key_ < records_[i - 1]->key_; i--) {
        Record *tmp = records_[i];
        records_[i] = records_[i - 1];
        records_[i - 1] = tmp;
      }
    } else {
      rc = false;
    }
  } else {
    records_[idx]->data_ = value;
  }
  return rc;
} // T(n) = O(n)
```  
### remove()  
Similar to update(), the remove function will in the worst case need to traverse through the entire table to locate
the element for deletion. This takes linear time to perform, so T(n) = O(n)
```c++
template <class TYPE> bool SimpleTable<TYPE>::remove(const std::string &key) {
  int idx = -1;
  int numRecords_ = numRecords();
  for (int i = 0; records_[i] != nullptr; i++) {
    if (records_[i]->key_ == key) {
      idx = i;
    }
  }
  if (idx != -1) {
    delete records_[idx];

    for (int i = idx; i < numRecords() - 1; i++) {
      records_[i] = records_[i + 1];
    }
    records_[numRecords_ - 1] = nullptr;
    return true;
  } else {
    return false;
  }
} // T(n) = O(n)
```  
### find()  
The find function loops through each record in the table to check for a matching key. In the worst case,
it will loop through the entire table, which would take T(n) = O(n) time to process.
```c++
template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string &key, TYPE &value) {
  int idx = -1;
  for (int i = 0; i < numRecords(); i++) {
    if (records_[i]->key_ == key) {
      idx = i;
    }
  }
  if (idx == -1)
    return false;
  else {
    value = records_[idx]->data_;
    return true;
  }
} // T(n) = O(n)
```  
### Copy Assignment Operator  
Like the copy constructor, this takes linear time. T(n) = O(n)
```c++
template <class TYPE>
const SimpleTable<TYPE> &
SimpleTable<TYPE>::operator=(const SimpleTable<TYPE> &rhs) {
  if (this != &rhs) {
    if (records_) {
      while (numRecords() != 0) {
        remove(records_[0]->key_);
      }
      delete[] records_;
    }
    records_ = new Record *[rhs.capacity_ + 1];
    capacity_ = rhs.capacity_;
    for (int i = 0; i < capacity_; i++) {
      records_[i] = nullptr;
    }
    for (int i = 0; i < rhs.numRecords(); i++) {
      update(rhs.records_[i]->key_, rhs.records_[i]->data_);
    }
  }
  return *this;
} // T(n) = O(n)
```  
### Move Assignment Operator  
The move assignment operator loops through each array entirely. Assuming both tables have the same size,
this will take linear time to process. T(n) = O(n)
```c++
template <class TYPE>
const SimpleTable<TYPE> &SimpleTable<TYPE>::operator=(SimpleTable<TYPE> &&rhs) {
  if (records_) {
    while (numRecords() != 0) {
      remove(records_[0]->key_);
    }
    delete[] records_;
  }
  records_ = rhs.records_;
  capacity_ = rhs.capacity_;
  rhs.records_ = nullptr;
  rhs.capacity_ = 0;

  return *this;
} // T(n) = O(n)
```
### Destructor  
The destructor also loops through the entire array to remove each element (via remove()), and then destroy the object from memory.
In this scenario, remove() will execute in O(1) each time, since the target element will always be the first element it will remove.
Therefore, the destructor will perform in linear time, which is T(n) = O(n)
```c++
template <class TYPE> SimpleTable<TYPE>::~SimpleTable() {
  if (records_) {
    int sz = numRecords();
    for (int i = 0; i < sz; i++) {
      remove(records_[0]->key_);
    }
    delete[] records_;
  }
} // T(n) = O(n)
```  
  
# Part B: Suggestions  
### Suggestion 1:  
The first improvement I can think of, is to improve the performance of the numRecords() function. Currently, this function goes through all the elements
and counts the number of occupied tables. In the worst case, it will loop it reaches the end of the table (is equal to capacity), which takes O(n) time to
process. To improve this execution time, I can introduce a new class member called numRecords_, which increments each time a new record is added, and
decrements when one is removed. By taking care of the tracked number of records this way, numRecords() can simply return the value of the numRecords_,
which will take O(1) constant time to process.
### Suggestion 2:



