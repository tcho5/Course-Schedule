#include <vector>

using namespace std;



class CoursesLLNode{
	public: 
		CoursesLLNode(string);
		CoursesLLNode();
		bool operator==(const CoursesLLNode&);
		string className;
		vector<CoursesLLNode*> preReq;
		//CoursesLLNode *prev = nullptr;
};
class ChooseClassLLNode{
	public:
		ChooseClassLLNode(int);
		ChooseClassLLNode();
		bool operator==(const ChooseClassLLNode&);
		int chooseNum;
		vector<string> courses;

};
class Courses{
	public:
		Courses();
		void readRequirementsFile(string);
		vector<CoursesLLNode> requirements;
		vector<ChooseClassLLNode> chooseClass;
		int C;
		int H;
		int F;
		int TOTAL;


	private:
		//vector<string*> studentSchedule;
		


};
