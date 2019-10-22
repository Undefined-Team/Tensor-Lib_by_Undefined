#include "ud_tensor.h"

ud_tensor   *ud_tens_flatten_cpy(ud_tensor *tensor)
{
    ud_tensor           *flat;
    ud_arr_size_t_a     *len;

    len = ud_arr_tset(size_t, ud_arr_type_size_t(), 1, tensor->len);
    flat = ud_tens_init(len);
    ud_mem_cpy(flat->val, tensor->val, flat->len * sizeof(float));
    return (flat);
}

ud_tensor   *ud_tens_flatten(ud_tensor *tensor)
{
    size_t *shape = ud_ut_malloc(sizeof(size_t));
    *shape = tensor->len;
    ud_ut_free(tensor->shape);
    tensor->shape = shape;
    ud_ut_free(tensor->shape_m);
    size_t *shape_m = ud_ut_malloc(sizeof(size_t));
    *shape_m = 1;
    tensor->shape_m = shape_m;
    tensor->shape_len = 1;
    tensor->len = *(tensor->shape);
    return (tensor);
}