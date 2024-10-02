#include <cstdlib>
#include "../tests/matrix_test_utils.h"

int main (int argc, char * argv [])
{
    using matrix_t = munkres_cpp::Matrix<MUNKRES_CPP_VALUE_TYPE>;

    std::vector<matrix_t *> matrices;
    for (int i = 1; i < argc; ++i) {
        const size_t size = std::stoi (argv [i]);
        matrix_t * matrix = new matrix_t {};
        * matrix = generate_random_matrix<matrix_t>(size, size);
        matrices.push_back (matrix);
    }
    write (matrices);

    return EXIT_SUCCESS;
}
