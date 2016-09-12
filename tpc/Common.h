#ifndef TPC_COMMON_H
#define TPC_COMMON_H

# include <string>

// Singleton Pattern: Private copy constructor and copy assigment ensure
// classes derived from class noncopyable cannot be copied.
class noncopyable
{
protected:
    noncopyable() {}

private:
    noncopyable(const noncopyable&) = delete;
    void operator=(const noncopyable&) = delete;
};

struct copyable
{
};

// For passing C-style string argument to a function
class StringArg : copyable
{
public:
    StringArg(const char* str) : str_(str) {}

    StringArg(const std::string& str) : str_(str.c_str()) {}

    const char* c_str() const { return str_; }

private:
    const char* str_;
};

template<typename To, typename From>
inline To implicit_cast(const From &f)
{
    return f;
};

#endif //TPC_COMMON_H
