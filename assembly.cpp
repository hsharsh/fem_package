#include "structure.h"

using namespace std;

int main(int argc, char** argv){
	freopen("serialoutput.o","w",stdout);
	ll nelm = 0, tnod = 0, ndof = 0, nnod = 0;

	ifstream input(argv[1]);
	vdd connectivity;
	vdd x;

	for(string line; getline(input,line);){
		if(line.substr(0,5) == "*Node"){
			while(getline(input, line) && (line.substr(0,1).compare("*"))){
				stringstream ss(line);
				string s;
				vd temp;
				REP(j, 4){
					ss >> s;

					int decimal = s.size()-1;
					REP(k, s.size()){
						if(s[k] == '.')
							decimal = k;
					}

					double num = 0;
					num = stoll(s.substr(0,decimal));
					if(decimal != (s.size()-1)){
						num += stoll("0" + s.substr(decimal+1,s.size()-decimal-2)) * pow(10, -1 * (int)(s.size()-decimal-2)) ;
					}
					if(j != 0)
						temp.push_back(num);
					ss.ignore();
				}
				tnod++;
				x.push_back(temp);
			}
		}

		if(line.substr(0,8) == "*Element"){
			string type = line.substr(15,line.size()-15);
			if(type == "C3D4"){
				ndof = 3;
				nnod = 4;
			}
			while(getline(input, line) && (line.substr(0,1).compare("*"))){
				stringstream ss(line);
				ll k;
				vd temp;
				REP(j, nnod + 1){
					ss >> k;
					if(j != 0)
						temp.push_back(k);
					ss.ignore();
				}
				connectivity.push_back(temp);
				nelm++;
			}
		}
	}


	Assembly m_assembly(nelm, tnod, ndof);
	vector<Node> 	nodes(tnod,Node(ndof));
	vector<Element> mesh(nelm,Element(ndof,4));

	REP(i, tnod){
		nodes[i].build_x(x[i]);
	}

	cout << "Nodes: " << endl;
	REP(i, tnod){
		cout << "Node " << i+1 << ": ";
		REP(j, 3){
			cout << x[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	cout << "Connectivity matrix: " << endl;
	REP(i,nelm){
		cout << "Element " << i+1 << ": ";
		REP(j,nnod)
			cout << connectivity[i][j]<< " ";
		cout << endl;
	}
	m_assembly.build_connectivity(connectivity);
/*
	cout << "Connectivity matrix : " << endl;
	REP(i, nelm){
		for(auto j : m_assembly.connectivity[i]){
			cout << j << " ";
		}
		cout << endl;
	}
*/

	REP(i, nelm){
		vd dof(mesh[i].nnod*ndof);
		REP(j, m_assembly.connectivity[i].size()){
			REP(k, ndof){
				dof[j*ndof + k] = (ndof * m_assembly.connectivity[i][j]) - (ndof - k);
			}
		}
/*		
		for(auto j : dof){
			cout << j+1 << " ";
		}
		cout << endl;
*/
		vdd kl = mesh[i].build_kl();
		REP(j, dof.size()){
			REP(k, dof.size()){
				m_assembly.k_global[dof[j]][dof[k]] += kl[j][k];
			}
		}
	}	

	cout << endl;
	cout << "K global:" << endl << endl;
	REP(i,tnod*ndof){
		REP(j,tnod*ndof){
			cout << m_assembly.k_global[i][j] << " ";
/*			if(m_assembly.k_global[i][j])
				cout << "x";
			else
				cout << "o";
*/		}
		cout << endl;
	}

}