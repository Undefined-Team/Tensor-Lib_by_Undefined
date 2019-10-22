#include "ud_tensor.h"

ud_arr_type    *ud_tens_type_tens(void)
{
    static ud_arr_type *type_tensor = NULL;
    if (!type_tensor) type_tensor = ud_arr_type_get(ud_tensor*);
    return type_tensor;
}