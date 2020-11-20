#include <iostream>
#include "reader.h"
#include "genetic.h"

using namespace std;

int main()
{
    int disciplinas, dias, salas, horarios;
    vector<vector<int>> disp_salas, pref_horario;
    string dataContent = readFromFile("data/10_5_5_8-1.dat");

    if (dataContent != "err")
    {
        tie(disciplinas, dias, salas, horarios, disp_salas, pref_horario) = middlewareToRemoveNoises(dataContent);
        printFormated(disciplinas, dias, salas, horarios, disp_salas, pref_horario);

        geneticWorks();
    }
    else
    {
        cerr << "ERROR: invalid input!" << endl;
    }

    return (0);
}