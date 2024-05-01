#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class Member
{
public:
    string DNA;
    int Fitness;
};

class Population
{
public:
    vector<Member> Members;
};

//* Function to calculate fitness
int CalculateFitness(const string &DNA, const string &targetDNA)
{
    int fitness = 0;
    for (size_t i = 0; i < DNA.size(); ++i)
    {
        if (DNA[i] == targetDNA[i])
        {
            ++fitness;
        }
    }
    return fitness;
}

//* Function to perform crossover
string Crossover(const string &parent1, const string &parent2)
{
    string child = parent1;
    for (size_t i = 0; i < parent1.size(); ++i)
    {
        if (rand() % 2 == 0)
        {
            child[i] = parent2[i];
        }
    }
    return child;
}

//* Function to apply mutation
void Mutate(string &DNA, int mutationRate)
{
    for (char &gene : DNA)
    {
        if (rand() % 1000 < mutationRate)
        {
            gene = rand() % 96 + 32;
        }
    }
}

bool fitness_comparison(const Member &a, const Member &b)
{
    return a.Fitness > b.Fitness;
}

int main()
{
    string targetDNA = "KYaaaaaaaa!! HOOOO raha haiiiii!!! Yahahah !! KYAAAAA!?";
    int populationSize = 1000;
    int mutationRate = 25; //* 0.01% mutatIs This daaamn op!nullptr)));

    Population population;
    population.Members.resize(populationSize);

    //! Initialize population with random DNA

    for (auto &member : population.Members)
    {
        member.DNA.resize(targetDNA.size());
        for (size_t j = 0; j < targetDNA.size(); ++j)
        {
            member.DNA[j] = static_cast<char>(rand() % 96 + 32);
        }
        member.Fitness = CalculateFitness(member.DNA, targetDNA);
    }

    int generation = 0;
    bool sequenceFound = false;
    int finalFitness = 0;
    string finalSequence;

    while (!sequenceFound)
    {
        ++generation;

        // Sort population by fitness
        // sort(population.Members.begin(), population.Members.end(), [](const Member &a, const Member &b)
        //      { return a.Fitness > b.Fitness; });
        sort(population.Members.begin(), population.Members.end(), fitness_comparison);

        // Check if sequence found
        if (population.Members[0].Fitness == targetDNA.size())
        {
            sequenceFound = true;
            finalFitness = population.Members[0].Fitness;
            finalSequence = population.Members[0].DNA;
            break;
        }

        // Select parents for crossover
        vector<Member> parents{population.Members[0], population.Members[1]};

        // Create new generation
        for (size_t i = 0; i < population.Members.size(); ++i)
        {
            string childDNA = Crossover(parents[0].DNA, parents[1].DNA);
            Mutate(childDNA, mutationRate);
            population.Members[i].DNA = childDNA;
            population.Members[i].Fitness = CalculateFitness(childDNA, targetDNA);
        }

        // Print progress
        cout << "Generation: " << generation << ", Highest Fitness: " << population.Members[0].Fitness
             << ", Sequence: " << population.Members[0].DNA << endl;
    }

    // Display final sequence, generation, and fitness
    cout << "Final Sequence: " << finalSequence << endl;
    cout << "Generation " << generation << ": Sequence evolved to the target! Final Fitness: " << finalFitness << endl;

    return 0;
}