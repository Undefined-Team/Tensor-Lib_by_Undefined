#include "ud_tensor.h"

ud_tensor *ud_tens_new(float *val, size_t len, size_t *shape, size_t *shape_m, size_t shape_len)
{
    ud_tensor *new_tensor;
    UD_UT_PROT_MALLOC(new_tensor = ud_ut_malloc(sizeof(ud_tensor)));
    new_tensor->val = val;
    new_tensor->len = len;
    new_tensor->shape = shape;
    new_tensor->shape_m = shape_m;
    new_tensor->shape_len = shape_len;
    return new_tensor;
}