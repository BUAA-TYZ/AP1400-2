#ifndef SHARED_PTR
#define SHARED_PTR

#include <atomic>

template<typename T>
class SharedPtr {
public:
    SharedPtr() = default;
    explicit SharedPtr(T* ptr)
        : count(new std::atomic_int(1)), _p(ptr) { }
    SharedPtr(const SharedPtr& sptr)
        : count(sptr.count), _p(sptr._p) { ++(*count); }
    SharedPtr& operator=(const SharedPtr& sptr) {
        // copy and swap
        auto tmp(sptr);
        swap(tmp);
        return *this;
    }
    ~SharedPtr() {
        if (_p) {
            if (--(*count) == 0) {
                delete _p;
                _p = nullptr;
            }
        }
    }

    T operator*() { return *_p; }
    T* operator->() { return _p; }
    explicit operator bool() {
        return _p != nullptr;
    }

    int use_count() { return *count; }
    T* get() { return _p; }
    void reset() {
        this->~SharedPtr();
        _p = nullptr;
    }
    void reset(T* ptr) {
        this->~SharedPtr();
        _p = ptr;
        count = new std::atomic_int (1);
    }

private:
    std::atomic_int* count = nullptr;
    T* _p = nullptr;

    void swap(SharedPtr& sptr) {
        std::swap(count, sptr.count);
        std::swap(_p, sptr._p);
    }
};

template<typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
    return SharedPtr<T>(new T (std::forward<Args>(args)...));
}

#endif //SHARED_PTR