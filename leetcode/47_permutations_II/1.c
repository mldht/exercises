/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
void insertion_sort(int *nums, int s, int e);

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int get_partition(int *nums, int s, int e)
{
    int mid = (e -s)/2 + s;

    if(nums[s] > nums[mid])
    {
        swap(nums +s,  nums + mid);
    }
    if(nums[s] > nums[e])
    {
        swap(nums +s, nums + e);
    }

    if(nums[mid] > nums[e])
    {
        swap(nums +mid, nums + e);
    }

    swap(nums + mid, nums + e-1);
    
    return nums[e-1];
}
void quick_sort(int *nums, int s, int e)
{
    int partition = get_partition(nums, s, e);
    int i, j;
    i = s;
    j = e-1;    
    while(1)
    {
        while(nums[++i]< partition);
        while(nums[--j] > partition);

        if(i < j)
        {
            swap(nums +i, nums + j);
        }
        else
        {
            break;
        }
    }

    swap(nums + i, nums + e-1);
    quick_sort(nums, s, i -1);
    quick_sort(nums, i+1, e);
}

void insertion_sort(int *nums, int s, int e)
{
    int i;
    for(i = s; i < e;++i)
    {
        int j = i;
        int k = nums[i+1];
        while(j >= s && nums[j] > k)
        {
            nums[j+1] = nums[j];
            --j;
        }
        nums[j+1] = k;
    }
}
void my_sort(int *nums, int s, int e)
{
    if( s + 10 < e)
    {
        quick_sort(nums, s, e);
    }
    else
    {
        insertion_sort(nums, s, e);
    }
}

void backtrack(int *nums, int numsSize, bool *flags, int idx, int *output, int **ret, int *retIdx )
{
    if(idx == numsSize)
    {
        int i;
        int k = *retIdx;
        for(i = 0; i < numsSize; ++i)
        {
            ret[k][i] = output[i];
        }

        *retIdx += 1;
        return;
    }

    int i;
    for(i = 0; i < numsSize; ++i)
    {
        if(flags[i] == true)
        {
            continue;
        }

   
    if(i > 0 && nums[i] == nums[i-1] && flags[i-1] == false)
    {
        continue;
    }
	flags[i] = true;
	output[idx] = nums[i];
    backtrack(nums, numsSize, flags, idx+1, output, ret, retIdx);
	flags[i] = false;
    }
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int total_size = 1;
    int tmp = numsSize;
    while(tmp > 1)
    {
        total_size *= tmp;
        --tmp;
    }
    int **ret = (int **)malloc(sizeof(int *) * total_size);
    int *buf = (int *)malloc(sizeof(int) * numsSize * total_size);

    int i;
    for(i = 0; i < total_size; ++i)
    {
        ret[i] = buf + i * numsSize;
    }

    *returnColumnSizes = (int *)malloc(sizeof(int) * total_size);
    for(i = 0; i < total_size; ++i)
    {
        (*returnColumnSizes)[i] = numsSize;
    }

    bool *flags = (bool *)malloc(sizeof(bool) * numsSize);
    for(i = 0; i < numsSize; ++i)
    {
        flags[i] = false;
    }

    int *output = (int *)malloc(sizeof(int) * numsSize);
/*  */
    *returnSize = 0;
    my_sort(nums, 0, numsSize -1);
    backtrack(nums, numsSize, flags, 0, output, ret, returnSize);

    return ret;
}
