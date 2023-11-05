#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class myString {
private:
    string data;
    int status; // 0 for success, -1 for error

public:
    myString(const string& inputString);
    myString(const myString& other);
    // function declarations
    int size() const;
    void addStart(const myString& other);
    void addEnd(const myString& other);
    myString partString(int startPos, int length) const;
    myString replPartString(const myString& replacement, int startPos, int length);
    myString replWholeString(const myString& replacement);
    int compareString(const myString& other) const;
    void initString();
    myString setString(const string& inputString);
    string getString() const;
    void printStringScreen() const;
    bool numericString() const;
    bool alphabeticString() const;
};

myString::myString(const string& inputString) {
    data = inputString;
    status = 0;
}

myString::myString(const myString& other) {
    data = other.data;
    status = other.status;
}

int myString::size() const {
    return data.size();
}

void myString::addStart(const myString& other) {
    data = other.data + data;
}

void myString::addEnd(const myString& other) {
    data += other.data;
}

myString myString::partString(int startPos, int length) const {
    if (startPos < 1 || startPos > size() || startPos + length > size() || startPos == size()) {
        return myString("");
    }

    return myString(data.substr(startPos - 1, length));
}

myString myString::replPartString(const myString& replacement, int startPos, int length) {
    if (startPos < 1 || startPos > size() || startPos + length > size() || startPos == size()) {
        status = -1;
        return *this;
    }

    data.replace(startPos - 1, length, replacement.data);
    return *this;
}

myString myString::replWholeString(const myString& replacement) {
    data = replacement.data;
    return *this;
}

int myString::compareString(const myString& other) const {
    return data.compare(other.data);
}

void myString::initString() {
    data = "";
    status = 0;
}

myString myString::setString(const string& inputString) {
    data = inputString;
    status = 0;
    return *this;
}

string myString::getString() const {
    return data;
}

void myString::printStringScreen() const {
    cout << data << endl;
}

bool myString::numericString() const {
    for (char c : data) {
        if (!isdigit(c) && c != '.' && c != '-' && c != '+') {
            return false;
        }
    }
    return true;
}

bool myString::alphabeticString() const {
    for (char c : data) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

int main() {
    ofstream logFile("myStringLog.txt"); // Names and opens file

    myString str("Hello ");
    str.addEnd(myString("world"));
    logFile << "addEnd: " << str.getString() << endl;

    myString part = str.partString(1, 5);
    logFile << "partString: " << part.getString() << endl;

    myString replacement("PartString Output");
    str.replPartString(replacement, 7, 5);
    logFile << "replPartString: " << str.getString() << endl;

    myString newStr("New string");
    str.replWholeString(newStr);
    logFile << "replWholeString: " << str.getString() << endl;

    myString compareStr("Hello, world");
    int cmp = str.compareString(compareStr);
    logFile << "compareString: " << cmp << endl;

    str.initString();
    logFile << "initString: " << str.getString() << endl;

    str.setString("Output setString");
    logFile << "setString: " << str.getString() << endl;

    str.addStart(myString("Output myString "));
    logFile << "addStart: " << str.getString() << endl;

    str.printStringScreen();

    logFile << "numericString: " << (str.numericString() ? "true" : "false") << endl;
    logFile << "alphabeticString: " << (str.alphabeticString() ? "true" : "false") << endl;

    logFile.close();

    return 0;
}
