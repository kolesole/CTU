/// A trivial concurrent hash set data structure, using a mutex per each bucket,
/// without any top-level locking. Does not support reallocation.

#include <forward_list>
#include <mutex>
#include <memory>
#include <array>
#include <unordered_set>
#include <iostream>

template<typename T, size_t BucketCount>
class concurrent_hash_set {
private:
    // forward declaration
    class bucket;

    std::array<bucket, BucketCount> buckets{};

public:
    void add(T item) {
        auto& bucket = get_bucket(item);

        auto lock = std::unique_lock(bucket.m);
        bucket.items.insert(item);
    }

    bool contains(T item) {
        auto& bucket = get_bucket(item);

        auto lock = std::unique_lock(bucket.m);
        return bucket.items.contains(item);
    }

    void erase(T item) {
        auto& bucket = get_bucket(item);

        auto lock = std::unique_lock(bucket.m);
        bucket.items.erase(item);
    }

private:
    bucket& get_bucket(const T& item) {
        auto hash = std::hash<T>()(item);
        return buckets[hash % BucketCount];
    }

    class bucket {
    public:
        std::mutex m;
        // ideally, we should take care to use a different hash function than the set
        std::unordered_set<T> items{};
    };
};

int main() {
    auto set = concurrent_hash_set<uint32_t, 32>();

    set.add(1);
    set.add(2);
    set.add(3);

    std::cout << "contains 1? " << set.contains(1) << "\n";
    set.erase(1);
    std::cout << "contains 1? " << set.contains(1) << "\n";
}
