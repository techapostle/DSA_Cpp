/*************************************************************/
/*                                                           */
/*  Starter file for a2                                      */
/*                                                           */
/*  Author1 Name: Kian Dadkhah Shokrollahi 119369205         */
/*      - class/function list/main author                    */
/*  Author2 Name: Matthew Lee 117715185                      */
/*      - main checker                                       */
/*                                                           */
/*************************************************************/

#ifndef TABLE_H
#define TABLE_H

#include "mylist.h"
#include <functional>
#include <string>
#include <utility>

template <class TYPE> class Table {
public:
  Table() {}
  virtual bool update(const std::string &key, const TYPE &value) = 0;
  virtual bool remove(const std::string &key) = 0;
  virtual bool find(const std::string &key, TYPE &value) = 0;
  virtual int numRecords() const = 0;
  virtual bool isEmpty() const = 0;
  virtual int capacity() const = 0;
  virtual ~Table() {}
};

template <class TYPE> class SimpleTable : public Table<TYPE> {

  struct Record {
    TYPE data_;
    std::string key_;
    Record(const std::string &key, const TYPE &data) {
      key_ = key;
      data_ = data;
    }
  };

  Record **records_; // the table
  int capacity_;     // capacity of the array

public:
  SimpleTable(int capacity);
  SimpleTable(const SimpleTable &rhs);
  SimpleTable(SimpleTable &&rhs);
  virtual bool update(const std::string &key, const TYPE &value);
  virtual bool remove(const std::string &key);
  virtual bool find(const std::string &key, TYPE &value);
  virtual const SimpleTable &operator=(const SimpleTable &rhs);
  virtual const SimpleTable &operator=(SimpleTable &&rhs);
  virtual ~SimpleTable();
  virtual bool isEmpty() const { return numRecords() == 0; }
  virtual int numRecords() const;
  virtual int capacity() const { return capacity_; }
};

template <class TYPE> int SimpleTable<TYPE>::numRecords() const {
  int rc = 0;
  for (int i = 0; records_[i] != nullptr; i++) {
    rc++; // n
  }
  return rc;
} // T(n) = O(n)

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity) : Table<TYPE>() {
  records_ = new Record *[capacity + 1];
  capacity_ = capacity;
  for (int i = 0; i < capacity_ + 1; i++) {
    records_[i] = nullptr;
  }
}

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
}

template <class TYPE> SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE> &&rhs) {
  capacity_ = rhs.capacity_;
  records_ = rhs.records_;
  rhs.records_ = nullptr;
  rhs.capacity_ = 0;
}

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
}

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
}

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
}

template <class TYPE> SimpleTable<TYPE>::~SimpleTable() {
  if (records_) {
    int sz = numRecords();
    for (int i = 0; i < sz; i++) {
      remove(records_[0]->key_);
    }
    delete[] records_;
  }
}

/* 
 * This class is a child of the Table class.
  It implements a Hash Table which uses the
  Seperate Chaining technique to deal with the problem of collision.
  This means each record is a separate linked list, and a new record
  that collides with an existing one is added to the existing record
  as an added node.
 * */
template <class TYPE> class ChainingTable : public Table<TYPE> {
  struct Record {
    TYPE data_;
    std::string key_;
    Record(const std::string &key = "", const TYPE &data = TYPE{}) {
      key_ = key;
      data_ = data;
    }
  };
  DList<Record> *HashTable;
  int capacity_;   // capacity of the array
  int numRecords_; // current number of elements in the array
  std::hash<std::string> hashFunction;

public:
  ChainingTable(int maxExpected);
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

/*
 * 1-arg Constructor initializing numRecords, capacity, and HashTable.
 */
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity) : Table<TYPE>() {
  capacity_ = capacity;
  numRecords_ = 0;
  HashTable = new DList<Record>[capacity + 1];
}

/*
 * Copy Constructor 
 * */
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE> &other) {
  capacity_ = other.capacity_;
  numRecords_ = other.numRecords_;
  HashTable = new DList<Record>[capacity_ + 1];
  for (int i = 0; i < capacity_ + 1; i++) {
    HashTable[i] = other.HashTable[i];
  }
}

/*
 * Move Constructor
 * */
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE> &&other) {
  capacity_ = other.capacity_;
  numRecords_ = other.numRecords_;
  HashTable = std::move(other.HashTable);
  other.HashTable = nullptr;
}

/*
 * This function is passed a key-value pair. If your table already has 
 * a record with a matching key, the record's value is replaced by the 
 * value passed to this function. If no record exists, a record with 
 * key-value pair is added to the table.
 * */
template <class TYPE>
bool ChainingTable<TYPE>::update(const std::string &key, const TYPE &value) {
  bool updated = false;
  auto idx = hashFunction(key) % capacity_;
  if (HashTable[idx].size()) {
    for (auto it = HashTable[idx].begin();
        it != HashTable[idx].end() && !updated; it++) {
      if ((*it).key_ == key) {
        (*it).data_ = value;
        updated = true;
      }
    }
    if (!updated) {
      auto it = HashTable[idx].end();
      HashTable[idx].insert(it, Record(key, value));
      numRecords_++;
      updated = true;
    }
  } else {
    auto it = HashTable[idx].end();
    HashTable[idx].insert(it, Record(key, value));
    numRecords_++;
    updated = true;
  }
  return updated;
}

/* 
 * This function is passed a key. If the table contains a record with a matching key, 
 * the record (both the key and the value) is removed from the table.
 * */
template <class TYPE> bool ChainingTable<TYPE>::remove(const std::string &key) {
  auto idx = hashFunction(key) % capacity_;
  if (HashTable[idx].size()) {
    for (auto it = HashTable[idx].begin(); it != HashTable[idx].end(); it++) {
      if ((*it).key_ == key) {
        HashTable[idx].erase(it);
        numRecords_--;
        return true;
      }
    }
  }
  return false;
}

/* This function is passed a key and a reference for passing back a found value.
 * If the table contains a record with a matching key,
 * the function returns true, and passes back the value from the record.
 * If it does not find a record with a matching key, function returns false.
 * */
template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string &key, TYPE &value) {
  auto idx = hashFunction(key) % capacity_;
  if (HashTable[idx].size()) {
    for (auto it = HashTable[idx].begin(); it != HashTable[idx].end(); it++) {
      if ((*it).key_ == key) {
        value = (*it).data_;
        return true;
      }
    }
  }
  return false;
}

/* Copy Assignment Operator
 * */
template <class TYPE>
const ChainingTable<TYPE> &
ChainingTable<TYPE>::operator=(const ChainingTable<TYPE> &other) {
  if (this != &other) {
    delete[] HashTable;
    capacity_ = other.capacity_;
    numRecords_ = other.numRecords_;
    HashTable = new DList<Record>[capacity_ + 1];
    for (int i = 0; i < capacity_ + 1; i++) {
      HashTable[i] = other.HashTable[i];
    }
  }
  return *this;
}

/* Move Assignment Operator
 * */
template <class TYPE>
const ChainingTable<TYPE> &
ChainingTable<TYPE>::operator=(ChainingTable<TYPE> &&other) {
  if (this != &other) {
    delete[] HashTable;
    capacity_ = other.capacity_;
    numRecords_ = other.numRecords_;
    HashTable = std::move(other.HashTable);
    other.HashTable = nullptr;
  }
  return *this;
}

/* Destructor
 * */
template <class TYPE> ChainingTable<TYPE>::~ChainingTable() {
  capacity_ = 0;
  numRecords_ = 0;
  if (HashTable) {
    delete[] HashTable;
  }
}

template <class TYPE> bool ChainingTable<TYPE>::isEmpty() const {
  return numRecords_ == 0;
}

/* This function returns the number of records in the table. 
 * */
template <class TYPE> int ChainingTable<TYPE>::numRecords() const {
  return numRecords_;
}

/* This function returns capacity of the table.
 * */
template <class TYPE> int ChainingTable<TYPE>::capacity() const {
  return capacity_;
}

/* This function returns the load factor of the table. (number of records divided by capacity of table)
 * */
template <class TYPE> double ChainingTable<TYPE>::loadFactor() const {
  return (double)numRecords_ / (double)capacity_;
}

/*
 * This Table class implements functions for the Linear Probing Hash Table.
 * Albeit in a traditional Linear Probing Hash Table, collisions are not handled
 *  by finding a new index, this LPTable instead uses one update function and
 *  overrides any colliding record with the incoming one. An insert function
 * with Linear Probing is not implemented.
 * */
template <class TYPE> class LPTable : public Table<TYPE> {
  struct Record {
    TYPE data_;
    std::string key_;
    std::string status_;
    Record() :
      data_{},
      key_{""},
      status_{"empty"} {}
    Record(const std::string &key, const TYPE &data, const std::string status) {
      key_ = key;
      data_ = data;
      status_ = status;
    }
  };

  std::hash<std::string> hashFunction;
  Record *records_;
  int capacity_;
  int numRecords_;
public:
  LPTable(int capacity);
  LPTable(const LPTable &other);
  LPTable(LPTable &&other);
  double loadFactor() const;
  virtual bool update(const std::string &key, const TYPE &value);
  virtual bool remove(const std::string &key);
  virtual bool find(const std::string &key, TYPE &value);
  virtual const LPTable &operator=(const LPTable &other);
  virtual const LPTable &operator=(LPTable &&other);
  virtual ~LPTable();
  virtual bool isEmpty() const;
  virtual int numRecords() const;
  virtual int capacity() const;
};

/* 1-Arg Constructor: initializes the capacity, numRecords, and records.
 * */
template <class TYPE> LPTable<TYPE>::LPTable(int capacity) : Table<TYPE>() {
  capacity_ = capacity;
  records_ = new Record[capacity_];
  numRecords_ = 0;
}

/* Copy Constructor
 * */
template <class TYPE> LPTable<TYPE>::LPTable(const LPTable<TYPE> &other) {
  records_ = nullptr;
  *this = other;
}

/* Move Constructor
 * */
template <class TYPE> LPTable<TYPE>::LPTable(LPTable<TYPE> &&other) {
  records_ = nullptr;
  *this = std::move(other);
}

/* This function is passed a key-value pair. If your table already has a record 
 * with a matching key, the record's value is replaced by the value passed to this function. 
 * If no record exists, a record with key-value pair is added to the table.
 * */
template <class TYPE>
bool LPTable<TYPE>::update(const std::string &key, const TYPE &value) {
  auto idx = hashFunction(key) % capacity_;
  auto i = idx;
  do {
    if (records_[idx].status_ == "empty") {
      break;
    } else if (records_[idx].key_.compare(key) == 0) {
      records_[idx].data_ = value;
      return true;
    }
    idx = (idx + 1) % capacity_;
  } while (idx != i);
  if (numRecords_ < capacity_ - 1) {
    records_[idx] = Record(key, value, "full");
    numRecords_++;
    return true;
  }
  return false;
}

/* This function is passed a key. If your table contains a record with a matching key, 
 * the record (both the key and the value) is removed from the table.
 * */
template <class TYPE> bool LPTable<TYPE>::remove(const std::string &key) {
  auto idx = hashFunction(key) % capacity_;
  auto i = idx;
  do {
    if (records_[idx].status_ == "empty") {
      return false;
    } else if (records_[idx].status_ == "full" &&
               records_[idx].key_.compare(key) == 0) {
      records_[idx].status_ = "deleted";
      numRecords_--;
      return true;
    }
    idx = (idx + 1) % capacity_;
  } while (i != idx);
  return false;
}

/* This function is passed a key and a reference for passing back a found value. If the table contains a record with 
 * a matching key, the function returns true, and passes back the value from the record. If it does not find a record 
 * with a matching key, function returns false.
 * */
template <class TYPE>
bool LPTable<TYPE>::find(const std::string &key, TYPE &value) {
  auto idx = hashFunction(key) % capacity_;
  auto i = idx;
  do {
    if (records_[idx].status_ == "empty") {
      return false;
    } else if (records_[idx].status_ == "full" &&
               records_[idx].key_.compare(key) == 0) {
      value = records_[idx].data_;
      return true;
    }
    idx = (idx + 1) % capacity_;
  } while (i != idx);
  return false;
}

/* Copy Assignment Operator
 * */
template <class TYPE>
const LPTable<TYPE> &LPTable<TYPE>::operator=(const LPTable<TYPE> &other) {
  if (this != &other) {
    delete[] records_;
    capacity_ = other.capacity_;
    numRecords_ = other.numRecords_;
    records_ = new Record[capacity_];
    for (int i = 0; i < capacity_; i++) {
      records_[i] = other.records_[i];
    }
  }
  return *this;
}

/* Move Assignment Operator
 * */
template <class TYPE>
const LPTable<TYPE> &LPTable<TYPE>::operator=(LPTable<TYPE> &&other) {
  if (this != &other) {
    records_ = other.records_;
    capacity_ = other.capacity_;
    numRecords_ = other.numRecords_;
    other.records_ = nullptr;
    other.capacity_ = other.numRecords_ = 0;
  }
  return *this;
}

/* Destructor
 * */
template <class TYPE>
LPTable<TYPE>::~LPTable() {
  if (records_) {
    delete[] records_;
  }
}

/* This function returns false if table is empty.
 * */
template <class TYPE>
bool LPTable<TYPE>::isEmpty() const {
  return numRecords_ == 0;
}

/* This function returns the number of records in the table.
 * */
template <class TYPE>
int LPTable<TYPE>::numRecords() const {
  return numRecords_;
}

/* This function returns capacity of the table.
 * */
template <class TYPE>
int LPTable<TYPE>::capacity() const {
  return capacity_;
}

/* This function returns the load factor of the table. (number of records divided by capacity of table)
 * */
template <class TYPE>
double LPTable<TYPE>::loadFactor() const {
  return (double)numRecords_ / (double)capacity_;
}

#endif
