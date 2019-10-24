#include "ud_tensor.h"

ud_tensor *ud_tens_init_ctr(size_t *shape, size_t shape_len)
{
    if (shape_len == 0) ud_ut_error("Rank must be greater than 0 (Bad shape <-> length ?)");
    size_t len;
    size_t *shape_m = ud_tens_shape_mult_init(shape, shape_len, &len);
    float *val;
    ud_ut_prot_malloc(val = ud_ut_malloc(sizeof(float) * len));
    ud_tensor *new_tensor = ud_tens_new(val, len, shape, shape_m, shape_len);
    return new_tensor;
}

ud_tensor *ud_tens_init(ud_arr *shape)
{
    ud_ut_count shape_len = shape->len;
    size_t *a_shape = (size_t*)shape->val;
    ud_ut_free(shape);

    ud_tensor *new_tensor = ud_tens_init_ctr(a_shape, shape_len);

    return new_tensor;
}

ud_tensor *ud_tens_init_val(ud_arr *shape, float new_val)
{
    ud_ut_count shape_len = shape->len;
    size_t *a_shape = (size_t*)shape->val;
    ud_ut_free(shape);

    ud_tensor *new_tensor = ud_tens_init_ctr(a_shape, shape_len);
    
    size_t len = new_tensor->len;
    float *val = new_tensor->val;
    while (len-- > 0) *val++ = new_val;
    return new_tensor;
}

ud_tensor *ud_tens_init_id(ud_arr *shape)
{
    ud_ut_count shape_len = shape->len;
    size_t *a_shape = (size_t*)shape->val;
    ud_ut_free(shape);

    ud_tensor *new_tensor = ud_tens_init_ctr(a_shape, shape_len);
    
    size_t len = new_tensor->len;
    float *val = new_tensor->val;
    ud_ut_count new_val = 0;
    while (len-- > 0) *val++ = new_val++;
    return new_tensor;
}

ud_tensor *ud_tens_init_rand(ud_arr *shape, float bound_1, float bound_2)
{
    ud_ut_count shape_len = shape->len;
    size_t *a_shape = (size_t*)shape->val;
    ud_ut_free(shape);

    ud_tensor *new_tensor = ud_tens_init_ctr(a_shape, shape_len);

    size_t len = new_tensor->len;
    float *val = new_tensor->val;
    while (len-- > 0) *val++ = ud_math_rand(bound_1, bound_2);
    return new_tensor;
}