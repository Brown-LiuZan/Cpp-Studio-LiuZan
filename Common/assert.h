#ifndef LIUZAN_COMMON_ASSERT_H
#define LIUZAN_COMMON_ASSERT_H


#include <stdexcept> //std::runtime_error
#include <string>
#include <iostream> //std::cerr
#include <exception> //std::terminate()


namespace liuzan
{
    enum DynamicAssertActionLevel
    {
        LZ_DAAL_NONE,
        LZ_DAAL_ERROR_MESSAGE,
        LZ_DAAL_THROW_EXCEPTION,
        LZ_DAAL_ABORT,
        LZ_DAAL_MAX
    };

/**
 * In DEBUG mode:
 *     Failed assert always abort process and generate a core.
 * In non-DEBUG mode:
 *     DYNAMIC_ASSERT_ERRMSG > DYNAMIC_ASSERT_EXCEPTION > DYNAMIC_ASSERT_ABORT
 *     Actually, DEFAULT_DAAL could never be specified by user.
 *     Instead and for clarification, user shall use one of three DYNAMIC_ASSERT_* exclusively.
 *     If none of three macro is defined, LZ_DAAL_NONE will be assigned to DEFUALT_DAAL and __DynamicAssert__ will be
 *     optimized out by compiler.
 * */
#ifdef DEBUG
#define DEFUALT_DAAL liuzan::LZ_DAAL_ABORT
#else //!DEBUG
#if defined(DYNAMIC_ASSERT_ERRMSG)
#define DEFUALT_DAAL liuzan::LZ_DAAL_ERROR_MESSAGE
#elif defined(DYNAMIC_ASSERT_EXCEPTION)
#define DEFUALT_DAAL liuzan::LZ_DAAL_THROW_EXCEPTION
#elif defined(DYNAMIC_ASSERT_ABORT)
#define DEFUALT_DAAL liuzan::LZ_DAAL_ABORT
#else //Nothing defined
#define DEFUALT_DAAL liuzan::LZ_DAAL_NONE
#endif //DYNAMIC_ASSERT_*
#endif //DEBUG

    class AssertException : public std::runtime_error
    {
    public:
        explicit AssertException(std::string const & inMsg)
            : std::runtime_error(inMsg)
        {}

        explicit AssertException(char const * inMsg)
            : std::runtime_error(inMsg)
        {}
    };

    template<DynamicAssertActionLevel DAAL>
    constexpr bool AssertIsWorkable() { return DAAL > LZ_DAAL_NONE; }

    template<bool Workable = AssertIsWorkable<DEFUALT_DAAL>()>
    void __DynamicAssert__(bool inPredicate, std::string const & inMsg)
    {
        if (inPredicate) return;

        switch (DEFUALT_DAAL)
        {
            case LZ_DAAL_ERROR_MESSAGE:
                {
                    std::cerr << "Assert Failed: " << inMsg << std::endl;
                    break;
                }
            case LZ_DAAL_THROW_EXCEPTION:
                {
                    throw AssertException(inMsg);
                }
            case LZ_DAAL_ABORT:
                {
                    std::terminate();
                }
            default:
                {
                    break;
                }
        }
    }

    template<bool Workable = AssertIsWorkable<DEFUALT_DAAL>()>
    void __DynamicAssert__(bool inPredicate, char const * inMsg)
    {
        std::string vTempStr(inMsg);
        __DynamicAssert__<Workable>(inPredicate, vTempStr);
    }

    template<bool Workable = AssertIsWorkable<DEFUALT_DAAL>()>
    void __DynamicAssert__(bool inPredicate)
    {
        std::string vTempStr("");
        __DynamicAssert__<Workable>(inPredicate, vTempStr);
    }
}  // namesapce liuzan

#define DynamicAssert liuzan::__DynamicAssert__<>
#define StaticAssert static_assert

#endif // LIUZAN_COMMON_ASSERT_H
