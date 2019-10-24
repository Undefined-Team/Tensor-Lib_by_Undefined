#include "ud_tensor.h"

size_t     *ud_tens_shape_mult_init(size_t *shape, ud_ut_count shape_len, size_t *len)
{
    size_t *shape_m;
    ud_ut_prot_malloc(shape_m = ud_ut_malloc(sizeof(size_t) * shape_len));
    --shape_len;
    size_t *shape_m_tmp = &shape_m[shape_len];
    size_t *shape_m_tmp_2 = shape_m_tmp - 1;
    *shape_m_tmp = 1;
    if (*shape == 0) ud_ut_error("Shape can't have a dimension of length 0 (Bad shape)");
    size_t new_len = 1;
    shape = &shape[shape_len];
    for (ud_ut_count i = shape_len; i > 0; --i)
    {
        if (*shape == 0) ud_ut_error("Shape can't have a dimension of length 0 (Bad shape)");
        *shape_m_tmp_2-- = *shape * *shape_m_tmp--;
        new_len *= *shape--;
    }
    *len = new_len * *shape;
    return shape_m;
}

size_t     *ud_tens_shape_mult(size_t *shape, ud_ut_count shape_len)
{
    size_t *shape_m;
    ud_ut_prot_malloc(shape_m = ud_ut_malloc(sizeof(size_t) * shape_len));
    --shape_len;
    size_t *shape_m_tmp = &shape_m[shape_len];
    size_t *shape_m_tmp_2 = shape_m_tmp - 1;
    *shape_m_tmp = 1;
    if (*shape == 0) ud_ut_error("Shape can't have a dimension of length 0 (Bad shape)");
    shape = &shape[shape_len];
    for (ud_ut_count i = shape_len; i > 0; --i)
    {
        if (*shape == 0) ud_ut_error("Shape can't have a dimension of length 0 (Bad shape)");
        *shape_m_tmp_2-- = *shape-- * *shape_m_tmp--;
    }
    return shape_m;
}