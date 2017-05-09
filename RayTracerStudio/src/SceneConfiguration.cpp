#include <cmath>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include "SceneConfiguration.hpp"

using namespace std;

//Used to preprocess the input file into a string for later use
static std::string 
Preprocess(fstream& InputFile) {
    std::string temp;
    std::string line;
    while (getline(InputFile,line, '\n')) {
        line = line.substr(0,line.find("//"));
        //skip comments, tabs, spaces, newlines, etc.
        for (std::string::iterator i = line.begin(); i != line.end(); ++i) {
            switch (*i) {
            case ' ':case '\t': case '\n': case '\r':
                break;
            default:
              temp.push_back(*i);
            }
        }
    }
    return temp;
}

//Parses the string generated from Preprocess and stores variable/sections
static bool 
Load(fstream& InputFile, std::map<std::string, std::string>& variables, std::set<std::string>& sections) {
    static std::string buff;
    std::string temp;
    int depth = 0;
    temp = Preprocess(InputFile);
    std::string::iterator i = temp.begin();
    std::string tempname;
    std::string tempvalue;
    std::string nextSection;
    
nameSearch:
    if (i == temp.end()) {
        goto end;
    }
    switch (*i) {
    case '{':
        if (sections.insert(tempname).second == false) {
            sections.clear();
            variables.clear();
            return false;
        }
        nextSection = tempname;
        tempname.resize(0);
        goto section;
        break;
    default:
        tempname.append(&*i, 1);
    }
    ++i;
    goto nameSearch;
        
section:
    if (i == temp.end()) {
        sections.clear();
        variables.clear();
        return false;
    }
    switch (*i) {
    case '{':
        ++depth; 
        break;
    case '}':
        --depth;
        if (depth == 0) {
            ++i;
            nextSection.resize(0);
            goto nameSearch;
        }
        break;
    default:
        goto name;
    }
    ++i;
    goto section;
    
name:
    if (i == temp.end()) {
            sections.clear();
            variables.clear();
        return false;
    }
    switch (*i) {
    case '{':
        goto section;
    case '}':
            sections.clear();
            variables.clear();
        return false;
    case '=':
        if (tempname.empty()) {
            sections.clear();
            variables.clear();
            return false;
        }
        ++i;
        goto value;
    default:
        tempname.append(&*i,1);
        break;
    }
    ++i;
    goto name;    
    
value:
    if (i == temp.end()) {
            sections.clear();
            variables.clear();
        return false;
    }
    switch (*i) {
    case '{':
            sections.clear();
            variables.clear();
        return false;
    case '}':
            sections.clear();
            variables.clear();
        return false;
    case ';':
        if (tempvalue.empty()) {
            sections.clear();
            variables.clear();
            return false;
        }
        buff.assign(nextSection);
        buff.push_back('/');
        buff.append(tempname);
        variables.insert(std::map<std::string, std::string>::value_type(buff, tempvalue));
        tempname.resize(0);
        tempvalue.resize(0);
        ++i;
        goto section;
    default:
        tempvalue.append(&*i, 1);
        break;
    }
    ++i;
    goto value;    
end:
    return true;
}

SceneConfiguration::SceneConfiguration(const std::string& Filename) :
Variables(NULL), Sections(NULL),Filename(Filename),Loaded(false){}

SceneConfiguration::~SceneConfiguration()
{
    if (Variables != NULL)
        delete static_cast<std::map<std::string, std::string> *>(Variables);
    if (Sections != NULL)
        delete static_cast<std::set<std::string> *>(Sections);
}

int 
SceneConfiguration::ParseInputBySectionName(const std::string& Name)
{
    if (!Loaded) {
        Loaded = true;
        Variables = new std::map<std::string, std::string>();
        Sections = new std::set<std::string>();
        fstream InputFile;
        bool result;
        InputFile.open(Filename.c_str(), ios::in);
        if (InputFile.is_open() == 0) {
            result = false; 
        } 
        else {
            result = Load(InputFile, 
                *(static_cast<std::map<std::string, std::string> *>(Variables)),
                *(static_cast<std::set<std::string> *>(Sections)));
            InputFile.close();
        }
        if (!result) {
            delete static_cast<std::map<std::string, std::string> *>(Variables);
            Variables = NULL;
            delete static_cast<std::set<std::string> *>(Sections);
            Sections = NULL;
            return -1;
        }
    }
    if (Variables == NULL) {
        return -1;
    }
    std::set<std::string>::const_iterator i = 
        ((std::set<std::string>*)Sections)->find(Name);
   if (i != ((std::set<std::string>*)Sections)->end() ) {
        section.assign(Name).push_back('/');
        return 0;
    } else {
        section.resize(0);
        return -1;
    }
}

//The functions below accept the name of a field in the input scene and return the 
//vale associated with it.  The default argument is used if needed.
int 
SceneConfiguration::GetIntegerValueOf(const std::string& Name, int Default) const
{
    static std::string searchName;
    searchName.assign(section).append(Name);
    std::map<std::string, std::string>::const_iterator i = 
        ((std::map<std::string, std::string> *)Variables)->find(searchName);
    if (i != ((std::map<std::string, std::string> *)Variables)->end()) 
        return atoi((*i).second.c_str());
    else {
        return Default;
    }
}

const std::string& 
SceneConfiguration::GetStringValueOf(const std::string& Name, const std::string &Default) const
{
    static std::string searchName;
    searchName.assign(section).append(Name);
    std::map<std::string, std::string>::const_iterator i = 
        ((std::map<std::string, std::string> *)Variables)->find(searchName);
    if (i != ((std::map<std::string, std::string> *)Variables)->end()) 
        return (*i).second;
    else {
        return Default;
    }
}

float 
SceneConfiguration::GetFloatValueOf(const std::string& Name, float Default) const
{
    static std::string searchName;
    searchName.assign(section).append(Name);
    std::map<std::string, std::string>::const_iterator i = 
        static_cast<std::map<std::string, std::string> *>(Variables)->find(searchName);
    if (i != ((std::map<std::string, std::string> *)Variables)->end()) 
        return atof((*i).second.c_str());
    else {
        return Default;
    }

}

bool 
SceneConfiguration::GetBooleanValueOf(const std::string& Name, bool Default) const
{
    static std::string searchName;
    searchName.assign(section).append(Name);
    std::map<std::string, std::string>::const_iterator i = 
        static_cast<std::map<std::string, std::string> *>(Variables)->find(searchName);
    if (i != ((std::map<std::string, std::string> *)Variables)->end()) {
        return (*i).second.compare("true") == 0;
    } else {
        return Default;
    }
}

Vector 
SceneConfiguration::GetVectorValueOf(const std::string& Name, const Vector& Default) const
{
    Vector tempVector;
    static std::string searchName; 
    searchName.assign(section).append(Name);
    std::map<std::string, std::string>::const_iterator i = 
        static_cast<std::map<std::string, std::string> *>(Variables)->find(searchName);
    if (i != ((std::map<std::string, std::string> *)Variables)->end()) {
        int Read = sscanf(i->second.c_str(), "%f,%f,%f", &tempVector.x, &tempVector.y, &tempVector.z);
        if (Read != 3) {
            return Default;
        }
        
        return tempVector;
    } else {
        return Default;
    }
}

Point 
SceneConfiguration::GetPointValueOf(const std::string& Name, const Point& Default) const
{
    Point tempPoint;
    static std::string searchName; 
    searchName.assign(section).append(Name);
    std::map<std::string, std::string>::const_iterator i = 
        static_cast<std::map<std::string, std::string> *>(Variables)->find(searchName);
    if (i != ((std::map<std::string, std::string> *)Variables)->end()) {
        int Read = sscanf(i->second.c_str(), "%f,%f,%f", &tempPoint.x, &tempPoint.y, &tempPoint.z);
        if (Read != 3) {
            return Default;
        }
        return tempPoint;
    } else {
        return Default;
    }
}

