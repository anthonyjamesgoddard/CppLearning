#include<iostream>
#include<vector>

int difference(std::vector<std::vector<int>>& s, std::vector<std::vector<int>>& t)
{
    int diff = 0, temp;
    for(int i=0;i<3;i++){
        for(int j = 0; j < 3;j++){
            temp = s[i][j]-t[i][j];
            diff += (temp >=0 ) ? temp : -temp; 
        }
    }
    return diff;
}

int main()
{
	// we input this wrong the first time so some tests were failing
	// found some alt solution where the guy types them in correct :)
	
    std::vector<std::vector<std::vector<int>>> magics = {
        {{8,1,6},{3,5,7},{4,9,2}},
        {{4,3,8},{9,5,1},{2,7,6}},
        {{2,9,4},{7,5,3},{6,1,8}},
        {{6,7,2},{1,5,9},{8,3,4}},
        {{6,1,8},{7,5,3},{2,9,4}},
        {{8,3,4},{1,5,9},{6,7,2}},
        {{4,9,2},{3,5,7},{8,1,6}},
        {{2,7,6},{9,5,1},{4,3,8}}};

    std::vector<std::vector<int>> input = {{4,5,8},{2,4,1},{1,9,7}};

    int min = 1000000;
    for(auto&v:magics){
        auto temp = difference(v,input);
        if(temp < min) min = temp;
    }
    
    std::cout << min << std::endl;
    return 0;
}
