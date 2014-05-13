#include<iostream>
#include<string>
#include<vector>
#include"PRNG.h"
using namespace std;



class parent{
private:
    unsigned int parent_age;
    string name;
public:
    parent(unsigned int a, string n){
        parent_age = a;
        name = n;
    }
    virtual unsigned int age(){
        return parent_age;
    }
    virtual string Name(){
        return name;
    }
    ~parent(){
        cout<<"GAME OVER"<<endl;
    }
};

class child:public parent{
private:
    //string new_name;
    //unsigned int new_age;
public:
    child(unsigned int a, string n):parent(a,n){
        //new_name = new_n;
        //new_age = new_a;
    }
   /* unsigned int newAge(){
        return new_age;
    }
    string newName(){
        return new_name;
    }
    unsigned int age(){
        return new_age;
    }*/
    ~child(){
        cout<<"chaljkasdjlakdjajdkladjkalsjdla"<<endl;
    }
};



int main(){
    child a(99,"chao");
    cout<<a.age()<<a.Name()<<endl;
}















