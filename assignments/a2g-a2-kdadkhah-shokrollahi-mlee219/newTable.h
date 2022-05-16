// This class is a child of the Table class.
// It implements a Hash Table which uses the 
//  Seperate Chaining technique to deal with the problem of collision.
// This means each record is a separate linked list, and a new record 
//  that collides with an existing one is added to the existing record
//  as an added node.
template <class TYPE> class ChainingTable : public Table<TYPE> {
  struct Record {
    TYPE data_;
    std::string key_;
    Record(const std::string &key, const TYPE &data) {
      key_ = key;
      data_ = data;
    }
  };
  int capacity_ = 0;
  int numRecord_ = 0;
  DList<Record*> *HashTable;
  std::hash<std::string> hashFunction;
public:
  ChainingTable(int capacity);
  ChainingTable(const ChainingTable &other);
  ChainingTable(ChainingTable &&other);
  double loadFactor() const;
  virtual bool update(const std::string &key, const TYPE &value);
  virtual bool remove(const std::string &key);
  virtual bool find(const std::string &key, TYPE &value);
  virtual const ChainingTable &operator=(const ChainingTable &other);
  virtual const ChainingTable &operator=(ChainingTable &&other);
  virtual ~ChainingTable();
  virtual bool isEmpty() const;
  virtual int numRecords() const;
  virtual int capacity() const;
};

// This constructor takes an int capacity and initializes a new HashTable
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity) : Table<TYPE>() {
  capacity_ = capacity;
  HashTable = new DList<Record*>[capacity_];
}

// Copy Constructor
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE> &other) {
  if (other.HashTable) { // this may not work, possibly use isEmpty()
    HashTable = nullptr;
    *this = other;
    // if (HashTable) { // this may not work. possibly will need isEmpty()
    //   for (int i = 0; i < capacity_; i++) {
    //     for (auto table : HashTable[i]) {
    //       delete table;
    //     }
    //   }
    // }
    // capacity_ = other.capacity_;
    // numRecord_ = other.numRecord_;
    // HashTable = new DList<Record*>[capacity_];
    // for (int i = 0; i < capacity_; i++) {
    //   for (auto table : other.HashTable[i]) {
    //     struct Record *tempRecord = new Record(table->key_, table->data_);
    //     HashTable[i].insert(HashTable[i].begin(), tempRecord);
    //   }
    // }
  }
}

// Move Constructor
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE> &&other) {
  if (other.HashTable) { // this may not work, possibly use isEmpty()
    HashTable = nullptr;
    *this = std::move(other);
    other.HashTable = nullptr;
    // capacity_ = other.capacity_;
    // numRecord_ = other.numRecord_;
    // HashTable = other.HashTable;
    // other.capacity_ = 0;
    // other.numRecord_ = 0;
    // other.HashTable = nullptr;
  }
}

// Update function adds a new record or updates an existing record if it already exists.
// It accepts a key, used to find an existing record, and a value to which the value of the
//  found record is written.
// In the ChainingTable implementation, collisions are handled by adding a new record
//  to the corresponding linked list.
template <class TYPE>
bool ChainingTable<TYPE>::update(const std::string &key, const TYPE &value) {
  // create new hash key value
  auto hashValue = hashFunction(key);
  int idx = hashValue % capacity_;
  // check for collision
  TYPE tempValue;
  if (find(key, tempValue)) {
    // if collision exists, add new record node to the target idx
    for (auto table : HashTable[idx]) {
      if (table->key_ == key) {
        HashTable[idx].insert(HashTable[idx].begin(), new Record(key, value));
        break;
      }
    }
    return true;
  } else {
    // create a new record with specified key and value pair
    HashTable[idx].insert(HashTable[idx].begin(), new Record(key, value));
    numRecord_++;
    return true;
  }
  return false;
}

// The remove function accepts a key and matches it to a record within the table,
//  which is then removed. Returns true if this process is successful
template <class TYPE> bool ChainingTable<TYPE>::remove(const std::string &key) {
  TYPE tempValue;
  bool exists = find(key, tempValue);
  if (exists) {
    auto hashValue = hashFunction(key);
    int idx = hashValue % capacity_;
    for (auto it = HashTable[idx].begin(); it != HashTable[idx].end();) {
      it = HashTable[idx].erase(it);
    }
    // for (auto node : HashTable[idx]) {
    //   delete node;
    // }
    numRecord_--;
  }
  return exists;
}

// This function finds a record matching its incoming key parameter.
// If a record is found, its data is written to the incoming value parameter,
//  and the function returns true, otherwise false.
template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string &key, TYPE &value) {
  auto hashValue = hashFunction(key);
  int idx = hashValue % capacity_;
  for (auto table : HashTable[idx]) {
    if (table->key_ == key) {
      value = table->data_;
      // std::cout << "found" << std::endl;
      return true;
    }
  }
  return false;
}

// Copy assignment operator
template <class TYPE>
const ChainingTable<TYPE> &
ChainingTable<TYPE>::operator=(const ChainingTable<TYPE> &other) {
  if (other.HashTable && HashTable != other.HashTable) { // other.HashTable may not work, and second clause may need comparison overload
    if (HashTable) {  // may not work, instead use isEmpty()
      for (int i = 0; i < capacity_; i++) {
        for (auto table : HashTable[i]) {
          delete table;
        }
      }
    }
    delete[] HashTable;
    capacity_ = other.capacity_;
    numRecord_ = other.numRecord_;
    HashTable = new DList<Record*>[capacity_];
    for (int i = 0; i < capacity_; i++) {
      for (auto table : other.HashTable[i]) {
        struct Record *tempRecord = new Record(table->key_, table->data_);
        HashTable[i].insert(HashTable[i].begin(), tempRecord);
      }
    }
  }
  return *this;
}

// Move assignment operator
template <class TYPE>
const ChainingTable<TYPE> &
ChainingTable<TYPE>::operator=(ChainingTable<TYPE> &&other) {
  if (other.HashTable && HashTable != other.HashTable) { // this may not work
    if (HashTable) {
      for (int i = 0; i < capacity_; i++) {
        for (auto table : HashTable[i]) {
          delete table;
        }
      }
    }
    delete[] HashTable;
    capacity_ = other.capacity_;
    numRecord_ = other.numRecord_;
    HashTable = new DList<Record*>[capacity_];
    for (int i = 0; i < capacity_; i++) {
      for (auto table : other.HashTable[i]) {
        HashTable[i].insert(HashTable[i].begin(), table);
      }
    }
    for (int i = 0; i < other.capacity_; i++) {
      auto it = other.HashTable[i].begin();
      while (true) {
        it = HashTable[i].erase(it);
        if (it == HashTable[i].end())
          break;
      }
    }
    other.HashTable = nullptr;
  }
  return *this;
}

// Destructor
template <class TYPE> ChainingTable<TYPE>::~ChainingTable() {
  // for (int i = 0; i < capacity_; i++) {
  //   for (auto node : HashTable[i]) {
  //     delete node;
  //   }
  // }
  // numRecord_ = 0;
  // capacity_ = 0;
  delete[] HashTable;
}

template <class TYPE> bool ChainingTable<TYPE>::isEmpty() const { 
  return numRecord_ == 0; 
}

template <class TYPE> int ChainingTable<TYPE>::numRecords() const { 
  return numRecord_; 
}

template <class TYPE> int ChainingTable<TYPE>::capacity() const { 
  return capacity_; 
}

template <class TYPE> double ChainingTable<TYPE>::loadFactor() const { 
  return (double)numRecord_ / (double)capacity_; 
}

