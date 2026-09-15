#include<iostream>
using namespace std;

int main(){
	const char* user = getenv("USERNAME");
	if(user != nullptr){
	cout << "Current user is: " << user <<"\n";
	}
}