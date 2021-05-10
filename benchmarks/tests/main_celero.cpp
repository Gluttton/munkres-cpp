#include <celero/Celero.h>
#include <vector>

#include "munkres-cpp/munkres.h"
#include "../../tests/matrix_test_utils.h"



std::vector<munkres_cpp::MUNKRES_CPP_MATRIX_TYPE<MUNKRES_CPP_VALUE_TYPE> *> matrices;

size_t i {0};



class MunkresFixture : public celero::TestFixture
{
    public:
        MunkresFixture ()
            : matrix (1, 1)
        {
        }

        void setUp (const celero::TestFixture::ExperimentValue &) override
        {
            matrix = * matrices [i];
        }

        munkres_cpp::MUNKRES_CPP_MATRIX_TYPE<MUNKRES_CPP_VALUE_TYPE> matrix;
};



BASELINE_F (Munkres, Solve, MunkresFixture, 5000, 1)
{
    munkres_cpp::Munkres<MUNKRES_CPP_VALUE_TYPE> munkres (matrix);
}



int main (int argc, char * argv [])
{
    read (matrices);

    while (i < matrices.size () ) {
        celero::Run (argc, argv);
        ++i;
    }
}
