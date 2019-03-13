#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<int> climbingLeaderboard(vector<int> scores, vector<int> alice) {
	int sz = scores.size() - 1;
	int highScore = -10;
	int position = 1;
	vector<int> leaderBoard;
	for (auto&v : alice){
		while (sz >= 0 && scores[sz] <= v){
			if (scores[sz] > highScore){
				position++;
				highScore = scores[sz];
			}
			sz--;
		}
		leaderBoard.push_back(position);
	}
	highScore = leaderBoard.back();
	for (auto&v : leaderBoard)
		v = highScore + 1 - v;
	return leaderBoard;
}

// still fails other tests

int main()
{
	vector<int> scores = { 100, 90, 90, 80, 75, 60 };
	vector<int> alice = { 50, 65, 77, 90, 102 };
	auto result = climbingLeaderboard(scores, alice);

	scores = { 100,100,50,40,40,20,10 }; 
	alice = { 5,25,50,120 };
	result = climbingLeaderboard(scores, alice);
	std::cout << "finished" << std::endl;
}