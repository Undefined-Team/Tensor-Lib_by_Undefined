#include "ud_tensor.h"

static size_t *ud_tens_comp_coord(size_t *coord, size_t len, size_t real_len)
{
    size_t *new_coord;
    UD_UT_PROT_MALLOC(new_coord = ud_ut_malloc(sizeof(size_t) * real_len));
    size_t *new_coord_tmp = new_coord;
    real_len -= len;
    while (len--) *new_coord_tmp++ = *coord++;
    while (real_len--) *new_coord_tmp++ = 0;
    return new_coord;
}

ud_tensor *ud_tens_get(ud_tensor *tensor, ud_arr_size_t_a *coord)
{
    size_t coord_len = coord->len;
    size_t shape_len = tensor->shape_len;
    if (coord_len == shape_len) ud_ut_error("This function can't return a float. Use pd_tens_get_val instead.");
    else if (coord_len > shape_len) ud_ut_error("Coord can't have more axis than tennsor");
    else if (coord_len == 0) ud_ut_error("Coord can't be empty");
    size_t *real_coord = ud_tens_comp_coord(coord->val, coord_len, shape_len);
    ud_tensor *child = ud_tens_new(ud_tens_get_pval(tensor, real_coord), tensor->shape_m[coord_len - 1],
    tensor->shape + coord_len, tensor->shape_m + coord_len, shape_len - coord_len);
    ud_arr_free(coord);
    ud_ut_free(real_coord);
    return child;
}

ud_tensor *ud_tens_get_cpy(ud_tensor *tensor, ud_arr_size_t_a *coord)
{
    ud_tensor *get_tensor = ud_tens_get(tensor, coord);
    ud_tensor *new_tensor = ud_tens_cpy(get_tensor);
    ud_ut_free(get_tensor);
    return (new_tensor);
}