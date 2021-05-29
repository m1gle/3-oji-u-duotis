#include "vector.h"

int main(){
    unsigned int sz = 100000000;

    int k = 0;
    std::vector<int> v1;
    
    auto start = std::chrono::high_resolution_clock::now(); auto st=start;
   
    for (int i = 1; i <= sz; ++i) {
        if(v1.capacity()==v1.size()) k ++;
        v1.push_back(i);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start; // Skirtumas (s)
    cout<<sz<<" dydzio std::vector užtruko: "<<diff.count()<<endl;
    
    //cout<<k<<endl;
    
    k = 0;
    Vector<int> v2;

    auto start2 = std::chrono::high_resolution_clock::now(); auto st2=start2;
    
    for(int i = 1; i<= sz; ++i) {
       if(v2.capacity()==v2.size()) k ++;
        v2.push_back(i);
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff2 = end2-start2; // Skirtumas (s)
    cout<<sz<<" dydzio std::vector užtruko: "<<diff2.count()<<endl;
    
    //cout<<k<<endl;
}
