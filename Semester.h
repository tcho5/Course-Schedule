#include <string>
#include <iostream>
#include <vector>

using std::string;

class Semester
{
	public:
		Semester();
		Semester(string, string, string, string, string, string, string);

		int year;
		string semester, c1, c2, c3, c4, c5, c6;

		std::vector<string> courses;

		friend std::ostream& operator<<(std::ostream&, const Semester&);
};
