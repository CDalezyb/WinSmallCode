#include <iostream>

namespace MySmartPtr
{
    template <typename T>
    class BaseSmartPtr
    {
    public:
        virtual T &operator*() { return *_ptr; }

        virtual T *operator->() { return _ptr; }

        virtual T *get() { return _ptr; }

    protected:
        BaseSmartPtr() {}

        BaseSmartPtr(T *ptr) : _ptr(ptr) {}
        ~BaseSmartPtr() {}

        void DeletePtr()
        {
            if (_ptr != nullptr)
                delete _ptr;
            _ptr = nullptr;
        }

        T *_ptr = nullptr;
    };

    // 为了方便WeakPtr使用lock函数返回SharedPtr，因此将WeakPtr设置为SharedPtr的友元类。
    // 叠甲-1：我个人认为这不是很好的实现，还有一种实现是在BaseSmartPtr中 定义 _ptr _shared_count 和 _weak_count
    // 叠甲-2：我在CSDN大部分的博客上看到的实现，都不是很完整，尤其是weakPtr的lock,expired,相比较而言，我觉得一起实现三种指针更加考验一个程序员。
    template <typename T>
    class WeakPtr;

    template <typename T>
    class SharedPtr : public BaseSmartPtr<T>
    {
    public:
        friend class WeakPtr<T>;
        SharedPtr() : BaseSmartPtr<T>() {}

        SharedPtr(T *ptr) : BaseSmartPtr<T>(ptr), _count(new long long(1))
        {
            std::cout << "T* ptr constructor of SharedPtr." << std::endl;
        }

        SharedPtr(T *ptr, long long *_count) : BaseSmartPtr<T>(ptr), _count(_count)
        {
            (*_count)++;
            std::cout << "T*  and long long *ptr constructor of SharedPtr(designed for WeakPtr)." << std::endl;
        }

        // copy constructor 拷贝构造函数
        SharedPtr(const SharedPtr<T> &sPtr) : BaseSmartPtr<T>(sPtr._ptr), _count(sPtr._count)
        {
            (*_count)++;
            std::cout << "copy constructor of SharedPtr." << std::endl;
        }

        // move constructor 移动构造函数
        SharedPtr(SharedPtr &&other) : BaseSmartPtr<T>(other._ptr), _count(other._count)
        {
            other._count = nullptr;
            other._ptr = nullptr;
            std::cout << "move constructor of SharedPtr." << std::endl;
        }

        // operator =  赋值运算符（左值）
        SharedPtr<T> &operator=(SharedPtr &other) noexcept
        {
            if (this->_ptr != other._ptr)
            {
                Release();

                this->_ptr = other._ptr;
                _count = other._count;
                ++(*_count);
            }
            std::cout << "operator = of SharedPtr." << std::endl;
            return *this;
        }

        // move operator =
        SharedPtr<T> &operator=(SharedPtr &&other) noexcept
        {
            if (this != &other)
            {
                Release();

                this->_ptr = other._ptr;
                _count = other._count;

                other._count = nullptr;
                other._ptr = nullptr;
            }

            std::cout << "move operator = of SharedPtr." << std::endl;

            return *this;
        }

        ~SharedPtr()
        {
            std::cout << "~ function of SharedPtr." << std::endl;
            Release();
        }

        long long use_count() { return this->_ptr != nullptr ? *_count : 0; }

        void reset(T *ptr = nullptr)
        {
            if (this->_ptr != ptr)
            {
                Release();

                if (ptr != nullptr)
                {
                    this->_ptr = ptr;
                    _count = new long long(1);
                }
                else
                {
                    this->_ptr = nullptr;
                    _count = nullptr;
                }
            }
        }

    protected:
        void Release()
        {
            if (this->_ptr != nullptr) // 在_ptr不为空的情况下，对count--，如果--后count等于0执行函数体内
            {
                (*_count)--;
                if ((*_count) == 0)
                {
                    //
                    this->DeletePtr();
                    delete _count;
                    _count = nullptr;
                    std::cout << " delete SharedPtr source." << std::endl;
                }
            }
        }

        // T *_ptr = nullptr;
        long long *_count = nullptr;
    };

    template <typename T>
    class UniquePtr : public BaseSmartPtr<T>
    {
    public:
        UniquePtr() : BaseSmartPtr<T>() {}

        UniquePtr(T *ptr) : BaseSmartPtr<T>(ptr)
        {
            std::cout << " T* constructor of UniquePtr" << std::endl;
        }

        ~UniquePtr()
        {
            if (this->_ptr != nullptr)
            {
                std::cout << " destructor of UniquePtr and delete corresponding source." << std::endl;
                this->DeletePtr();
            }
        }

        // copy constructor and operator = are deleted to avoid copy
        UniquePtr(const UniquePtr<T> &other) = delete;
        UniquePtr &operator=(const UniquePtr<T> &other) = delete;

        UniquePtr(UniquePtr<T> &&other) : BaseSmartPtr<T>(other._ptr)
        {
            std::cout << "move destructor of UniquePtr." << std::endl;
            other._ptr = nullptr;
        }

        UniquePtr &operator=(UniquePtr<T> &&other) noexcept
        {
            std::cout << "move operator = of UniquePtr" << std::endl;
            if (this != &other)
            {
                if (this->_ptr != nullptr)
                    this->DeletePtr();
                this->_ptr = other._ptr;
                other._ptr = nullptr;
            }

            return *this;
        }

        void reset(T *ptr = nullptr)
        {
            if (this->_ptr != ptr)
            {
                if (this->_ptr != nullptr)
                    this->DeletePtr();
                this->_ptr = ptr;
            }
        }
    };

    template <typename T>
    class WeakPtr : public BaseSmartPtr<T>
    {
    public:
        WeakPtr() : BaseSmartPtr<T>() {}

        WeakPtr(const SharedPtr<T> &otherShared) : BaseSmartPtr<T>(otherShared._ptr), _count(otherShared._count)
        {
            std::cout << " WeakPtr constructed from SharedPtr." << std::endl;
        }

        WeakPtr(const WeakPtr<T> &other) : BaseSmartPtr<T>(other._ptr), _count(other._count)
        {
            std::cout << " WeakPtr constructed from WeakPtr." << std::endl;
        }

        WeakPtr<T> &operator=(const WeakPtr<T> &other)
        {
            std::cout << " WeakPtr oprtator = ." << std::endl;
            this->_ptr = other._ptr;
            _count = other._count;
            return *this;
        }

        ~WeakPtr()
        {
            std::cout << " deconstructor of WeakPtr." << std::endl;
        }

        SharedPtr<T> lock()
        {
            if (*_count > 0)
            {
                return std::move(SharedPtr<T>(this->_ptr, this->_count));
            }
            else
                return SharedPtr<T>();
        }

        bool expired()
        {
            return *(_count) > 0;
        }

    private:
        long long *_count = nullptr;
    };
}

using namespace MySmartPtr;

void TestSharedPtr()
{
    std::cout << "--------------------- Test Sharedptr ---------------------------" << std::endl;
    SharedPtr<int> sPtr1 = new int(1);
    SharedPtr<int> sPtr2 = sPtr1;
    SharedPtr<int> sPtr3(sPtr2);

    *sPtr1 = 100;
    std::cout << "sPtr1:" << *sPtr1 << std::endl;
    std::cout << "sPtr2:" << *sPtr2 << std::endl;
    std::cout << "sPtr3:" << *sPtr3 << std::endl;
    SharedPtr<int> sPtr4(std::move(sPtr3));

    sPtr2 = std::move(sPtr4);
}

struct TestStruct
{
    int x = 0;
    int y = 1;
    TestStruct(int a, int b) : x(a), y(b) {}

    int count()
    {
        return x + y;
    }
};

void TestUniqueptr()
{
    std::cout << "--------------------- Test Uniqueptr ---------------------------" << std::endl;
    UniquePtr<int> uPtr1 = new int(1);

    // UniquePtr<int> uPtr2(uPtr1); 无法调用

    UniquePtr<int> uPtr2 = std::move(uPtr1);
    std::cout << *uPtr2 << std::endl;

    uPtr1 = std::move(uPtr2);

    // UniquePtr<int> uPtr3(std::)

    auto i = uPtr1.get();
    std::cout << *i << std::endl;

    UniquePtr<TestStruct> SUPtr = new TestStruct(10, 11);
    std::cout << SUPtr->x << std::endl;
    std::cout << SUPtr->y << std::endl;
    std::cout << SUPtr->count() << std::endl;
}

void TestWeakPtr()
{
    std::cout << "--------------------- Test Weakptr ---------------------------" << std::endl;
    SharedPtr<int> sPtr = new int(1);
    WeakPtr<int> wPtr1 = sPtr;
    WeakPtr<int> wPtr2 = wPtr1;

    WeakPtr<int> wPtr3;
    wPtr3 = wPtr2;
}

// void

int main()
{

    TestSharedPtr();

    TestUniqueptr();

    TestWeakPtr();

    return 0;
}