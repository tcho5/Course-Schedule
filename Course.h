#include <vector>
#include <string>

using namespace std;
using std::string;



class CoursesLLNode{
	public: 
		CoursesLLNode(string);
		CoursesLLNode();
		bool operator==(const CoursesLLNode&);
		string className;
		vector<CoursesLLNode> preReq;
		bool visited = false;\
		int required = 0;
		//1 for required
		//0 for anything else
};
class ChooseClassLLNode{
	public:
		ChooseClassLLNode(int);
		ChooseClassLLNode();
		bool operator==(const ChooseClassLLNode&);
		int chooseNum;
		vector<string> courses;

};
class Course{
	public:
		Course();
		Course(int, string, string, string);
		vector<CoursesLLNode> requirements;
		vector<ChooseClassLLNode> chooseClass;
		int C;
		int H;
		int F;
		int TOTAL;


		int credits;
		string semester, name, tags;
		int getCredits();
		string getSemester();
		string getName();
		string getTags();


	private:
		//vector<string*> studentSchedule;
		


};
