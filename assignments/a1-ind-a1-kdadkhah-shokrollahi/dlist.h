/********************************************************************/
/*                                                                  */
/*  A1 Part 2: DList starter file                                   */
/*                                                                  */
/*  Author1 Name: Kian Dadkhah Shokrollahi                          */
/*      - class/function list/main author or main checker           */
/*  Author2 Name: <name here>                                       */
/*      - class/function list/main author or main checker           */
/*                                                                  */
/********************************************************************/

#ifndef DLIST_H
#define DLIST_H

#include <iostream>

template <typename T>
class DList {
  struct Node {
    T data_;
    Node* next_;
    Node* prev_;

    Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr)
      : data_{data}, next_{next}, prev_{prev} {}
  };

  Node* front_;
  Node* back_;

public:

  class const_iterator {
    friend class DList;
    Node* curr_;
    const DList* list_;
    const_iterator(Node* n, const DList* t) : curr_{n}, list_{t} {}
  public:
    const_iterator() : curr_{nullptr}, list_{nullptr} {}
    const T& operator*() const { return curr_->data_; }

    const_iterator operator++() {
      if (curr_)
        curr_ = curr_->next_;
      return *this;
    }
    const_iterator operator++(int) {
      auto old = *this;
      if (curr_)
        curr_ = curr_->next_;
      return old;
    }
    const_iterator operator--() {
      if (curr_)
        curr_ = curr_->prev_;
      else if (list_->back_)
        curr_ = list_->back_;
      return *this;
    }
    const_iterator operator--(int) {
      auto old = *this;
      if (curr_)
        curr_ = curr_->prev_;
      else if (list_->back_)
        curr_ = list_->back_;
      return old;
    }
    T& operator[](int n) {
      n = n < 0 ? 0 : n;
      for(int i = 0; i < n; n++){
        if (curr_)
          this->operator++();
      }
      return *this->curr_->data_;
    }
    bool operator==(const const_iterator& rhs) const {
      return curr_ == rhs.curr_ && list_ == rhs.list_;
    }
    bool operator!=(const const_iterator& rhs) const {
      return curr_ != rhs.curr_ || list_ != rhs.list_;
    }
  };

  class iterator : public const_iterator {
    friend class DList;
    iterator(Node* n, const DList* l) : const_iterator(n, l) {}
  public:
    iterator() : const_iterator() {}
    T& operator*() { return this->curr_->data_; }
    const T& operator*() const { return this->curr_->data_; }
    iterator operator++() {
      if (this->curr_)
        this->curr_ = this->curr_->next_;
      return *this;
    }
    iterator operator++(int) {
      auto old = *this;
      if (this->curr_)
        this->curr_ = this->curr_->next_;
      return old;
    }
    iterator operator--() {
      if (this->curr_)
        this->curr_ = this->curr_->prev_;
      else if (this->list_->back_)
        this->curr_ = this->list_->back_;
      return *this;
    }
    iterator operator--(int) {
      auto old = *this;
      if (this->curr_)
        this->curr_ = this->curr_->prev_;
      else if (this->list_->back_)
        this->curr_ = this->list_->back_;
      return old;
    }
    bool operator==(const iterator& rhs) const {
      return this->curr_ == rhs.curr_ && this->list_ == rhs.list_;
    }
    bool operator!=(const iterator& rhs) const {
      return this->curr_ != rhs.curr_ || this->list_ != rhs.list_;
    }
  };
  
  DList() : front_{nullptr}, back_{nullptr} {}
  ~DList();
  DList(const DList&);
  DList& operator=(const DList&);
  DList(DList&& rhs);
  DList& operator=(DList&&);
  iterator insert(iterator, const T&);
  iterator search(const T&);
  iterator erase(iterator);
  void sort(iterator, iterator);
  bool empty() const;
  int size() const;

  const_iterator cbegin() const {
    return const_iterator(front_, this);
  }
  iterator begin() {
    return iterator(front_, this);
  }
  const_iterator cend() const {
    return const_iterator(nullptr, this);
  }
  iterator end() {
    return iterator(nullptr, this);
  }
};

template <typename T>
DList<T>::~DList() {
  Node* n = nullptr;
  while (front_) {
    n = front_;
    front_ = front_->next_;
    delete n;
  }
}

template <typename T>
DList<T>::DList(const DList& rhs) {
  front_ = nullptr;
  back_ = nullptr;
  Node* n = rhs.front_;
  while (n) {
    insert(end(), n->data_);
      n = n->next_;
  }
}

template <typename T>
DList<T>& DList<T>::operator=(const DList& rhs) {
  if (this != &rhs) {
    Node* n = nullptr;
    while (front_) {
      n = front_;
      front_ = front_->next_;
      delete n;
    }
    front_ = nullptr;
    back_ = nullptr;
    for (Node* nn = rhs.front_; nn != nullptr; nn = nn->next_) {
      insert(end(), nn->data_);
    }
  }
  return *this;
}

template <typename T>
DList<T>::DList(DList&& rhs) {
  front_ = rhs.front_;
  back_ = rhs.back_;
  rhs.front_ = nullptr;
  rhs.back_ = nullptr;
}

template <typename T>
DList<T>& DList<T>::operator=(DList&& rhs) {
  if (this != &rhs) {
    Node* n = nullptr;
    while (!empty()) {
      n = front_;
      front_ = front_->next_;
      delete n;
    }
    front_ = rhs.front_;
    back_ = rhs.back_;
    rhs.front_ = nullptr;
    rhs.back_ = nullptr;
  }
  return *this;
}

template <typename T>
typename DList<T>::iterator DList<T>::insert(iterator it1, const T& data) {
  Node* a = new Node(data);
  if (it1.curr_ == nullptr) {
    if (front_ == nullptr) {
      front_ = a;
      back_ = a;
    }
    else {
      a->prev_ = back_;
      back_->next_ = a;
      back_ = a;
    }
  }
  else {
    if (it1.curr_ == front_) {
      a->next_ = front_;
      front_->prev_ = a;
      front_ = a;
    }
    else {
      a->next_ = it1.curr_;
      a->prev_ = it1.curr_->prev_;
      it1.curr_->prev_->next_ = a;
      it1.curr_->prev_ = a;
    }
  }
  return iterator(a, this);
}

template <typename T>
typename DList<T>::iterator DList<T>::search(const T& data) {
  for (auto i = begin(); i != end(); i++) {
    if (*i == data)
      return i;
  }
  return end();
}

template <typename T>
typename DList<T>::iterator DList<T>::erase(iterator it1) {
  if (it1.curr_ == nullptr) {
    return end();
  }
  else {
    if (it1.curr_ == front_) {
      front_ = front_->next_;
      front_->prev_ = nullptr;
    }
    else {
      it1.curr_->prev_->next_ = it1.curr_->next_;
      if (it1.curr_ == back_) {
        back_ = it1.curr_->prev_;
      }
      else {
        it1.curr_->next_->prev_ = it1.curr_->prev_;
      }
    }
      Node* a = it1.curr_;
      it1.curr_ = it1.curr_->next_;
      delete a;
      return it1;
  }
}

template <typename T>
void DList<T>::sort(iterator first, iterator last) {
  Node* curr;
  iterator it1 = first;
  iterator it2;
  ++it1;

  Node* smallPrev = nullptr;
  Node* smallNum = nullptr;
  Node* smallNext = nullptr;

  Node* highPrev = nullptr;
  Node* highNum = nullptr;
  Node* highNext = nullptr;

  if (this->size() == 2 && it1.curr_->prev_->data_.count_ > it1.curr_->data_.count_) {
    highNum = it1.curr_->prev_;
    smallNum = it1.curr_;

    front_ = smallNum;
    highNum->next_ = smallNum->next_;
    smallNum->prev_ = highNum->prev_;
    highNum->prev_ = smallNum;
    smallNum->next_ = highNum;
    back_ = highNum;
  }
  if (this->size() > 2 && last.curr_ == nullptr && first.curr_->prev_ == nullptr) {
    for (it1 = it1++; it1 != last; it1++) {
      curr = it1.curr_;
      for (it2 = it1; it2.curr_->prev_ != nullptr && it2.curr_->prev_->data_.count_ > curr->data_.count_;) {
        --it2;
        smallNum = it2.curr_->next_;
        highNum = it2.curr_;
        if (highNum->data_.count_ > smallNum->data_.count_) {
          smallPrev = it1.curr_->prev_;
          smallNext = smallNum->next_;

          highNext = it2.curr_->next_;
          highPrev = it2.curr_->prev_;

          highNum->next_ = smallNext;
          if (smallNext != nullptr)
            smallNext->prev_ = highNum;
          else
            back_ = highNum;
        }
      }
      if (it2.curr_ != curr) {
        curr->prev_ = it2.curr_->prev_;
        curr->next_ = it2.curr_;
        it2.curr_->prev_ = curr;
        if (curr->prev_ == nullptr)
          front_ = curr;
        else
          curr->prev_->next_ = curr;
      }
    }
  } else if(first.curr_->prev_ != nullptr){
    --first;
    for (it1 = first; it1 != last; it1++) {
      curr = it1.curr_;
      for (it2 = it1; it2.curr_->prev_ != first.curr_ && it1.curr_->prev_ != nullptr && it2.curr_->prev_->data_.count_ > curr->data_.count_;) {
        --it2;
        smallNum = it2.curr_->next_;
        highNum = it2.curr_;
        if (highNum->data_.count_ > smallNum->data_.count_) {
          smallPrev = it1.curr_->prev_;
          smallNext = smallNum->next_;

         highNext = it2.curr_->next_;
          highPrev = it2.curr_->prev_;

          highNum->next_ = smallNext;
          if (smallNext != nullptr)
            smallNext->prev_ = highNum;
          else
            back_ = highNum;
        }
      }
      if (it2.curr_ != curr) {
        curr->prev_ = it2.curr_->prev_;
        curr->next_ = it2.curr_;
        it2.curr_->prev_ = curr;
        if (curr->prev_ == nullptr)
          front_ = curr;
        else
          curr->prev_->next_ = curr;
      }
    }
  }
  else {
    for (it1 = first; it1 != last; it1++) {
      curr = it1.curr_;
      for (it2 = it1; it1.curr_ != first.curr_ && it2.curr_->prev_ != nullptr && it2.curr_->prev_->data_.count_ > curr->data_.count_;) {
        --it2;
        smallNum = it2.curr_->next_;
        highNum = it2.curr_;
        if (highNum->data_.count_ > smallNum->data_.count_) {
          smallPrev = it1.curr_->prev_;
          smallNext = smallNum->next_;

          highNext = it2.curr_->next_;
          highPrev = it2.curr_->prev_;

          highNum->next_ = smallNext;
          if (smallNext != nullptr)
            smallNext->prev_ = highNum;
          else
            back_ = highNum;
        }
      }
      if (it2.curr_ != curr) {
        curr->prev_ = it2.curr_->prev_;
        curr->next_ = it2.curr_;
        it2.curr_->prev_ = curr;
        if (curr->prev_ == nullptr)
          front_ = curr;
        else
          curr->prev_->next_ = curr;
      }
    }
  }
}

template <typename T>
bool DList<T>::empty() const {
  return front_ == nullptr;
}

template <typename T>
int DList<T>::size() const {
  int size = 0;
  for (auto i = cbegin(); i != cend(); i++)
    ++size;
  return size;
}

#endif // DLIST_H
