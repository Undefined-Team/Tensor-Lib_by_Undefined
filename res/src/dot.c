#include "ud_tensor.h"

// ud_arr      *ud_tens_get_counter_axis(size_t len, ud_arr *axis)
// {
//     size_t          j_a = 0;
//     size_t          j_b = 0;
//     ud_arr          *counter_axis;

//     counter_axis = ud_arr_init(ud_T_ARR, 2);
//     ((ud_arr **)counter_axis->val)[0] = ud_arr_init(size_t, len - ((ud_arr **)axis->val)[0]->len);
//     ((ud_arr **)counter_axis->val)[1] = ud_arr_init(size_t, len - ((ud_arr **)axis->val)[0]->len);

//     size_t *t_axis_a_val = (size_t *)((ud_arr **)axis->val)[0]->val;
//     size_t *t_axis_b_val = (size_t *)((ud_arr **)axis->val)[1]->val;
//     size_t *t_counter_axis_a_val = (size_t *)((ud_arr **)counter_axis->val)[0]->val;
//     size_t *t_counter_axis_b_val = (size_t *)((ud_arr **)counter_axis->val)[1]->val;

//     for (size_t i = 0; i < len; i++)
//     {
//         ud_bool     in_axis_a = false;
//         ud_bool     in_axis_b = false;
//         for (size_t k = 0; k < ((ud_arr **)axis->val)[0]->len && (!in_axis_a || !in_axis_b); k++)
//         {
//             if (i == t_axis_a_val[k])
//                 in_axis_a = true;
//             if (i == t_axis_b_val[k])
//                 in_axis_b = true;
//         }
//         if (!in_axis_a)
//             t_counter_axis_a_val[j_a++] = i;
//         if (!in_axis_b)
//             t_counter_axis_b_val[j_b++] = i;
//     }
//     return (counter_axis);
// }

// ud_arr      *ud_tens_dot_shape_mult(ud_tensor *a, ud_tensor *b, ud_arr *axis, ud_arr *counter_axis, ud_arr *mem_shapes)
// {
//     ud_arr  *shape_mult = ud_arr_init(ud_arr *, 2);
//     size_t axis_len = ((ud_arr **)axis->val)[0]->len;
//     size_t counter_axis_len = a->shape_len - ((ud_arr **)axis->val)[0]->len;

//     size_t *t_a_shape_val = (size_t *)a->shape;
//     size_t *t_b_shape_val = (size_t *)b->shape;
//     size_t *t_axis_a_val = (size_t *)((ud_arr **)axis->val)[0]->val;
//     size_t *t_axis_b_val = (size_t *)((ud_arr **)axis->val)[1]->val;
//     size_t n_a = 1;
//     size_t n_b = 1;
//     for (size_t i = 0; i < axis_len; i++)
//     {
//         n_a *= t_a_shape_val[t_axis_a_val[i]];
//         n_b *= t_b_shape_val[t_axis_b_val[i]];
//     }
//     size_t *t_counter_axis_a_val = (size_t *)((ud_arr **)counter_axis->val)[0]->val;
//     size_t *t_counter_axis_b_val = (size_t *)((ud_arr **)counter_axis->val)[1]->val;
//     size_t *t_mem_shapes_val = (size_t *)mem_shapes->val;
//     size_t m_a = 1;
//     size_t m_b = 1;
//     for (size_t i = 0; i < counter_axis_len; i++)
//     {
//         size_t val_a = t_a_shape_val[t_counter_axis_a_val[i]];
//         size_t val_b = t_b_shape_val[t_counter_axis_b_val[i]];
//         m_a *= val_a;
//         m_b *= val_b;
//         t_mem_shapes_val[i] = val_a;
//         t_mem_shapes_val[i + counter_axis_len] = val_b;
//     }
//     ((ud_arr **)shape_mult->val)[0] = ud_arr_set(size_t, 2, m_a, n_a);
//     ((ud_arr **)shape_mult->val)[1] = ud_arr_set(size_t, 2, n_b, m_b);
//     return (shape_mult);
// }

// ud_tensor   *ud_tens_dot(ud_tensor *a, ud_tensor *b, ud_arr *axis)
// {
//     ud_arr *shape_mult;
//     ud_arr *counter_axis;
//     size_t  tens_len = a->shape_len;
//     size_t  axis_len = ((ud_arr **)axis->val)[0]->len;
//     ud_arr *mem_shapes = ud_arr_init(size_t, (tens_len - axis_len) * 2);

//     counter_axis = (tens_len > axis_len ? ud_tens_get_counter_axis(tens_len, axis) : NULL);
//     shape_mult = ud_tens_dot_shape_mult(a, b, axis, counter_axis, mem_shapes);
//     ud_arr *new_dim_a = ud_arr_concat_shape(ud_T_SIZE_T, ((ud_arr **)counter_axis->val)[0], ((ud_arr **)axis->val)[0]);
//     ud_arr *new_dim_b = ud_arr_concat_shape(ud_T_SIZE_T, ((ud_arr **)counter_axis->val)[1], ((ud_arr **)axis->val)[1]);
//     ud_tensor *t_a = ud_tens_reshape(a, new_dim_a);
//     ud_tensor *t_b = ud_tens_reshape(b, new_dim_b);
//     ud_tensor *reshape_t_a = ud_tens_reshape(t_a, ((ud_arr **)shape_mult->val)[0]);
//     ud_tensor *reshape_t_b = ud_tens_reshape(t_b, ((ud_arr **)shape_mult->val)[1]);
//     ud_tensor *dot_res = ud_matrix_dot(reshape_t_a, reshape_t_b);
//     ud_tensor *res = ud_tens_reshape(dot_res, mem_shapes);
//     return (res);
// }