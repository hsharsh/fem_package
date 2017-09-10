#include "structure.h"

using namespace std;

int main(){
	ll nelm, tnod;
	cout << "Enter the number of elements: ";
	cin >> nelm;
	
	cout << "Enter the total number of nodes: ";
	cin >> tnod;


	Assembly m_assembly(nelm, tnod);
	vector<Element> mesh(nelm);

	REP(i, nelm){
		cout << "Enter the nodes connected to elements " << i+1 << ": ";
		vd connectivity(mesh[i].nnod);
		REP(j, mesh[i].nnod){
			cin >> connectivity[j];
		}
		m_assembly.build_connectivity(i,connectivity);
	}

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
		vd dof(mesh[i].nnod*mesh[i].ndof);
		REP(j, m_assembly.connectivity[i].size()){
			REP(k, mesh[i].ndof){
				dof[j*mesh[i].ndof + k] = (mesh[i].ndof * m_assembly.connectivity[i][j]) - (mesh[i].ndof - k);
			}
		}
		
		for(auto j : dof){
			cout << j << " ";
		}
		cout << endl;

		vdd kl = mesh[i].build_kl();
		REP(j, dof.size()){
			REP(k, dof.size()){
				m_assembly.k_global[dof[j]][dof[k]] += kl[j][k];
			}
		}
	}	

	REP(i,tnod){
		REP(j,tnod){
			cout << m_assembly.k_global[i][j] <<"\t";
		}
		cout << endl;
	}

}