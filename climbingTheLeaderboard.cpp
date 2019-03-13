#include <bits/stdc++.h>

using namespace std;

vector <int> climbingLeaderboard(vector <int> scores, vector <int> alice) {
    vector<int> result;
    reverse(alice.begin(), alice.end());
    int lastIndex = 0;
    int lastRank = 1;

    for (int i = 0; i < alice.size(); i++) {

        int rank = lastRank;
        for (int j = lastIndex; j < scores.size(); j++) {
            if (alice[i] >= scores[j]) {
                lastIndex = j;
                break;
            }

            else if (alice[i] < scores[j]) {
                rank++;
            }

            if (scores[j] == scores[j+1] && rank != 1) {
                rank--;
            }
        }
        result.push_back(rank);   
        lastRank = rank;
    }
    reverse(result.begin(), result.end());

    return result;
}
