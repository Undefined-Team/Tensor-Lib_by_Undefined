#include <ud_memory.h>
#include <ud_math.h>
#include <ud_utils.h>
#include <ud_array.h>
#include <ud_string.h>
#include <ud_tensor.h>
#include <assert.h>

int byte_cmp(void *tens, void *arr, size_t len)
{
    char *a_tens = (char *)tens;
    char *a_arr = (char *)arr;
    for (ud_ut_count i = 0; i < len; i++)
        if (a_tens[i] != a_arr[i])
            return (0);
    return (1);
}

int main(void)
{
    ud_tensor   *zero = ud_tens_init(ud_arr_set(size_t, 3, 1, 2, 3));
    ud_tensor   *val_five = ud_tens_init_id(ud_arr_set(size_t, 3, 1, 2, 3));
    ud_tensor   *id = ud_tens_init_val(ud_arr_set(size_t, 3, 1, 2, 3), 5);

    ud_ut_time("%s", "Starting tests...");
    //Basic tests
    assert(byte_cmp(zero->val, ud_arr_set(float, 6, 0,0,0,0,0,0)->val, zero->len));
    assert(zero->len == 6 && id->len == 6 && val_five->len == 6);
    assert(byte_cmp(id->val, ud_arr_set(float, 6, 5,5,5,5,5,5)->val, id->len));
    assert(byte_cmp(val_five->val, ud_arr_set(float, 6, 0,1,2,3,4,5)->val, val_five->len));
    ud_ut_time("%s", "All tests passed.");
}