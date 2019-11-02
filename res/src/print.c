#include "ud_tensor.h"

static void        ud_tens_print_ft(ud_tensor *tensor, size_t space, size_t *coord)
{
    coord[space] = 0;
    size_t *shape = tensor->shape;
    size_t rank = tensor->shape_len - space;
    if (rank == 0 || tensor->len == 0)
        return ;
    if (space == tensor->shape_len - 1)
    {
        for (size_t i = 0; i < space; i++) printf("%*s", UD_UT_SPACE_NBR, "");
        printf("%s[ ", ud_ut_color_t[rank % UD_UT_COLOR_NBR]);
        for (size_t i = 0; i < shape[space]; i++)
        {
            printf("%.2f ", ud_tens_get_val(tensor, coord));
            ++coord[space];
        }
        printf("]%s\n", UD_UT_COLOR_N);
    }
    else
    {
        for (size_t i = 0; i < space; i++) printf("%*s", UD_UT_SPACE_NBR, "");
        printf("%s[ %zd%s\n", ud_ut_color_t[rank % UD_UT_COLOR_NBR], rank, UD_UT_COLOR_N);
        for (size_t i = 0; i < shape[space]; i++)
        {
            ud_tens_print_ft(tensor, space + 1, coord);
            ++coord[space];
        }
        for (size_t i = 0; i < space; i++) printf("%*s", UD_UT_SPACE_NBR, "");
        printf("%s]%s\n", ud_ut_color_t[rank % UD_UT_COLOR_NBR], UD_UT_COLOR_N);
    }
}

void        ud_tens_print_ctr(void *v_tensor, ...)
{
    if (!v_tensor) return;
    ud_tensor *tensor = *(ud_tensor **)v_tensor;
    if (!tensor) return;
    size_t coord[tensor->shape_len];
    ud_tens_print_ft(tensor, 0, coord);
}