#include "HeroesDB.h"
#include <iostream>
#include "Console.h"
#include <algorithm> 
#include <string_view>
#include <locale>
#include <cctype>

//----------------------------------------------------------------
//                                                              //
//		        ADD YOUR METHOD DEFINITIONS HERE                //
//                                                              //
std::vector<Hero> HeroesDB::Merge(const std::vector<Hero>& left, const std::vector<Hero>& right, SortBy sortByChoice)
{
	std::vector<Hero> result;
	std::vector<Hero> leftCopy = left;
	std::vector<Hero> rightCopy = right;

	while (!leftCopy.empty() && !rightCopy.empty())
	{
		int compResult = Hero::Compare(leftCopy.front(), rightCopy.front(), sortByChoice);
		if (compResult <= 0)
		{
			result.push_back(leftCopy.front());
			leftCopy.erase(leftCopy.begin());
		}
		else
		{
			result.push_back(rightCopy.front());
			rightCopy.erase(rightCopy.begin());
		}
	}

	while (!leftCopy.empty())
	{
		result.push_back(leftCopy.front());
		leftCopy.erase(leftCopy.begin());
	}

	while (!rightCopy.empty())
	{
		result.push_back(rightCopy.front());
		rightCopy.erase(rightCopy.begin());
	}

	return result;
}

std::vector<Hero> HeroesDB::MergeSort(const std::vector<Hero>& heroes, SortBy sortByChoice)
{
	if (heroes.size() <= 1)
	{
		return heroes;
	}

	std::vector<Hero> left;
	std::vector<Hero> right;
	size_t middle = heroes.size() / 2;

	for (size_t i = 0; i < middle; i++)
	{
		left.push_back(heroes[i]);
	}
	for (size_t i = middle; i < heroes.size(); i++)
	{
		right.push_back(heroes[i]);
	}

	left = MergeSort(left, sortByChoice);
	right = MergeSort(right, sortByChoice);

	return Merge(left, right, sortByChoice);
}

int HeroesDB::BinarySearch(const std::vector<Hero>& heroes, const std::string& searchTerm, int low, int high)
{
	if (high < low)
		return -1;

	int mid = (low + high) / 2;

	std::string searchUpper = toUpper(searchTerm);
	std::string heroNameUpper = toUpper(heroes[mid].Name());

	if (searchUpper < heroNameUpper)
	{
		return BinarySearch(heroes, searchTerm, low, mid - 1);
	}
	else if (searchUpper > heroNameUpper)
	{
		return BinarySearch(heroes, searchTerm, mid + 1, high);
	}
	else
	{
		return mid;
	}
}

void HeroesDB::FindHero(const std::string& heroName)
	{
		int index = BinarySearch(_heroes, heroName, 0, _heroes.size() - 1);

		if (index == -1)
		{
			std::cout << heroName << " was not found." << std::endl;
		}
		else
		{
			std::cout << heroName << " was found at index " << index << "." << std::endl;
		}
	}

void HeroesDB::GroupHeroes()
{
	_groupedHeroes.clear();

	for (const Hero& hero : _heroes)
	{
		std::string heroName = hero.Name();
		if (!heroName.empty())
		{
			char key = std::toupper(heroName[0]);

			auto it = _groupedHeroes.find(key);
			if (it == _groupedHeroes.end())
			{
				std::vector<Hero> heroVec;
				heroVec.push_back(hero);
				_groupedHeroes[key] = heroVec;
			}
			else
			{
				it->second.push_back(hero);
			}
		}
	}
}

void HeroesDB::PrintGroupCounts()
{
	if (_groupedHeroes.empty())
	{
		GroupHeroes();
	}

	for (const auto& entry : _groupedHeroes) 
	{
		char keyLower = std::tolower(entry.first);
		size_t count = entry.second.size();
		std::cout << keyLower << ": " << count << std::endl;
	}
}

//----------------------------------------------------------------
//                                                              //
//		        DO NOT EDIT THE CODE BELOW                      //
//                                                              //


HeroesDB::HeroesDB()
{
	DeserializeFromFile("heroes.json");
}

std::string HeroesDB::toUpper(const std::string& str)
{
	std::string copy = str;
	std::transform(copy.begin(),
		copy.end(),
		copy.begin(),
		[](unsigned char c) { return std::toupper(c); });
	return copy;
}

std::string HeroesDB::toUpper2(const std::string& str)
{
	std::string copy = str;
	for (auto& c : copy) c = toupper(c);
	return copy;
}

void HeroesDB::SortByNameDescending()
{
	std::vector<Hero> sorted(_heroes); //clone the list

	size_t n = sorted.size();
	bool swapped;
	do
	{
		swapped = false;
		for (size_t i = 1; i <= n - 1; i++)
		{
			int compResult = _stricmp(sorted[i - 1].Name().c_str(), sorted[i].Name().c_str());
			//int compResult = toUpper(sorted[i - 1].Name()).compare(toUpper(sorted[i].Name()));
			if (compResult < 0)
			{
				swapped = true;
				std::swap(sorted[i - 1], sorted[i]);

				//int temp = vec[i - 1];
				//vec[i - 1] = vec[i];
				//vec[i] = temp;
			}
		}
		--n;
	} while (swapped);

	for (auto& hero : sorted)
	{
		std::cout << hero.Id() << ": " << hero.Name() << std::endl;
	}
	std::cout << std::endl;
}
bool HeroesDB::charComparer(char c1, char c2)
{
	return std::tolower(c1, std::locale()) == std::tolower(c2, std::locale());
}
bool HeroesDB::isPrefix(const std::string& prefix, const std::string& word)
{
	return  (std::mismatch(prefix.begin(), prefix.end(),
		word.begin(), word.end(),
		charComparer)).first == prefix.end();
}


bool HeroesDB::Deserialize(const std::string& s)
{
	rapidjson::Document doc;
	if (!InitDocument(s, doc))
		return false;

	if (!doc.IsArray())
		return false;


	_heroes.reserve(doc.Size());

	for (rapidjson::SizeType i = 0; i < doc.Size(); ++i)
	{
		rapidjson::Value& node = doc[i];
		Hero myHero(node);
		_heroes.push_back(myHero);
	}

	return true;
}

bool HeroesDB::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	return true;
}