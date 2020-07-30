bool isIsomorphic(char * s, char * t){
    int hash[256];
    int hash2[256];



    int i =0;

    for(i = 0; i < 256; ++i)
    {
        hash[i] = hash2[i] = -1;
    }

    i = 0;
    while(s[i] != '\0')
    {
        if(hash[s[i]] == -1)
        {
            hash[s[i]] = i;
        }
        ++i;
    }

    i = 0;
    while(t[i] != '\0')
    {
        if(hash2[t[i]] == -1)
        {
            hash2[t[i]] = i;
        }
        ++i;
    }

    int len = i;
    for(i = 0; i < len; ++i)
    {
        if(hash[s[i]] != hash2[t[i]])
        {
            return false;
        }
    }
    return true;
}
