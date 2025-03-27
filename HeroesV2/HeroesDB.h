#pragma once

#include <iostream>
#include <string>
#include <map>
#include "Hero.h"
#include "enums.h"


class HeroesDB : public JSONBase
{
public:
    HeroesDB();
	virtual ~HeroesDB() {};
    size_t Count() { return _heroes.size(); }

    void SortByNameDescending();

    //----------------------------------------------------------------
    //                                                              //
    //		       ADD YOUR METHOD DECLARATIONS HERE                //
    //                                                              //
    std::vector<Hero> MergeSort(const std::vector<Hero>& heroes, SortBy sortByChoice);

    std::vector<Hero> Merge(const std::vector<Hero>& left, const std::vector<Hero>& right, SortBy sortByChoice);

    int BinarySearch(const std::vector<Hero>& heroes, const std::string& searchTerm, int low, int high);

    void FindHero(const std::string& heroName);

    void GroupHeroes();

    const std::vector<Hero>& GetHeroes() const { return _heroes; }

private:
    std::vector<Hero> _heroes;
    std::map<char, std::vector<Hero>> _groupedHeroes;

    static std::string toUpper(const std::string& str);
    static std::string toUpper2(const std::string& str);
    static bool charComparer(char c1, char c2);
    static bool isPrefix(const std::string& prefix, const std::string& word);

    virtual bool Deserialize(const std::string& s);
    virtual bool Deserialize(const rapidjson::Value& obj) { return false; };
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
};
