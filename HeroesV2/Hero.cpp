#include "Hero.h"
#include <iostream>
//----------------------------------------------------------------
//                                                              //
//		        DO NOT EDIT THE CODE BELOW                      //
//                                                              //
bool HeroStats::Deserialize(const rapidjson::Value& obj)
{
	Intelligence = (obj["intelligence"].GetInt());
	Strength = (obj["strength"].GetInt());
	Speed = (obj["speed"].GetInt());
	Durability = (obj["durability"].GetInt());
	Power = (obj["power"].GetInt());
	Combat = (obj["combat"].GetInt());
	return true;
}
bool HeroAppearance::Deserialize(const rapidjson::Value& obj)
{
	Gender = obj["gender"].GetString();
	if(obj["race"].IsString())
		Race = obj["race"].GetString();

	const rapidjson::Value& heights = obj["height"];
	for (rapidjson::SizeType i = 0; i < heights.Size(); ++i)
	{
		Height.push_back(heights[i].GetString());
	}

	const rapidjson::Value& weights = obj["weight"];
	for (rapidjson::SizeType i = 0; i < weights.Size(); ++i)
	{
		Weight.push_back(weights[i].GetString());
	}

	EyeColor = obj["eyeColor"].GetString();
	HairColor = obj["hairColor"].GetString();
	return true;
}
bool HeroBio::Deserialize(const rapidjson::Value& obj)
{
	FullName = obj["fullName"].GetString();
	AlterEgos = obj["alterEgos"].GetString();

	const rapidjson::Value& aliases = obj["aliases"];
	for (rapidjson::SizeType i = 0; i < aliases.Size(); ++i)
	{
		Aliases.push_back(aliases[i].GetString());
	}
	PlaceOfBirth = obj["placeOfBirth"].GetString();
	FirstAppearance = obj["firstAppearance"].GetString();
	if (obj["publisher"].IsString())
		Publisher = obj["publisher"].GetString();
	Alignment = obj["alignment"].GetString();
	return true;
}
bool HeroWork::Deserialize(const rapidjson::Value& obj)
{
	Occupation = obj["occupation"].GetString();
	Base = obj["base"].GetString();
	return true;
}
bool HeroConnections::Deserialize(const rapidjson::Value& obj)
{
	GroupAffiliation = obj["groupAffiliation"].GetString();
	Relatives = obj["relatives"].GetString();
	return true;
}
bool HeroImages::Deserialize(const rapidjson::Value& obj)
{
	XS = obj["xs"].GetString();
	SM = obj["sm"].GetString();
	MD = obj["md"].GetString();
	LG = obj["lg"].GetString();
	return true;
}

Hero::Hero() : _id(-1)
{ }
Hero::Hero(const rapidjson::Value& obj)
{
	Deserialize(obj);
}
bool Hero::Equals(Hero other)
{
	return _name == other._name && _id == other._id;
}


bool Hero::Deserialize(const rapidjson::Value& obj)
{
	Id(obj["id"].GetInt());
	Name(obj["name"].GetString());

	_powerstats.Deserialize(obj["powerstats"].GetObject());
	_appearance.Deserialize(obj["appearance"].GetObject());
	_biography.Deserialize(obj["biography"].GetObject());
	_work.Deserialize(obj["work"].GetObject());
	_connections.Deserialize(obj["connections"].GetObject());
	_images.Deserialize(obj["images"].GetObject());

	//read object for Stats, Appearance, Bio, etc

	return true;
}

bool Hero::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{

	return true;
}

std::string Hero::GetSortByAttribute(SortBy sortByChoice) const
{
	std::string attribute;
	switch (sortByChoice)
	{
	case Intelligence:
		attribute = std::to_string(Powerstats().Intelligence);
		break;
	case Strength:
		attribute = std::to_string(Powerstats().Strength);
		break;
	case Speed:
		attribute = std::to_string(Powerstats().Speed);
		break;
	case Durability:
		attribute = std::to_string(Powerstats().Durability);
		break;
	case Power:
		attribute = std::to_string(Powerstats().Power);
		break;
	case Combat:
		attribute = std::to_string(Powerstats().Combat);
		break;
	default:
		break;
	}
	return attribute;
}
int Hero::Compare(const Hero& hero1, const Hero& hero2, SortBy sortByChoice)
{
	int attr1 = 0, attr2 = 0;
	switch (sortByChoice)
	{
	case Intelligence:
		attr1 = hero1.Powerstats().Intelligence;
		attr2 = hero2.Powerstats().Intelligence;
		break;
	case Strength:
		attr1 = hero1.Powerstats().Strength;
		attr2 = hero2.Powerstats().Strength;
		break;
	case Speed:
		attr1 = hero1.Powerstats().Speed;
		attr2 = hero2.Powerstats().Speed;
		break;
	case Durability:
		attr1 = hero1.Powerstats().Durability;
		attr2 = hero2.Powerstats().Durability;
		break;
	case Power:
		attr1 = hero1.Powerstats().Power;
		attr2 = hero2.Powerstats().Power;
		break;
	case Combat:
		attr1 = hero1.Powerstats().Combat;
		attr2 = hero2.Powerstats().Combat;
		break;
	default:
		break;
	}

	int compResult =
		(attr1 == attr2) ? 0 :
		(attr1 < attr2) ? -1 :
		1;

	return compResult;
}