#include<iostream>
using namespace std;

int main(){
	FILE* file = fopen("ghost.txt", "r");
	if (file ==nullptr)
	perror("Failed to open file");
}