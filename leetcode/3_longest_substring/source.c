
int getStrLen(char *s)
{
	int i = 0;
	while( *(s+i) != '\0')
	{
		++i;
	}
	
	return i;
}

int lengthOfLongestSubstring(char * s){

	int i = 0, j = 0;
	int k;
	int len = getStrLen(s);
	int maxlen = 0;
	char set[256] = {0,};

	while( i <= j && j < len)
	{
		if( set[ s[j] ] == 0)
		{
			set [s[j] ] = 1;
			if(maxlen < j -i+1)
			{
				maxlen = j - i+1;	
			}

			++j;
		}
		else
		{
			set[s[i]] = 0;
			++i;
		}
	}

	return maxlen;
}

int main(void)
{
	char *str = "abcabcbb";
	int len = lengthOfLongestSubstring(str);
	 str ="bbbbb";
	len = lengthOfLongestSubstring(str);
	return 0;

}

