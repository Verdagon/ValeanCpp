#ifndef VALEAN_VREF_
#define VALEAN_VREF_

#include <utility>

extern size_t vrefNextKey;

template<typename T>
class vowned;

template<typename T>
class vref;

template<typename T>
class vref_guard;

template<typename T>
class vref {
public:
  vref(vowned<T>* own_) :
    own(own_),
    rememberedKey(own_->currentKey) {}
  ~vref() {}

  vref_guard<T> open() {
    return vref_guard<T>(own, rememberedKey);
  }

private:
  size_t rememberedKey;
  vowned<T>* own;
};

template<typename T>
class vref_guard {
public:
  vref_guard(vowned<T>* own_, size_t rememberedKey) :
      own(own_) {
    assert(rememberedKey == own->currentKey);
    assert(own->present);
    own->present = false;
  }
  ~vref_guard() {
    own->present = true;
  }

  T& operator*() { return own->contents; }
  const T& operator*() const { return own->contents; }
  T* operator->() { return &own->contents; }
  const T* operator->() const { return &own->contents; }

private:
  vowned<T>* own;
};

template<typename T>
class vowned {
public:
  vowned(T contents_) :
      present(true),
      currentKey(vrefNextKey++),
      contents(std::move(contents_)) {}
  ~vowned() {
  	assert(present);
  }

  vref<T> ref() {
  	return vref<T>(this);
  }

private:
  friend class vref<T>;
  friend class vref_guard<T>;

  bool present : 1;
  size_t currentKey : 63;
  T contents;
};

template<typename T, typename... P>
vowned<T> make_vowned(P&&... params) {
  return vowned<T>(T(std::forward<P>(params)...));
}

#endif
