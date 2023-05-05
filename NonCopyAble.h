#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

class NonCopyAble {
public:
    NonCopyAble() = default;
protected:
    virtual ~NonCopyAble() {}
    NonCopyAble(const NonCopyAble& ) = delete;
    NonCopyAble& operator=(const NonCopyAble& ) = delete;

    NonCopyAble(const NonCopyAble&& ) = delete;
    NonCopyAble& operator=(const NonCopyAble&& ) = delete;

};

#endif
