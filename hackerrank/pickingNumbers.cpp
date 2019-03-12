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
    return *max_element(counters.begin(),counters.end());
}

// failing test wherer ther are 100 elements with same value
