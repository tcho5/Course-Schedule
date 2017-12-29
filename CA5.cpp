#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cstdio>
#include <iterator>
#include <algorithm>
#include <queue>
#include "Course.h"
#include "Semester.h"

using namespace std;
Course *trySchedule = new Course();
unordered_map<string, Course> course_offerings;
vector<Semester> schedule;
vector<string> courses_taken;
int totalRequired = 0;
int total_credits = 0;

template <class T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) 
{
    os << "[";
    for (auto i : v)
    {
        os << " " << i << endl;
    }
    os << " ]";
    return os;
}

bool semesterComparator(const Semester &s1, const Semester &s2)
{
	return (s1.year != s2.year) ? s1.year < s2.year : s1.semester > s2.semester;
}

int stringToInt(string text){
	stringstream iss(text);
	int integer = 0;
	iss >> integer;
	return integer;
}

void trim(string &s){
	size_t p = s.find_first_not_of(" \t");
	s.erase(0, p);
	p = s.find_last_not_of(" \t");
	if (string::npos != p) s.erase(p+1);

}
CoursesLLNode BreadthFirstSearch(CoursesLLNode &root, string courseToCheck){
	queue<CoursesLLNode> Q;
	CoursesLLNode tempNode;
	string temp;
	Q.push(root);
	int checker = 0;
 	if(root.visited == false){
 		string temp;
		root.visited= true;
		for(unsigned i = 0; i < trySchedule->requirements.size(); i++) {
			if(root.className == trySchedule->requirements.at(i).className){
				trySchedule->requirements.at(i) = root;
			}
 		}
		Q.push(root);
		while(!Q.empty()){
			root = Q.front();
			temp = root.className;
			Q.pop();
			if(temp == courseToCheck){
				return root;
			}
			for(auto i : root.preReq){
				if(!i.visited){
					i.visited = true;
					for(unsigned j = 0; j < trySchedule->requirements.size(); j++) {
						if(i.className == trySchedule->requirements.at(j).className){
							trySchedule->requirements.at(j) = i;
						}
 					}
					Q.push(i);
				}
			}
		}
 	}
 	for(auto a : trySchedule->requirements){
 		tempNode.className = courseToCheck;
 		if (a.className == courseToCheck) {
 			checker ++;
 			return a;
 		}
 	}	
 	if(checker == 0){
 		return tempNode;
 	}else{return root;}
}

void Schedule(string fileName){
	int inc = 0;
	ifstream file(fileName);
	string semester, c1, c2, c3, c4, c5, c6, line;
	//vector<Semester> schedule;
	while (getline(file, line))
	{
		c1 = "";
		c2 = "";
		c3 = "";
		c4 = "";
		c5 = "";
		c6 = "";
		istringstream iss(line);
		iss >> semester >> c1 >> c2 >> c3 >> c4 >> c5 >> c6;
		Semester sem(semester, c1, c2, c3, c4, c5, c6);
		schedule.push_back(sem);


		std::unordered_map<std::string, Course>::iterator it;

		for (auto c : sem.courses){
			if (c != ""){
				it = course_offerings.find(c);
				if (it != course_offerings.end()){
					total_credits += it->second.credits;
				}

				inc++;
			}
		}
	}
	sort(schedule.begin(), schedule.end(), semesterComparator);
}

void CourseOfferings(string file)
{
	fstream file2;
	file2.open(file);
	string name, semester, tags, wordstr;
	int credits;

	while(getline(file2, wordstr))
	{
		istringstream iss(wordstr);
		iss >> name >> credits >> semester >> tags;
		Course course(credits, name, semester, tags);
		course_offerings.insert({name, course});
	}
  
}

void readRequirementsFile(string file){
		ifstream loadfile;
		loadfile.open(file);
		int sum = 0, numChoose;
		string filler = "";
		string str, option, text, credits, course, prereq;
		while(getline(loadfile, str)){
			sum++;
			istringstream buff(str);
			istringstream iss(str);
			iss >> option;
			getline(iss, text);
			trim(text);
			if(option == "TOTAL"){
				int total = stringToInt(text);
				trySchedule->TOTAL = total;
			}
			else if(option == "CREDIT"){
				istringstream isss(text);
				isss >> credits;
				if(credits == "C"){
					getline(isss, text); int creditNum = stringToInt(text); trySchedule->C=creditNum;
				}
				else if(credits == "H"){
					getline(isss, text); int creditNum = stringToInt(text); trySchedule->H=creditNum;
				}
				else if(credits == "F"){
					getline(isss, text); int creditNum = stringToInt(text); trySchedule->F=creditNum;
				} 
				else{cout << "Invalid Credit" << endl;}		
			}
			else if(option == "COURSE"){
				istringstream isss(text);
				isss >> course >> option; 
				CoursesLLNode courseNode(course);
				// M R O **********
				if(option == "M" || option == "R") courseNode.required = 1;
				//CoursesLLNode courseNode(course);
				trySchedule->requirements.push_back(courseNode);
				while (isss >> prereq) {
					vector<CoursesLLNode> v = trySchedule->requirements;
					vector<CoursesLLNode>::iterator it;
					it = find(v.begin(), v.end(), CoursesLLNode(prereq));
					CoursesLLNode courseNode2;
					if(it == v.end()){ //element does not exist
						courseNode2.className = prereq;
						trySchedule->requirements.push_back(courseNode2);
					} else {
						courseNode2 = *it;
						//courseNode2 now has values of prereqs
					}
					courseNode.preReq.push_back(courseNode2);

					for(unsigned i = 0; i < trySchedule->requirements.size(); i++) {
						if(courseNode.className == trySchedule->requirements.at(i).className){
							trySchedule->requirements.at(i) = courseNode;
						}
 					}
				}
			}
			else if(option == "CHOOSE"){
				istringstream isss(text);
				string num; 
				isss >> num;
				numChoose = stringToInt(num); 
				ChooseClassLLNode chooseNode(numChoose);
				trySchedule->chooseClass.push_back(chooseNode);
				while (isss >> str){
					chooseNode.courses.push_back(str);
					vector<CoursesLLNode> v = trySchedule->requirements;
					vector<CoursesLLNode>::iterator it;
					it = find(v.begin(), v.end(), CoursesLLNode(str));
					CoursesLLNode courseNode1;
					if(it == v.end()){ //element does not exist
						courseNode1 = CoursesLLNode(str);
						trySchedule->requirements.push_back(courseNode1);
					} else {
						courseNode1 = *it;
					}
					for(unsigned i = 0; i < trySchedule->chooseClass.size(); i++) {
						if(chooseNode == trySchedule->chooseClass.at(i)){
							trySchedule->chooseClass.at(i) = chooseNode;
						}
 					}
				}

			}
		}
		loadfile.close();
}

int main(int argc, char *argv[]) {
   	if (argc == 4){
		string file1 = argv[1], file2 = argv[2], file3 = argv[3];
		int sum = 0;
		readRequirementsFile(file1);
		CourseOfferings(file2);
		Schedule(file3);
		vector<CoursesLLNode> v1 = trySchedule->requirements;

		if (total_credits < trySchedule->TOTAL){
			cout << "Bad plan. Here's why: " << endl;
			cout << "- You do not reach the credit requirement with this plan." << endl;
			return 0;
		} else {
			for (auto i : schedule){
				for (auto s : i.courses){
					for(CoursesLLNode c : v1) {
						if (s != ""){
							CoursesLLNode courseObject = BreadthFirstSearch(c, s);
							if (courseObject.preReq.size() > 0){
								if (courses_taken.size() == 0){
									cout << "Bad Plan. Here's why: " << endl;
									cout << "- You did not take the necesary prereqs for " << s << "." << endl;
									return 0;
								} else {
									unsigned int amount = 0;
									for (auto pre : courseObject.preReq){
										if (!(find(courses_taken.begin(), courses_taken.end(), pre.className) != courses_taken.end())){  
											cout << "Bad Plan. Here's why: " << endl;
											cout << "- You did not take the necesary prereqs for " << s << "." << endl;
											return 0;
										} else {amount++;}
									}
									if (amount == courseObject.preReq.size()) {
										courses_taken.push_back(s);
									}
									break;
								}

							} else {
								courses_taken.push_back(s);
								break;
							}
						}
					}
				}
			}
		}
		for (auto a : trySchedule->chooseClass) {
			//a.chooseNum 
			for(auto b : a.courses){
				for(auto c : courses_taken){
					if(c == b){
						sum++;
					}
				}
				
			}
			if(sum < a.chooseNum){
				cout << "Not a good schedule..." << endl;
				cout << "You only took " << sum <<" Classes." << "You need to take: " << a.chooseNum << " classes" <<endl;
				return 0;
			}
		}
		int counter = 0;
		for (auto thing : v1){
			if (thing.required == 1){
				for (auto temp : courses_taken){
					if(thing.className == temp){
						counter++;
						break;
					}
				}
			}
		}
		for (auto a: v1){
			if(a.required == 1){
				totalRequired++;
			}
		}
		if(counter != totalRequired){
			cout << "Bad plan... Heres why..." << endl;
			cout << "You have not taken all the Required Courses" << endl;
			return 0;
		}
	}
	else{cout << "Wrong file input" << endl;}
	cout << "Good plan. Get to work." << endl;	
	delete trySchedule;
}
