#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iterator>

#include "Courses.h"

using namespace std;

Courses::Courses(){}
CoursesLLNode::CoursesLLNode(){}
ChooseClassLLNode::ChooseClassLLNode(){}

ChooseClassLLNode::ChooseClassLLNode(int chooseNum){
	this->chooseNum = chooseNum;
}
CoursesLLNode::CoursesLLNode(string className){
	this->className = className;
}
bool CoursesLLNode::operator==(const CoursesLLNode& b){
	return this->className == b.className;
}
bool ChooseClassLLNode::operator==(const ChooseClassLLNode& b){
	return this->chooseNum == b.chooseNum;
}		

void Courses::readRequirementsFile(string file){
	ifstream loadfile;
	loadfile.open(file);
	int sum = 0;
	string str, option;
	vector <string> v;
	//cout << file << endl;
	while(getline(loadfile, str)){
		sum++;
		cout << "Line: " << sum << " "  << str << endl;
		istringstream buff(str);
		for(string word; buff >> word;) v.push_back(word);
		//istringstream iss(str);
		//iss >> option;
		//cout << "Option: " << option << endl;
	
	}
	for(vector<string>::iterator it = v.begin(); it != v.end(); it++){
		cout << *it;
	} 
	loadfile.close();
}

