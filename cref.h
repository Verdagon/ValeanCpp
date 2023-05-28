#ifndef VALEAN_CREF_
#define VALEAN_CREF_

#include <utility>

template<typename T>
class cowned;

template<typename T>
class cref;

template<typename T>
class cref_guard;

template<typename T>
class cref {
public:
  cref(cowned<T>* own_) :
      own(own_) {
    own->refCount++;
  }
  ~cref() {
  	own->refCount--;
  }

  cref_guard<T> open() {
    return cref_guard<T>(own);
  }

private:
  cowned<T>* own;
};

template<typename T>
class cref_guard {
public:
  cref_guard(cowned<T>* own_) :
      own(own_) {
    assert(own->present);
    own->present = false;
  }
  ~cref_guard() {
    own->present = true;
  }

  T& operator*() { return own->contents; }
  const T& operator*() const { return own->contents; }
  T* operator->() { return &own->contents; }
  const T* operator->() const { return &own->contents; }

private:
  cowned<T>* own;
};

template<typename T>
class cowned {
public:
  cowned(T contents_) :
      present(true),
      refCount(0),
      contents(std::move(contents_)) {}
  ~cowned() {
  	assert(present);
  	assert(refCount == 0);
  }

  cref<T> ref() {
  	return cref<T>(this);
  }

private:
  friend class cref<T>;
  friend class cref_guard<T>;

  bool present : 1;
  size_t refCount : 63;
  T contents;
};

template<typename T, typename... P>
cowned<T> make_cowned(P&&... params) {
  return cowned<T>(T(std::forward<P>(params)...));
}

#endif
