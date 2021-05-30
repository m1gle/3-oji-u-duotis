#include "vector.h"

int main(){
    std::vector<int> v1;
    Vector<int> v2;

    v1.assign(3,123);
    cout<<"std::vector.assign(3,123): ";
    for(int i = 0; i<v1.size(); i++){
        cout<<v1[i]<<" ";
    }
    cout<<endl;

    v2.assign(3,123);
    cout<<"Vector.assign(3,123): ";
    for(int i = 0; i<v2.size(); i++){
        cout<<v2[i]<<" ";
    }
    cout<<endl;

    v1.push_back(10);
    cout<<"std::vector.push_back(5): ";
    for(int i = 0; i<v1.size(); i++){
        cout<<v1[i]<<" ";
    }
    cout<<endl;

    v2.push_back(10);
    cout<<"Vector.push_back(5): ";
    for(int i = 0; i<v2.size(); i++){
        cout<<v2[i]<<" ";
    }
    cout<<endl;

    v1.pop_back();
    cout<<"std::vector.pop_back(): ";
    for(int i = 0; i<v1.size(); i++){
        cout<<v1[i]<<" ";
    }
    cout<<endl;

    v2.pop_back();
    cout<<"Vector.pop_back(): ";
    for(int i = 0; i<v2.size(); i++){
        cout<<v2[i]<<" ";
    }
    cout<<endl;
    
    cout<<"std::vector dydis: "<<v1.size()<<endl;

    cout<<"Vector dydis: "<<v2.size()<<endl;

    v1.reserve(50);
    cout<<"std::vector capacity() po reserve(50): "<<v1.capacity()<<endl;

    v2.reserve(50);
    cout<<"Vector capacity() po reserve(50): "<<v1.capacity()<<endl;

    v1.clear();
    cout<<"std::vector dydis po clear(): "<<v1.size()<<endl;

    v2.clear();
    cout<<"Vector dydis po clear(): "<<v2.size()<<endl;
}
