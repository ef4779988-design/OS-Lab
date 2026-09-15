#include<iostream>
#include<windows.h>
using namespace std;

int main (){
	cout<< "My Process ID is: " 
	<< GetCurrentProcessId() << "\n";
	return 0;
}