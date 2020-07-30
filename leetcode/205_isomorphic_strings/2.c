bool isIsomorphic(char * s, char * t){
    char arr[256];
    char arr2[256];
    int i;
    for(i = 0; i < 256; ++i)
    {
        arr[i] = -1;
        arr2[i] = -1;
    }

    while(*s != '\0')
    {
        //char tmp = arr[*s];
        if(arr[*s] == -1)
        {
            arr[*s] = *t;
        }
        else
        {
            if(arr[*s] != *t)
            {
                return false;
            }
        }

        if(arr2[*t] == -1)
        {
            arr2[*t] = *s;
        }
        else if(arr2[*t] != *s)
        {
            return false;
        }
        ++s;
        ++t;
    }

    return true;
}
