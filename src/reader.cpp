#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

string readFromFile(string filename)
{
    string dataContent, line;
    ifstream dataFile(filename);

    cout << "\nReading -> " << filename.substr(5, 10) << '\n'
         << endl;

    if (dataFile.is_open())
    {
        while (getline(dataFile, line))
        {
            dataContent.append(line + '\n');
        }

        dataFile.close();
    }
    else
    {
        cerr << "ERROR: Could not open file." << endl;
        return "err";
    }

    return dataContent;
}

tuple<int, int, int, int, vector<vector<int>>, vector<vector<int>>> middlewareToRemoveNoises(string dataContent)
{
    // Tuple to return ordered values
    // disciplina
    // dias
    // salas
    // Horário
    // MAT (disciplina X salas)
    // MAT (disciplina X horário)
    tuple<int, int, int, int, vector<vector<int>>, vector<vector<int>>> inputValues;

    vector<int> allNumbers;
    int tmpNumber;
    bool read = false;

    // Remove dirty lines
    bool negativeNumber = false;
    for (int i = 0; i < dataContent.length() - 1; i++)
    {

        if (dataContent[i] == '\n')
        {
            read = true;
        }
        else if ((dataContent[i] == '#'))
        {
            read = false;
        }

        if (read)
        {
            // cout << dataContent[i] << endl;
            tmpNumber = dataContent[i] - '0';

            if (tmpNumber >= 0)
            {
                negativeNumber = false;
            }
            else
            {
                negativeNumber = true;
            }

            if (!negativeNumber && (dataContent[i + 1] - '0') < 0)
            {
                allNumbers.push_back(tmpNumber);
            }
            else if (!negativeNumber && (dataContent[i + 1] - '0') >= 0)
            {
                tmpNumber *= 10;
                allNumbers.push_back(tmpNumber);

                i += 1;
            }
        }
    }

    int disciplinas = allNumbers[0];
    int dias = allNumbers[1];
    int salas = allNumbers[2];
    int horarios = allNumbers[3];

    vector<vector<int>> disp_salas;
    vector<vector<int>> pref_horario;

    int k = 4;
    for (int i = 0; i < disciplinas; i++)
    {
        vector<int> tmpVector;
        for (int j = 0; j < salas; j++)
        {
            tmpVector.push_back(allNumbers[k]);
            k++;
        }

        disp_salas.push_back(tmpVector);
    }

    for (int i = 0; i < disciplinas; i++)
    {
        vector<int> tmpVector;
        for (int j = 0; j < horarios; j++)
        {
            tmpVector.push_back(allNumbers[k]);
            k++;
        }

        pref_horario.push_back(tmpVector);
    }

    inputValues = make_tuple(disciplinas, dias, salas, horarios, disp_salas, pref_horario);

    return inputValues;
}

void printFormated(int disciplinas, int dias, int salas, int horarios, vector<vector<int>> disp_salas, vector<vector<int>> pref_horario)
{
    cout << "disciplinas: " << disciplinas << endl;
    cout << "dias: " << dias << endl;
    cout << "salas: " << salas << endl;
    cout << "horario: " << horarios << endl;

    cout << "\nMAT (disciplina x salas): \n"
         << endl;
    for (int i = 0; i < disciplinas; i++)
    {
        for (int j = 0; j < salas; j++)
        {
            cout << "[" << disp_salas[i][j] << "] ";
        }
        cout << '\n';
    }

    cout << "\nMAT (disciplina x horario): \n"
         << endl;
    for (int i = 0; i < disciplinas; i++)
    {
        for (int j = 0; j < horarios; j++)
        {
            cout << "[" << pref_horario[i][j] << "] ";
        }
        cout << '\n';
    }
}