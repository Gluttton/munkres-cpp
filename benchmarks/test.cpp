#include <celero/Celero.h>
#include <vector>

#include "munkres-cpp/munkres.h"
#include "../tests/matrix_test_utils.h"



std::vector<munkres_cpp::MUNKRES_CPP_MATRIX_TYPE<MUNKRES_CPP_VALUE_TYPE> *> matrices;



class MunkresFixture : public celero::TestFixture
{
    public:
        MunkresFixture ()
            : matrix (1, 1)
        {
        }

        std::vector <celero::TestFixture::ExperimentValue> getExperimentValues () const override
        {
            read (matrices);
            std::vector <celero::TestFixture::ExperimentValue> problemSpace;
            for (size_t i = 0; i < matrices.size (); ++i) {
                problemSpace.push_back (i);
            }
            return problemSpace;
        }

        void onExperimentStart (const celero::TestFixture::ExperimentValue & e) override
        {
            matrix = * matrices [e.Value];
        }

        munkres_cpp::MUNKRES_CPP_MATRIX_TYPE<MUNKRES_CPP_VALUE_TYPE> matrix;
};



BASELINE_F (Munkres, Solve, MunkresFixture, 128, 32)
{
    munkres_cpp::Munkres<MUNKRES_CPP_VALUE_TYPE, munkres_cpp::MUNKRES_CPP_MATRIX_TYPE> munkres (matrix);
}



CELERO_MAIN
