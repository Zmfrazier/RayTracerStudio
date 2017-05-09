#ifndef __SCENECONFIGURATION_HPP
#define __SCENECONFIGURATION_HPP
#include <string>

#include "Primitives.hpp"

class SceneConfiguration {
private:
    void* Variables;
    void* Sections;
    const std::string Filename;
    std::string section;
    bool Loaded;
public:
    bool GetBooleanValueOf(const std::string& Name, bool Default) const;
    float GetFloatValueOf(const std::string& Name, const float Default) const;
    const std::string& GetStringValueOf(const std::string& Name, const std::string& Default) const;
    int GetIntegerValueOf(const std::string& Name, int Default) const;
    Vector GetVectorValueOf(const std::string& Name, const Vector& Default) const;
    Point GetPointValueOf(const std::string& Name, const Point& Default) const;
    
    int ParseInputBySectionName(const std::string &Name);
    ~SceneConfiguration();
    SceneConfiguration(const std::string &FileName);
};

#endif 
