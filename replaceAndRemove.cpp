#include<iostream>
#include<string>

int replaceAByTwoDRemoveB(int size, char s[])
{
	// the foward iteration removes all
	// 'b' entires. Also the a's are counted
	int write_idx = 0, a_count = 0;
	for(int i = 0; i < size; ++i){
		if(s[i] != 'b'){
			s[write_idx++] = s[i];
		}
		if(s[i] == 'a'){
			++a_count;
		}
	}	

	// we want to start reading
	// from the end of the "overwritten" string
	int cur_idx = write_idx - 1;
	// we write from the end + a_count -1
	write_idx = write_idx + a_count - 1;
	int final_size = write_idx + 1;

	while(cur_idx >= 0){
		if(s[cur_idx] == 'a'){
			s[write_idx--] = 'd';
			s[write_idx--] = 'd';
		} else {
			s[write_idx--] = s[cur_idx];
		}
	--cur_idx;
	}
	return final_size;
}

int main()
{
	return 0;
}
