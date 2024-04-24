#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>


struct Student 
{
    std::string name;
    std::vector<int> grades;

    Student(const std::string name, std::vector<int>& grades) : name(name) {}

    void addGrade(int grade) {
        grades.push_back(grade);
    }

    double avgGrade() const {
        if(grades.empty())
            return 0.0;
        int sum = std::accumulate(grades.begin(), grades.end(), 0);
        return static_cast<double>(sum)/grades.size();
    }

};

class StudentManager {
private:
    std::unordered_map< int, std::shared_ptr<Student> > students;

public:

    void addStudent(int studentId, const std::string& name) {
        students[studentId] = std::make_shared<Student>(name);
          
    }

    void expellStudent(int studentId) {
        students.erase(studentId);
    }

    void addGrade(int studentId, int grade) {
        if(students.find(studentId) != students.end()) {
            students[studentId]->addGrade(grade);
        }
        else {
            std::cout << "student with id " << studentId << " not found" << '\n';
        }
    }

    void findStudent(int studentId) {
        if(students.find(studentId) != students.end()) {
            auto student = students[studentId];
            std::cout << "student id: " << studentId << ", name: " << student->name << ", grades: ";
            for(int grade : student->grades) {
                std::cout << grade << " " << '\n';
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "student with id: " << studentId << " not found" << '\n';
        }
    }

    double avgGradeAllStudents() {
        double sum = 0.0;
        int counter = 0;
        for(const auto& pair : students) {
            sum+=pair.second->avgGrade();
            counter++;
        }
        return counter > 0 ? sum / counter : 0.0;
    }
};


int main()
{
    StudentManager SM;

    SM.addStudent(142, "DENIS");
    SM.addStudent(10, "KUZAN");
    SM.addStudent(1011, "SISYA");

    SM.addGrade(1011, 10);
    SM.addGrade(1011, 8);
    SM.addGrade(1011, 6);

    SM.addGrade(10, 11);
    SM.addGrade(10, 4);
    SM.addGrade(10, 10);

    SM.addGrade(142, 12);
    SM.addGrade(142, 4);
    SM.addGrade(142, 9);

    SM.findStudent(142);
    SM.findStudent(1011);
    SM.findStudent(10);



}