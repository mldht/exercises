nt getSquaredSum(int n)
{
    int sum = 0;
    while(n)
    {
        int tmp = n%10;
        sum += tmp * tmp;
        n = n/10;
    }
    return sum;
}

bool isHappy(int n){
    int slow = n;
    int fast = getSquaredSum(n);
    while(fast != 1 && fast != slow)
    {
        slow = getSquaredSum(slow);
        fast = getSquaredSum(getSquaredSum(fast));
    }

    return fast == 1;
}
