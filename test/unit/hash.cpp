#include <ankerl/unordered_dense.h>

#include <doctest.h>

#include <unordered_set>

TEST_CASE("hash_string") {
    auto h = ankerl::unordered_dense::hash<std::string>();

    auto set = std::unordered_set<uint64_t>();
    auto str = std::string();
    for (size_t l=0; l<100; ++l) {
        set.insert(h(str));
        str.push_back('x');
    }
    REQUIRE(set.size() == 100);
}
