#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T>
void move_vectors(std::vector<T>& V1, std::vector<T>& V2) { V2 = std::move(V1); }

int main() {
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;
    move_vectors(one, two);

    return EXIT_SUCCESS;
}