#include "ud_tensor.h"

static size_t       *ud_error_manager(ud_arr *new_dim, size_t shape_len)
{
    if (shape_len != new_dim->len) ud_ut_error("There must be as many new dimensions as the rank of the tensor-> (tensor->rank == new_dim->len)");
    ud_bool valid[new_dim->len];
    ud_mem_set(valid, false, sizeof(ud_bool) * new_dim->len);
    size_t *t_new_dim = (size_t*)new_dim->val;
    size_t t_index;
    size_t new_dim_len = new_dim->len;
    for (ud_ut_count i = 0; i < new_dim_len; i++)
    {
        t_index = t_new_dim[i];
        if (t_index >= new_dim_len) ud_ut_error("A dimension can't be greater than the number of dimensions (new_dim->val[i] < new_dim->length)");
        else if (valid[t_index] == true) ud_ut_error("2 dimensions can't have the same dimension");
        valid[t_index] = true;
    }
    return t_new_dim;
}

static size_t       *ud_get_new_shape(size_t *shape, ud_arr_size_t_a *new_dim)
{
    size_t shape_len = new_dim->len; // WARNING IF MAKE FEATURE OF 1 DIM GUESS
    size_t *new_shape;
    UD_UT_PROT_MALLOC(new_shape = ud_ut_malloc(sizeof(size_t) * shape_len));
    size_t *a_new_shape = new_shape;
    size_t *a_new_dim = (size_t*)new_dim->val;
    while (shape_len-- > 0) *a_new_shape++ = shape[*a_new_dim++];
    return new_shape;
}

void        ud_tens_transpose(ud_tensor *tensor, ud_arr_size_t_a *new_dim)
{
    size_t shape_len = tensor->shape_len;
    size_t *t_new_dim = ud_error_manager(new_dim, shape_len);
    size_t *new_shape;
    size_t *new_shape_m;
    if(!(new_shape = ud_ut_malloc(sizeof(size_t) * shape_len))
    || !(new_shape_m = ud_ut_malloc(sizeof(size_t) * shape_len))) return ;
    size_t *t_new_shape = new_shape;
    size_t *t_new_shape_m = new_shape_m;
    size_t *shape = tensor->shape;
    size_t *shape_m = tensor->shape_m;
    while (shape_len-- > 0)
    {
        *t_new_shape++ = shape[*t_new_dim];
        *t_new_shape_m++ = shape_m[*t_new_dim++];
    }
    ud_ut_free(shape);
    ud_ut_free(shape_m);
    ud_arr_free(new_dim);
    tensor->shape = new_shape;
    tensor->shape_m = new_shape_m;
}

static void ud_set_shape_shapem_max(size_t *old_shape, size_t *old_shape_m, size_t *new_dim, size_t *n_shape, int *n_max, size_t shape_len)
{
    int *old_n_map = n_max;
    size_t n_shape_m;
    *n_max-- = 0;
    while (shape_len-- > 1)
    {
        *n_shape   = old_shape[*new_dim];
        n_shape_m = old_shape_m[*new_dim--];
        *n_max--   = (*n_shape-- - 1) * n_shape_m + *old_n_map;
        *old_n_map = n_shape_m - *old_n_map;
        --old_n_map;
    }
    *n_shape   = old_shape[*new_dim];
    *old_n_map = old_shape_m[*new_dim] - *old_n_map;
}

static void         ud_coord_update(size_t *n_shape, size_t *coord, int *n_max, size_t *index)
{
    if (*coord == *n_shape)
    {
        *coord = 0;
        --coord;
        ++(*coord);
        ud_coord_update(n_shape - 1, coord, n_max - 1, index);
    }
    else
        *index += *n_max;
}

ud_tensor       *ud_tens_transpose_cpy(ud_tensor *tensor, ud_arr_size_t_a *new_dim)
{
    size_t shape_len = tensor->shape_len;
    size_t *t_new_dim = ud_error_manager(new_dim, shape_len);
    size_t len = tensor->len;

    size_t b_shape[shape_len];
    int b_max[shape_len];
    size_t *n_shape = b_shape + (shape_len - 1);
    int *n_max = b_max + (shape_len - 1);
    size_t *n_new_dim = t_new_dim + (shape_len - 1);
    ud_set_shape_shapem_max(tensor->shape, tensor->shape_m, n_new_dim, n_shape, n_max, shape_len);

    size_t coord[shape_len];
    size_t *coord_x = coord - 1;
    for (ud_ut_count i = 0; i < shape_len; ++i) *++coord_x = 0;

    float *new_val;
    UD_UT_PROT_MALLOC(new_val = ud_ut_malloc(sizeof(float) * len));
    float *end_val = new_val + (len - 1);
    float *beg_val = new_val;
    float *t_beg_val = tensor->val;
    float *t_end_val = t_beg_val + len - 1;

    size_t index = 0;
    ud_ut_count tmp_len = len / 2;
    while (tmp_len-- > 0)
    {
        *beg_val++ = *(t_beg_val + index);
        *end_val-- = *(t_end_val - index);
        ++(*coord_x);
        ud_coord_update(n_shape, coord_x, n_max, &index);
    }
    size_t *new_shape = ud_get_new_shape(tensor->shape, new_dim);
    size_t *new_shape_m = ud_tens_shape_mult(new_shape, shape_len);
    ud_arr_free(new_dim);
    return ud_tens_new(new_val, len, new_shape, new_shape_m, shape_len);
}