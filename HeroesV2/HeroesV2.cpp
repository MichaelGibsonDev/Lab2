#include <iostream>
#include "HeroesDB.h"
#include "Console.h"
#include "Input.h"
#include <locale>
#include "Tester.h"

int main()
{
    Tester v2Test;
    Console::ResizeWindow(150, 30);

    HeroesDB heroDB;

    int menuSelection = 0;
    std::vector<std::string> menuOptions{ "1. Sort by Name (descending)", "2. Sort By", "3. Find Hero (Binary Search)", "4. Print Group Counts", "5. Find All Heroes by first letter", "6. Remove Hero", "7. Exit" };
    std::vector<std::string> sortByOptions { "1. Intelligence", "2. Strength", "3. Speed", "4. Durability", "5. Power", "6. Combat" };

    do
    {
        Console::Clear();
        menuSelection = Input::GetMenuSelection(menuOptions);
        Console::Clear();


        //----------------------------------------------------------------
        //                                                              //
        //    Call your methods in the appropriate case statement       //
        //                                                              //
        switch (menuSelection)
        {
        case 1:
        {
            heroDB.SortByNameDescending();
            break;
        }
        case 2:
        {
            int sortBySelection = Input::GetMenuSelection(sortByOptions, "Sort by? ");
            SortBy sortByChoice;
            switch (sortBySelection)
            {
            case 1: sortByChoice = Intelligence; break;
            case 2: sortByChoice = Strength; break;
            case 3: sortByChoice = Speed; break;
            case 4: sortByChoice = Durability; break;
            case 5: sortByChoice = Power; break;
            case 6: sortByChoice = Combat; break;
            }

            std::vector<Hero> sortedHeroes = heroDB.MergeSort(heroDB.GetHeroes(), sortByChoice);

            for (const auto& hero : sortedHeroes)
            {
                std::cout << hero.Id() << ": " << hero.Name() << " (" << hero.GetSortByAttribute(sortByChoice) << ")" << std::endl;
            }
        }
        case 3:
        {
            std::string heroToFind = Input::GetString("Enter hero name to search: ");
            heroDB.FindHero(heroToFind);
            break;
        }
        case 4:
        {
            heroDB.PrintGroupCounts();
            break;
        }
        case 5:
        {
            std::string letter = Input::GetString("Enter a letter to search a Hero: ");
            heroDB.FindHeroesByLetter(letter);
            break;
        }
        case 6:
        {

            break;
        }
        default:
            break;
        }

        Input::PressEnter();

    } while (menuSelection != menuOptions.size());

    return 0;
}