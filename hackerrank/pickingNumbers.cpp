int pickingNumbers(vector<int> a) {
    sort(a.begin(),a.end());
    int counter = 0;
    int chosen = a[0];
    std::vector<int> counters;
    for(auto&v:a){
        if(abs(v-chosen) <= 1){
            counter++;
        }
        else{
            counters.push_back(counter);
            counter = 1;
            chosen = v;
        }
    }
    counters.push_back(counter); // just incase all elements are the same
    return *max_element(counters.begin(),counters.end());
}

