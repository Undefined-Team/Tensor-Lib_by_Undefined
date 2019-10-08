#include "ud_tensor.h"

void    ud_tens_free(ud_tensor *tensor)
{
    ud_ut_free(tensor->val);
    ud_ut_free(tensor->shape);
    ud_ut_free(tensor->shape_m);
    ud_ut_free(tensor);
}