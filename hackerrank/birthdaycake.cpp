#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<int> arr = {8,1,4,5,6,5,6,5,6,7,8,7,8,8,8,4,3,2,1};
    
    int count = 1;
    int h = -1;
    for(auto& v : arr){
        if(v > h){
            count = 1;
            h = v;
        }
        else if(v==h){
            count++;
        }
    }
    std::cout << count << std::endl;
}
