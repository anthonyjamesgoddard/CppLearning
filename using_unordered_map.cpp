#include <iostream>
#include <unordered_map>
using index_pair = std::pair<std::size_t, std::size_t>;

// this file is just a template for understanding
// how we might implement hash's for user defined 
// keys in an unordered_map. In this case
// our "user-defined" type is index_pair above.
// This "comes with" a == operator.
//
// If our user defined type was a little more
// exotic we would have to explicity give
// it a == operator :)

namespace std {
template <>
struct hash<index_pair> {
    std::size_t operator()(const index_pair& ip) const {
        std::cout << "by modifying std" << std::endl;
        return std::hash<std::size_t>()(ip.first) ^
               (std::hash<std::size_t>()(ip.second));
    }
};
}  // namespace std

struct index_pair_hash {
    std::size_t operator()(const index_pair& ip) const {
        std::cout << "explicitly defining hash " << std::endl;
        return std::hash<std::size_t>()(ip.first) ^
               (std::hash<std::size_t>()(ip.second));
    }
};

int main() {
    std::unordered_map<index_pair, float, index_pair_hash> ipmap; 
    std::unordered_map<index_pair, float> ipmap1;

    const index_pair p = std::make_pair(1,1);
    const index_pair a = std::make_pair(1,1);
    
    if(a == p) {
        std::cout << "they are equal" << std::endl;
    }
    
    ipmap1[a] = 3.0f;
    ipmap[a] = 3.0f;
}
