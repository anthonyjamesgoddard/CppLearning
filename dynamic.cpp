// some really cool dynamic programming problems

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>


using std::make_unique;
using std::min;
using std::string;
using std::vector;


void print2dArray(vector<vector<int>> a){
    std::cout << "------------" << std::endl;
    for(auto&i : a) {
        for(auto&j:i){
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "-------------" << std::endl;
    
}

// this function solves the problem of counting the number of ways we can
// reach a final score given a collection of individual scores.


// lets say our final score is 7 and we are allowed individual play scores
// 2, 3, 5

// x          0 1 2 3 4 5 6 7
// ---------------------------
// 2        | 1 0 1 0 1 0 1 0       k = 2
// 2, 3     | 1 0 1 1 1 1 2 1       k = 3
// 2, 3, 5  | 1 0 1 1 1 2 2 2       k = 5

// If we denote the matrix shown above as A then A[i][j] = A[i-1][j] + A[i][j-k]
// where k is the max score allowed in row i.

// This implementation uses O(sn) space and time.

int NumCombinationsForFinalScore(int final_score, const vector<int>& ind_ply_scrs) {
    size_t scores_sz = ind_ply_scrs.size();
    vector<vector<int>> num_com_for_score(scores_sz, vector<int>(final_score + 1, 0));
    for (size_t i = 0; i < scores_sz; ++i) {
        num_com_for_score[i][0] = 1;  // One way to reach 0.
        for (size_t j = 1; j <= final_score; ++j) {
            
            // only relevant for i == 0
            int without_this_play = i >= 1 ? num_com_for_score[i - 1][j] : 0;
            
            // if the partial final score is greater than
            // the current individual score then ...
            int with_this_play = j >= ind_ply_scrs[i] ? num_com_for_score[i][j - ind_ply_scrs[i]] : 0;
            
            num_com_for_score[i][j] = without_this_play + with_this_play;
        }
    }
    return num_com_for_score.back().back();
}




// When looking at two strings, we would like to know how many edits we
// need to make to convert one string into another. An edit can be either
// an insertion, deletion or substitutiion of a single char

// To understand this algorithm it is best to draw a ternary tree...
// you will see why caching is neccesary then



int ComputeDistanceBetweenPrefixes(const string&, int, const string&, int,
                                   vector<vector<int>>*);

int LevenshteinDistance(const string& A, const string& B) {
    
    vector<vector<int>> distance_between_prefixes(A.size(), vector<int>(B.size(), -1));
    
    return ComputeDistanceBetweenPrefixes(A, A.size() - 1,
                                          B, B.size() - 1,
                                          std::make_unique<vector<vector<int>>>(A.size(), vector<int>(B.size(), -1)).get());
}

int ComputeDistanceBetweenPrefixes(const string& A, int A_idx, const string& B, int B_idx,
                                   vector<vector<int>>* distance_between_prefixes_ptr) {
    vector<vector<int>>& distance_between_prefixes = *distance_between_prefixes_ptr;
    if (A_idx < 0) {
        // A is empty so add all of B's characters.
        return B_idx + 1;
    } else if (B_idx < 0) {
        // B is empty so delete all of A's characters.
        return A_idx + 1;
    }
    if (distance_between_prefixes[A_idx][B_idx] == -1) {
        if (A[A_idx] == B[B_idx]) {
            distance_between_prefixes[A_idx][B_idx] = ComputeDistanceBetweenPrefixes(A, A_idx - 1, B, B_idx - 1, distance_between_prefixes_ptr);
        } else {
            int substitute_last = ComputeDistanceBetweenPrefixes(A, A_idx - 1, B, B_idx - 1, distance_between_prefixes_ptr);
            int add_last = ComputeDistanceBetweenPrefixes(A, A_idx - 1, B, B_idx, distance_between_prefixes_ptr);
            int delete_last = ComputeDistanceBetweenPrefixes(A, A_idx, B, B_idx - 1, distance_between_prefixes_ptr);
            distance_between_prefixes[A_idx][B_idx] = 1 + min({substitute_last, add_last, delete_last});
        }
    }
    return distance_between_prefixes[A_idx][B_idx];
}

// this is from a project Euler problem.
// can be solved using combinatorics. We want
// the maximum number of ways of traversing a
// 2d grid from top left to bottom right
// we can only travel right and down

int ComputeNumberOfWaysToXY(int,int,vector<vector<int>>*);

int NumberOfWays(int n, int m) {
    vector<vector<int>> number_of_ways(n, vector<int>(m, 0));
    return ComputeNumberOfWaysToXY(n-1, m-1, &number_of_ways);
}

int ComputeNumberOfWaysToXY(int x,int y,vector<vector<int>>* n_o_w_p) {
    if(x==0 && y == 0) {
        return 1;
    }
    
    vector<vector<int>>& n_o_w = *n_o_w_p;
    if(!n_o_w[x][y]) {
        int top = x == 0 ? 0 : ComputeNumberOfWaysToXY(x-1,y, n_o_w_p);
        int left = y == 0 ? 0 : ComputeNumberOfWaysToXY(x,y-1, n_o_w_p);
        n_o_w[x][y] = top + left;
    }
    
    return n_o_w[x][y];
}

// maximum score traversing a grid of numbers
// The maximum score at (i,j) is equal
// to the maximum of the max score atainable at
// (i-1,j ) and (i,j-1) plus the score attainable
// at that square


int ComputeMaxScore(int x,int y,
                    vector<vector<int>>* max_score_p,
                    vector<vector<int>>&scores);

int MaxScore(int N, int M, vector<vector<int>>&scores) {
    vector<vector<int>> maxScore(scores.size(), vector<int>(scores[0].size(), -1));
    return ComputeMaxScore(N-1, M-1, &maxScore, scores);
}


int ComputeMaxScore(int x,int y,
                    vector<vector<int>>* max_score_p,
                    vector<vector<int>>& scores) {
    if(x==0 && y == 0) {
        vector<vector<int>>& max_score = *max_score_p;
        max_score[0][0] = scores[0][0];
        return scores[0][0];
    }
    
    vector<vector<int>>& max_score = *max_score_p;
    if(max_score[x][y] == -1) {
        int top = x == 0 ? scores[0][y] : ComputeMaxScore(x-1,y,max_score_p,scores);
        int left = y == 0 ? scores[x][0] : ComputeMaxScore(x,y-1,max_score_p,scores);
        max_score[x][y] = std::max(top, left) + scores[x][y];
    }
    
    return max_score[x][y];
}

// the famous knapsack problem
struct Item;
int OptimumSubjectToItemAndCapacity(const vector<Item>&, int, int,
                                    vector<vector<int>>*);

struct Item {
    int weight, value;
};

int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
    return OptimumSubjectToItemAndCapacity(items,
                                           items.size() - 1,
                                           capacity,
                                           make_unique<vector<vector<int>>>(items.size(),
                                           vector<int>(capacity + 1, -1)).get());
}

// Returns the optimum value when we choose from items[0, k] and have a
// capacity of available_capacity.
int OptimumSubjectToItemAndCapacity(const vector<Item>& items, int k,
                                    int available_capacity,
                                    vector<vector<int>>* V_ptr) {
    if (k < 0) {
        // No items can be chosen.
        return 0;
    }
    
    // V[i][j] holds the optimum value when we choose from items[0, i] and have
    // a capacity of j.
    vector<vector<int>>& V = *V_ptr;
    if (V[k][available_capacity] == -1) {
        int without_curr_item = OptimumSubjectToItemAndCapacity(items, k - 1, available_capacity, V_ptr);
        int with_curr_item = 0;
        if(items[k].weight < available_capacity) {
            with_curr_item = items[k].value + OptimumSubjectToItemAndCapacity(
                                                           items, k - 1,
                                                           available_capacity - items[k].weight, V_ptr);
        }
        V[k][available_capacity] = std::max(without_curr_item, with_curr_item);
    }
    return V[k][available_capacity];
}




int MinimumPathWeight(const vector<vector<int>>& triangle) {
    if (triangle.empty()) {
        return 0;
    }
    // Store the previous row's minimum weight paths
    // passing through each of those entries.
    vector<int> prev_row(triangle.front());
    for (int i = 1; i < triangle.size(); ++i) {
        vector<int> curr_row(triangle[i]);
        // first entry
        curr_row.front() += prev_row.front();
        // intermediate entries
        for (int j = 1; j < curr_row.size() - 1; ++j) {
            curr_row[j] += min(prev_row[j - 1], prev_row[j]);
        }
        // last entry
        curr_row.back() += prev_row.back();
        prev_row.swap(curr_row);
    }
    return *min_element(cbegin(prev_row), cend(prev_row));
}


int main(int argc, char* argv[]) {
    // to test my explaination above
    vector<vector<int>> scores = {{2,2,2,2,2},
                                  {2,1,1,7,2},
                                  {2,1,67,1,2},
                                  {2,1,3,3,2},
                                  {1,4,1,1,2}
    };
    
    
    std::cout << MaxScore(5,5, scores) << std::endl;
    
    
}
