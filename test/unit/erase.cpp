#include <ankerl/unordered_dense.h>

#include <app/checksum.h>
#include <app/nanobench.h>

#include <doctest.h>

#include <algorithm>
#include <unordered_set>

template <typename A, typename B>
[[nodiscard]] auto is_eq(A const& a, B const& b) -> bool {
    if (a.size() != b.size()) {
        return false;
    }
    return std::all_of(a.begin(), a.end(), [&b](auto const& k) {
        return b.end() != b.find(k);
    });
}

TEST_CASE("count") {
    auto uds = ankerl::unordered_dense::set<uint32_t>();
    auto us = std::unordered_set<uint32_t>();
    auto rng = ankerl::nanobench::Rng();
    for (size_t i = 0; i < 10000; ++i) {
        auto key = rng.bounded(1000);
        uds.insert(key);
        us.insert(key);
        REQUIRE(uds.size() == us.size());

        key = rng.bounded(1000);
        uds.erase(key);
        us.erase(key);
        REQUIRE(uds.size() == us.size());
    }
    REQUIRE(is_eq(uds, us));
}
