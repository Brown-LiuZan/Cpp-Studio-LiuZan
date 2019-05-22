#include "assert.h"

namespace liuzan {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
    // GCC won't deduplicate template specialization, so they must reside in
    // .cxx files.
    template<>
    void __DynamicAssert__<false>(bool inPredicate, std::string const & inMsg)
    {}

    template<>
    void __DynamicAssert__<false>(bool inPredicate, char const * inMsg)
    {}

    template<>
    void __DynamicAssert__<false>(bool inPredicate)
    {}
#pragma GCC diagnostic pop

} // namespace liuzan
