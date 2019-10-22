#include "ud_tensor.h"

ud_tensor   *ud_tens_matrixdot(ud_tensor *a, ud_tensor *b)
{
    ud_tensor   *result;
    size_t      x_a = a->shape[0];
    size_t      x_b = b->shape[0];
    size_t      y_a = a->shape[1];
    size_t      y_b = b->shape[1];

    if (a->shape_len != 2 || b->shape_len != 2)
        ud_ut_error("Can't do matrix dot product on tensor with %zd dimensions and tensor with %zd dimensions.\n", a->shape_len, b->shape_len);
    else if (y_a != x_b)
        ud_ut_error("Matrix [%zd, %zd] incompatible with matrix [%zd, %zd].\n", x_a, y_a, x_b, y_b);
    ud_arr *tens_shape = ud_arr_tset(size_t, ud_arr_type_size_t(), x_a, y_b);
    result = ud_tens_init(tens_shape);

    float *t_result_val = (float *)result->val;
    float *t_a_val = (float *)a->val;
    float *t_b_val = (float *)b->val;

    for (size_t k = 0; k < x_a; k++)
        for (size_t l = 0; l < y_b; l++)
        {
            float sum = 0;
            for (size_t j = 0; j < y_a; j++)
                sum += t_a_val[(k * y_a) + j] * t_b_val[(j * y_b) + l];
            *(t_result_val++) = sum;
        }
    return (result);
}