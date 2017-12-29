#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iterator>

#include "Course.h"

using namespace std;

Course::Course(){}
CoursesLLNode::CoursesLLNode(){}
ChooseClassLLNode::ChooseClassLLNode(){}

Course :: Course(int credits, string name, string semester, string tags)
{
	this->credits = credits;
	this->name = name;
	this->semester = semester;
	this->tags = tags;
}

int Course :: getCredits()
{
	return this->credits;
}

string Course :: getName()
{
	return this->name;
}

string Course :: getSemester()
{
	return this->semester;
}

string Course :: getTags()
{
	return this->tags;
}

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


