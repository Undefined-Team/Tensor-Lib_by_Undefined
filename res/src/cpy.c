#include "ud_tensor.h"

ud_tensor *ud_tens_cpy(ud_tensor *tensor_src)
{
    ud_ut_count shape_len = tensor_src->shape_len;
    if (shape_len == 0) ud_ut_error("Rank must be greater than 0 (Bad shape <-> length ?)");
    size_t len = tensor_src->len;

    size_t *shape;
    ud_ut_prot_malloc(shape = ud_ut_malloc(sizeof(size_t) * shape_len));
    size_t *tmp_shape = shape;
    size_t *shape_src = tensor_src->shape;
    for (ud_ut_count i = 0; i < shape_len; ++i)
    {
        if (*shape_src == 0) ud_ut_error("Shape can't have a dimension of length 0 (Bad shape)");
        *tmp_shape++ = *shape_src++;
    }
    size_t *shape_m;
    ud_ut_prot_malloc(shape_m = ud_ut_malloc(sizeof(size_t) * shape_len));
    size_t *tmp_shape_m = shape_m;
    size_t *shape_m_src = tensor_src->shape_m;
    for (ud_ut_count i = 0; i < shape_len; ++i) *tmp_shape_m++ = *shape_m_src++;
    
    float *val;
    ud_ut_prot_malloc(val = ud_ut_malloc(sizeof(float) * len));
    ud_tensor *new_tensor = ud_tens_new(val, len, shape, shape_m, shape_len);

    new_tensor->val = val;
    float *val_src = tensor_src->val;
    while (len-- > 0) *val++ = *val_src++;
    return new_tensor;
}