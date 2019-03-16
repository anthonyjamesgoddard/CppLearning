// linear time

vector<int> gradingStudents(vector<int> grades) {
    for(auto&v:grades){ 
        if(v < 38) continue;      
        int temp = 5 * ((v + 2) / 5);
        if(v<temp){
            v = temp;
        }
    }
    return grades;
}