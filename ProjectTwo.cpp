#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// Stores one course and the course numbers of all its prerequisites.
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

using CourseTable = unordered_map<string, Course>;

// Removes whitespace from both ends of a string.
string trim(const string& text) {
    size_t start = 0;
    while (start < text.length() && isspace(static_cast<unsigned char>(text[start]))) {
        ++start;
    }

    size_t end = text.length();
    while (end > start && isspace(static_cast<unsigned char>(text[end - 1]))) {
        --end;
    }

    return text.substr(start, end - start);
}

// Converts course-number input to uppercase so searches are case-insensitive.
string toUpper(string text) {
    transform(text.begin(), text.end(), text.begin(), [](unsigned char character) {
        return static_cast<char>(toupper(character));
    });
    return text;
}

// Splits one comma-separated record into individual fields.
vector<string> splitCsvLine(const string& line) {
    vector<string> fields;
    string field;
    stringstream lineStream(line);

    while (getline(lineStream, field, ',')) {
        fields.push_back(trim(field));
    }

    // getline does not preserve a final empty field after a trailing comma.
    if (!line.empty() && line.back() == ',') {
        fields.emplace_back("");
    }

    return fields;
}

// Loads and validates the complete file before replacing the current table.
bool loadCourses(const string& fileName, CourseTable& courses) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cout << "Error: Unable to open \"" << fileName << "\"." << endl;
        return false;
    }

    CourseTable candidateCourses;
    string line;
    size_t lineNumber = 0;

    while (getline(inputFile, line)) {
        ++lineNumber;

        // Ignore a blank line instead of creating an invalid course.
        if (trim(line).empty()) {
            continue;
        }

        vector<string> fields = splitCsvLine(line);
        if (fields.size() < 2 || fields[0].empty() || fields[1].empty()) {
            cout << "Error: Invalid course record on line " << lineNumber << "." << endl;
            return false;
        }

        Course course;
        course.courseNumber = toUpper(fields[0]);
        course.title = fields[1];

        // Empty trailing columns occur in the supplied ABCU data file.
        for (size_t index = 2; index < fields.size(); ++index) {
            if (!fields[index].empty()) {
                course.prerequisites.push_back(toUpper(fields[index]));
            }
        }

        if (candidateCourses.find(course.courseNumber) != candidateCourses.end()) {
            cout << "Error: Duplicate course " << course.courseNumber
                 << " on line " << lineNumber << "." << endl;
            return false;
        }

        candidateCourses.emplace(course.courseNumber, course);
    }

    if (candidateCourses.empty()) {
        cout << "Error: The course data file is empty." << endl;
        return false;
    }

    // Every prerequisite must refer to another course in the input file.
    for (const auto& entry : candidateCourses) {
        const Course& course = entry.second;
        for (const string& prerequisite : course.prerequisites) {
            if (candidateCourses.find(prerequisite) == candidateCourses.end()) {
                cout << "Error: " << course.courseNumber
                     << " references missing prerequisite " << prerequisite << "." << endl;
                return false;
            }
        }
    }

    courses = std::move(candidateCourses);
    cout << courses.size() << " courses loaded successfully." << endl;
    return true;
}

// Copies courses from the hash table, sorts them, and prints the schedule.
void printCourseList(const CourseTable& courses) {
    vector<Course> sortedCourses;
    sortedCourses.reserve(courses.size());

    for (const auto& entry : courses) {
        sortedCourses.push_back(entry.second);
    }

    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& left,
                                                         const Course& right) {
        return left.courseNumber < right.courseNumber;
    });

    cout << "Here is a sample schedule:" << endl;
    for (const Course& course : sortedCourses) {
        cout << course.courseNumber << ", " << course.title << endl;
    }
}

// Finds and prints one course plus the number and title of each prerequisite.
void printCourse(const CourseTable& courses, const string& requestedNumber) {
    string courseNumber = toUpper(trim(requestedNumber));
    auto courseIterator = courses.find(courseNumber);

    if (courseIterator == courses.end()) {
        cout << "Course " << courseNumber << " not found." << endl;
        return;
    }

    const Course& course = courseIterator->second;
    cout << course.courseNumber << ", " << course.title << endl;
    cout << "Prerequisites: ";

    if (course.prerequisites.empty()) {
        cout << "None" << endl;
        return;
    }

    for (size_t index = 0; index < course.prerequisites.size(); ++index) {
        const Course& prerequisite = courses.at(course.prerequisites[index]);
        if (index > 0) {
            cout << "; ";
        }
        cout << prerequisite.courseNumber << ", " << prerequisite.title;
    }
    cout << endl;
}

void displayMenu() {
    cout << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

int main() {
    CourseTable courses;
    bool dataLoaded = false;
    string input;

    cout << "Welcome to the course planner." << endl;

    while (true) {
        displayMenu();
        if (!getline(cin, input)) {
            cout << endl << "Thank you for using the course planner!" << endl;
            break;
        }

        stringstream inputStream(trim(input));
        int choice = 0;
        char extraCharacter = '\0';

        // Reject input such as "2abc" rather than partially reading it as 2.
        if (!(inputStream >> choice) || (inputStream >> extraCharacter)) {
            cout << input << " is not a valid option." << endl;
            continue;
        }

        if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
            break;
        }

        if (choice == 1) {
            cout << "Enter the file name: ";
            string fileName;
            getline(cin, fileName);
            if (loadCourses(trim(fileName), courses)) {
                dataLoaded = true;
            }
        } else if (choice == 2) {
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            } else {
                printCourseList(courses);
            }
        } else if (choice == 3) {
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            } else {
                cout << "What course do you want to know about? ";
                string courseNumber;
                getline(cin, courseNumber);
                printCourse(courses, courseNumber);
            }
        } else {
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
