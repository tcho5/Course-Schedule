#include "Semester.h"

Semester :: Semester(){}

Semester :: Semester(string semester, string c1, string c2, string c3, string c4, string c5, string c6)
: c1(c1), c2(c2), c3(c3), c4(c4), c5(c5), c6(c6)
{
	// parse F2017 into -> F and 2017
	this->semester = string(1, semester[0]);
	this->year = atoi(semester.substr(1, 4).c_str());
	courses.push_back(c1);
	courses.push_back(c2);
	courses.push_back(c3);
	courses.push_back(c4);
	courses.push_back(c5);
	courses.push_back(c6);


	// semester = F
	// year = 2017
}

std::ostream& operator<<(std::ostream& os, const Semester &s) 
{
    os << "Semester(" << s.semester << s.year << ", " << "c1=" << s.c1 << ", "
    											  	  << "c2=" << s.c2 << ", "
    											  	  << "c3=" << s.c3 << ", "
    											  	  << "c4=" << s.c4 << ")";
    return os;
}

