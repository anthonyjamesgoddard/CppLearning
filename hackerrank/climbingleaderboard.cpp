#include<iostream>
#include<vector>

using namespace std;

vector <int> climbingLeaderboard(vector <int> scores, vector <int> alice) {
	// find the highest rank
	int h_rank = 1;
	for (int i = scores.size() - 1; i>0; i--){
		if (scores[i]<scores[i - 1]){
			h_rank++;
		}
	}
	h_rank++;
	
	vector<int>ranks(alice.size());
	int j = scores.size() - 1;
	for (int i = 0; i<alice.size(); i++){
		while (alice[i] >= scores[j]){
			if (h_rank == 1){
				break;
			}
			if (scores[j] == scores[j - 1]){
				j--;
			}
			else{
				j--;
				h_rank--;
			}
		}
		ranks[i] = h_rank;
	}
	return ranks;
}

int main()
{
	vector<int> alice = {1,3,5,6,8,23};
	vector<int> scores = {100,100,34,5,3,3,3,3,2,1};
	auto result = climbingLeaderboard(scores,alice);

	for(auto& v: result)
		std::cout << v << std::endl;
}
