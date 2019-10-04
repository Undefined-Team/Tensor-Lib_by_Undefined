#include "ud_tensor.h"

float ud_tens_get_mval(ud_tensor *tensor, ...)
{
    va_list arg;
    va_start(arg, tensor);
    size_t *shape_mult = tensor->shape_m;
    ud_ut_count shape_len = tensor->shape_len;
    float *val = tensor->val;
    for (ud_ut_count i = 0; i < shape_len; ++i)
        val += *shape_mult++ * (size_t)va_arg(arg, unsigned int);
    return *val;
}

float *ud_tens_get_mpval(ud_tensor *tensor, ...)
{
    va_list arg;
    va_start(arg, tensor);
    size_t *shape_mult = tensor->shape_m;
    ud_ut_count shape_len = tensor->shape_len;
    float *val = tensor->val;
    for (ud_ut_count i = 0; i < shape_len; ++i)
        val += *shape_mult++ * (size_t)va_arg(arg, unsigned int);
    return val;
}


float ud_tens_get_val(ud_tensor *tensor, size_t *coord)
{
    size_t *shape_mult = tensor->shape_m;
    ud_ut_count shape_len = tensor->shape_len;
    float *val = tensor->val;
    for (ud_ut_count i = 0; i < shape_len; ++i)
        val += *shape_mult++ * *coord++;
    return *val;
}

float *ud_tens_get_pval(ud_tensor *tensor, size_t *coord)
{
    size_t *shape_mult = tensor->shape_m;
    ud_ut_count shape_len = tensor->shape_len;
    float *val = tensor->val;
    for (ud_ut_count i = 0; i < shape_len; ++i)
        val += *shape_mult++ * *coord++;
    return val;
}