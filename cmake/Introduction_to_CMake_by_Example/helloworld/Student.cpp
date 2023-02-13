#include <iostream>
#include "Student.h"

Student::Student(std::string name):name(name){}

void Student::display(){
	std::cout << "A student with name " << this->name << "\n";
}

