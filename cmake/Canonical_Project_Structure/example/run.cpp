#include <src/student/student.hpp>
#include <src/matrix/matrix.hpp>

int main(int argc, char *argv[]){
   Student s("Joe");
   s.display();

   int a[] = {5, 10, 15};
   print_fixed_array(a);
   return 0;
}
