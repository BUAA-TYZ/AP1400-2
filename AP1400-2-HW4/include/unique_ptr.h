#ifndef UNIQUE_PTR
#define UNIQUE_PTR


template<typename T>
class UniquePtr {
public:
    UniquePtr() = default;
    explicit UniquePtr(T* ptr) {
        _p = ptr;
    }
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    ~UniquePtr() { delete _p; }

    T operator*() { return *_p; }
    T* operator->() { return _p; }
    explicit operator bool() {
        return _p != nullptr;
    }

    T* get() { return _p; }
    void reset();
    void reset(T* ptr);
    T* release();

private:
    T* _p = nullptr;
};

template<typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T (std::forward<Args>(args)...));
}

template<typename T>
void UniquePtr<T>::reset() {
    delete _p;
    _p = nullptr;
}

template<typename T>
void UniquePtr<T>::reset(T* ptr) {
    delete _p;
    _p = ptr;
}

template<typename T>
T* UniquePtr<T>::release() {
    T* res = _p;
    _p = nullptr;
    return res;
}








#endif //UNIQUE_PTR