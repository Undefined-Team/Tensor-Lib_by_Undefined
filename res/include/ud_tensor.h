#ifndef UD_TENSOR_H
# define UD_TENSOR_H

// Lib
#include <ud_utils.h>
#include <ud_memory.h>
#include <ud_array.h>
#include <ud_math.h>

// Macro

// Structures
typedef struct  uds_tensor {
    float       *val;
    size_t      len;
    size_t      *shape;
    size_t      *shape_m;
    size_t      shape_len;
}               ud_tensor;

// Prototypes
ud_tensor       *ud_tens_init_ctr(size_t *shape, size_t shape_len);
ud_tensor       *ud_tens_init(ud_arr *shape);
ud_tensor       *ud_tens_init_val(ud_arr *shape, float new_val);
ud_tensor       *ud_tens_init_id(ud_arr *shape);
ud_tensor       *ud_tens_init_rand(ud_arr *shape, float bound_1, float bound_2);
ud_tensor       *ud_tens_new(float *val, size_t len, size_t *shape, size_t *shape_m, size_t shape_len);
size_t          *ud_tens_shape_mult_init(size_t *shape, ud_ut_count shape_len, size_t *len);
size_t          *ud_tens_shape_mult(size_t *shape, ud_ut_count shape_len);
void            ud_tens_print(ud_tensor *tensor);
float           ud_tens_get_val(ud_tensor *tensor, size_t *coord);
float           *ud_tens_get_pval(ud_tensor *tensor, size_t *coord);

#endif