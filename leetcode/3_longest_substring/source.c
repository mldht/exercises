
int count[255];

int myStrLen(char *s)
{
	char *str = s;
	while(*str != '\0')
	{
		++str;
	}

	return str-s;
}


int lengthOfLongestSubstring(char * s){

	int i,j;
	int maxlen = 0;
	int len = myStrLen(s);
	for(i = 0; i < len; ++i)
	{
		int k;
		for(k = 0; k < 255; ++k)
		{
			count[k] = 0;
		}
		for(j = i; j < len; ++j)
		{
			if(count[s[j]] > 0)
			{
				maxlen = (maxlen < j - i) ? j - i : maxlen;
				break;		
			}

			count[s[j]]++;
		}	

		if(j == len)
		{
			maxlen = (maxlen < j-i) ? j-i: maxlen;
		}
	}

	return maxlen;
}

int main(void)
{
	int len = lengthOfLongestSubstring(" ");
	return 0;
}
