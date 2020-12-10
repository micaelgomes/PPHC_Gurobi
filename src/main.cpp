#include <iostream>
#include "reader.h"
#include "gurobi_c++.h"

using namespace std;

int main()
{
	int disciplinas, dias, salas, horarios;
	vector<vector<int>> disp_salas, pref_horario;
	string dataContent = readFromFile("data/80_5_5_8-1.dat");

	if (dataContent != "err")
	{
		// get values from file .dat
		tie(disciplinas, dias, salas, horarios, disp_salas, pref_horario) = middlewareToRemoveNoises(dataContent);
		
		// this function print data like Matrix
		printFormated(disciplinas, dias, salas, horarios, disp_salas, pref_horario);

		try
		{
			// Create an environment
			GRBEnv env = GRBEnv(true);
			env.set("LogFile", "ppch.log");
			env.start();

			// Create an empty model
			GRBModel model = GRBModel(env);

			// Create variable X_jtkh
			GRBVar x[disciplinas][dias][salas][horarios];
			// Create variable Y_k
			GRBVar y[salas];

			// Attr value to vars
			for (int j = 0; j < disciplinas; j++)
			{
				for (int t = 0; t < dias; t++)
				{
					for (int k = 0; k < salas; k++)
					{
						for (int h = 0; h < horarios; h++)
						{
							string label = "X_" + to_string(j) + "_" + to_string(t) + "_" + to_string(k) + "_" + to_string(h);
							x[j][t][k][h] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, label);
						}
					}
				}
			}

			for (int k = 0; k < salas; k++)
			{
				string label = "Y_" + to_string(k);
				y[k] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, label);
			}

			// Set objective
			GRBLinExpr fo = 0, fo_yk = 0;

			// get all room used
			for(int k = 0; k < salas; k++ ){
				fo_yk += y[k];
			}

			// get sum value
			for (int j = 0; j < disciplinas; j++)
			{
				for (int t = 0; t < dias; t++)
				{
					for (int k = 0; k < salas; k++)
					{
						for (int h = 0; h < horarios; h++)
						{	
							fo += x[j][t][k][h]*pref_horario[j][h];	
						}
					}
				}
			}

			model.setObjective(fo - fo_yk, GRB_MAXIMIZE);
			model.update();

			// Constraint 1 
			for (int j = 0; j < disciplinas; j++)
			{
				GRBLinExpr c1 = 0;
				
				for (int t = 0; t < dias; t++)
				{
					for (int k = 0; k < salas; k++)
					{
						for (int h = 0; h < horarios; h++)
						{
							c1 += x[j][t][k][h];
						}
					}
				}

				// Add constraint: c1
				string label = "c1_" + to_string(j);
				model.addConstr(c1 == 2, label);
			}

			// Constraint 2
			for (int t = 0; t < dias; t++)
			{
				for (int k = 0; k < salas; k++)
				{
					for (int h = 0; h < horarios; h++)
					{
						GRBLinExpr c2 = 0;

						for (int j = 0; j < disciplinas; j++)
						{
							c2 += x[j][t][k][h];
						}

						// Add constraint: c2
						string label = "c2_" + to_string(t) + '-' + to_string(k) + '-' + to_string(h);			
						model.addConstr(c2 <= 1, label);
					}
				}
			}

			// Constraint 3
			for (int j = 0; j < disciplinas; j++)
			{
				for (int k = 0; k < salas; k++)
				{
					GRBLinExpr c3 = 0, c_jk = disp_salas[j][k];

					for (int t = 0; t < dias; t++)
					{
						for (int h = 0; h < horarios; h++)
						{
							c3 += x[j][t][k][h];
						}
					}

					// Add constraint: c3
					string label = "c3_" + to_string(j) + '-' + to_string(k);	
					model.addConstr(c3 <= c_jk, label);
				}
			}

			// Constraint 4
			for (int j = 0; j < disciplinas; j++)
			{
				for (int t = 0; t < dias; t++)
				{
					for (int k = 0; k < salas; k++)
					{
						for (int h = 0; h < horarios; h++)
						{
							// Add constraint: c4
							string label = "c4_" + to_string(j) + '-' + to_string(t) + '-' + to_string(k) + '-' + to_string(h) + "_Y_" + to_string(k);	
							model.addConstr(x[j][t][k][h] <= y[k], label);
						}
					}
				}
			}

			model.update();
			model.optimize();

			// check model
			model.write("ppch_model.lp");

			// Print result in Grid
			bool empty = true;
			for (int k = 0; k < salas; k++)
			{
        cout << "\nSALA - " << (k+1) << endl;
        cout << "---------------------------------------------------------------------" << endl;
        cout << "            |";

  			for (int t = 0; t < dias; t++)
  			{
          cout << "| DIA - " << (t+1) << " |";
        }

        cout << "|" << endl;
          
        for (int h = 0; h < horarios; h++)
				{
          cout << "---------------------------------------------------------------------" << endl;
          cout << (h+1) << "º horário  |";
          
          for (int t = 0; t < dias; t++){
          	empty = true;

          	for (int j = 0; j < disciplinas; j++){
          		
          		if ( x[j][t][k][h].get(GRB_DoubleAttr_X) > 0 ){
	              if (j < 9) 
	              	cout << "|    " << (j+1) << "    |";
	              else 
	              	cout << "|   " << (j+1) << "    |";
	              
	              empty = false;
	              break;
	            }
          	}

          	if(empty) cout << "|         |";           
          }

          cout << "|" << endl;
				}

        cout << "---------------------------------------------------------------------" << endl;
        cout << "\n" << endl;
			}

			cout << "SALAS USADAS: ";
			for (int k = 0; k < salas; k++)
			{
				if(y[k].get(GRB_DoubleAttr_X) > 0){
					cout << "[ "<< (k+1) << " ]";
				}
			}
			cout << endl;

			cout << "\nValor da F.O: " << model.get(GRB_DoubleAttr_ObjVal) << "\n" << endl;
		}
		catch (GRBException e)
		{
			cout << "Error code = " << e.getErrorCode() << endl;
			cout << e.getMessage() << endl;
		}
		catch (...)
		{
			cout << "Exception during optimization" << endl;
		}
	}
	else
	{
		cerr << "ERROR: invalid input!" << endl;
	}

	return (0);
}
