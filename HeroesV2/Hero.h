#pragma once
#include "JSONBase.h"
#include <vector>
#include "enums.h"
//----------------------------------------------------------------
//                                                              //
//		        DO NOT EDIT THE CODE BELOW                      //
//                                                              //
struct HeroStats
{
    int Intelligence;
    int Strength;
    int Speed;
    int Durability;
    int Power;
    int Combat;

    bool Deserialize(const rapidjson::Value& obj);
};

struct HeroAppearance
{
    std::string Gender;
    std::string Race;
    std::vector<std::string> Height;
    std::vector<std::string> Weight;
    std::string EyeColor;
    std::string HairColor;

    bool Deserialize(const rapidjson::Value& obj);
};

struct HeroBio
{
    std::string FullName;
    std::string AlterEgos;
    std::vector<std::string> Aliases;
    std::string PlaceOfBirth;
    std::string FirstAppearance;
    std::string Publisher;
    std::string Alignment;

    bool Deserialize(const rapidjson::Value& obj);
};
struct HeroWork
{
    std::string Occupation;
    std::string Base;

    bool Deserialize(const rapidjson::Value& obj);
};
struct HeroConnections
{
    std::string GroupAffiliation;
    std::string Relatives;

    bool Deserialize(const rapidjson::Value& obj);
};
struct HeroImages
{
    std::string XS;
    std::string SM;
    std::string MD;
    std::string LG;

    bool Deserialize(const rapidjson::Value& obj);
};

class Hero : public JSONBase
{
public:
    Hero();
    Hero(const rapidjson::Value& obj);

    virtual bool Deserialize(const rapidjson::Value& obj);
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

    // Getters/Setters.
    int Id() const { return _id; }
    void Id(int id) { _id = id; }

    const std::string& Name() const { return _name; }
    void Name(const std::string& name) { _name = name; }

    const HeroStats& Powerstats() const { return _powerstats; }
    void Powerstats(const HeroStats& powerstats) { _powerstats = powerstats; }

    const HeroAppearance& Appearance() const { return _appearance; }
    void Appearance(HeroAppearance appearance) { _appearance = appearance; }

    const HeroBio& Biography() const { return _biography; }
    void Biography(HeroBio biography) { _biography = biography; }

    const HeroWork& Work() const { return _work; }
    void Work(HeroWork work) { _work = work; }

    const HeroConnections& Connections() const { return _connections; }
    void Connections(HeroConnections connections) { _connections = connections; }

    const HeroImages& Images() const { return _images; }
    void Images(HeroImages images) { _images = images; }

    std::string GetSortByAttribute(SortBy sortByChoice) const;
    static int Compare(const Hero& hero1, const Hero& hero2, SortBy sortByChoice);

private:
    int _id;
    std::string _name;

    HeroStats _powerstats;
    HeroAppearance _appearance;
    HeroBio _biography;
    HeroWork _work;
    HeroConnections _connections;
    HeroImages _images;

    bool Equals(Hero other);
};

