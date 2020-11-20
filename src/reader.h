#ifndef _H_READER
#define _H_READER

#include <vector>
#include <tuple>

using namespace std;

/**
 * @param filename
 * @return file data to memory.
 */
string readFromFile(string filename);

/**
 * @param
 * @return clear noises from data.
 */
tuple<int, int, int, int, vector<vector<int>>, vector<vector<int>>> middlewareToRemoveNoises(string dataContent);

/**
 * @param all
 * @return print all infos in memory.
 */
void printFormated(int disciplinas, int dias, int salas, int horarios, vector<vector<int>> disp_salas, vector<vector<int>> pref_horario);

#endif
