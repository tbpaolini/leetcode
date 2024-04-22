#include <stdlib.h>
#include <math.h>

static int p2[17] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};

/*  Note: In consecutive binary integers, bit 0 flips each 2⁰ counts,
    bit 1 flips each 2¹ counts, bit 2 flips each 2² counts, and so on...
    The count keeps doubling each bit to the left.
*/

int* countBits(int n, int* returnSize){
    int *ans = calloc(1, (n+1) * sizeof(int));
    *returnSize = n+1;
    for (int i = 0; i <= n; i++){
        for (int j = 0; j < 17; j++){
            if ((i / p2[j]) % 2 == 1){
                ans[i] += 1;
            }
        }
    }
    return ans;
}
