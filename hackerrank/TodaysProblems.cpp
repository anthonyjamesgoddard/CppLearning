// Here I sort first then count in the obvious way.
// You can use std::map/std::unordered_map to get 
// a similar complexity solution.

// O(nlog(n))

int sockMerchant(int n, vector<int>& a) {
    std::sort(a.begin(), a.end());
    int i = 0, pairs = 0;
    while(i<a.size()){
        int t = a[i];
        if(a[i+1] == a[i]){
            pairs++; i++;
        }
        i++;
    }
    return pairs;
}

// a linear solution would be nice.


// This is a simple problem, easy linear algorithm
// Complete the countingValleys function below.

// O(n)

int countingValleys(int n, string s) {
    int vallc = 0;
    int h = 0;
    for(int i = 0;i < n-1; i++){
        if(s[i] == 'D'){
            h--;
        }
        else{
            h++;
        }
        if(h == -1 && s[i+1] == 'U') vallc++;
    }
    return vallc;
}

// another simple one
// Complete the jumpingOnClouds function below.
int jumpingOnClouds(vector<int> c) {
    int steps = 0;
    int loc = 0;
    while(loc < c.size()){
        if(c[loc + 2] == 0 && loc != c.size() - 2){
            loc += 2;
        }
        else{
            loc++;
        }
        steps++;
    }
    return steps-1;
}

// simple as it gets 
int hourglassSum(vector<vector<int>> arr) {
  int sum = -10000;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {

      int top = arr[i][j] + arr[i][j + 1] + arr[i][j + 2];
      int middle = arr[i + 1][j + 1];
      int bottom = arr[i + 2][j] + arr[i + 2][j + 1] + arr[i + 2][j + 2];
      if (top + middle + bottom > sum) {
        sum = top + middle + bottom;
      }
    }
  }
  return sum;
}


