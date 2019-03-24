// Solution to Queens Attack II from HackerRank. 
// The time complexity of this solution is O(numberOfObsticles)

#include<iostream>
#include<vector>
#include<set>
// calculates the number of possible moves in the absense of
// a obstacle
int moveCount(int n, int i, int j) {
	return 4 * (n - 1) - abs(i - j) - abs(i+j-n-1);
}


// solution to the problem

// we take the approach of just removing
int queensAttack(int n, int k, int r_q, int c_q, std::vector<std::vector<int>>& obstacles) {
	int withoutObs = moveCount(n, r_q, c_q);
	for (auto & obs : obstacles) {
		if (obs[0] == r_q) {
			if (obs[1] < c_q) {
				withoutObs = withoutObs - abs(c_q) + abs(c_q - obs[1]);
			}
			else {
				withoutObs = withoutObs - abs(n - c_q) + abs(c_q - obs[1]) - 1;
			}
		}
		else if (obs[1] == c_q) {
			if (obs[0] < r_q) {
				withoutObs = withoutObs - abs(r_q) + abs(r_q - obs[0]);
			}
			else {
				withoutObs = withoutObs - abs(n - r_q) + abs(r_q - obs[0]) - 1;
			}
		}
		else if ((obs[0] - r_q) == (obs[1] - c_q)) {
			withoutObs = withoutObs - abs(n - c_q) + abs(c_q - obs[1]) - 1;
		}
		else if ((obs[0] - r_q) == -(obs[1] - c_q)) {
			withoutObs = withoutObs - abs(n - c_q) + abs(c_q - obs[1]) - 1;
		}
		else {
			// do nothing!
		}
	}
	return withoutObs;
}

int main()
{
	std::vector<std::vector<int>> O;
	std::vector<int> o1 = { 5, 5 };
	std::vector<int> o2 = { 4, 2 };
	std::vector<int> o3 = { 2, 3 };
	O.push_back(o1);
	O.push_back(o2);
	O.push_back(o3);
	
	int value = queensAttack(5, 0, 4, 3, O);

	return 0;
}