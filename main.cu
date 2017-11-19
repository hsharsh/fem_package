#include "structure.h"
#include "assembly.h"
#include "device.cuh"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv){
	freopen("paralleloutput.o","w",stdout);
	ll nelm = 0, tnod = 0, ndof = 0, nnod = 0;
	string type;

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
					
					bool negative = false;
					if(s.substr(0,1) == "-")
						negative = true;
					num = stoll(s.substr((negative ? 1 : 0),decimal - (negative ? 1 : 0)));
					if(decimal != (s.size()-1)){
						num += stoll("0" + s.substr(decimal+1,s.size()-decimal-2)) * pow(10, -1 * (int)(s.size()-decimal-2)) ;
					}
					if(negative)
						num *= -1;
					
					if(j != 0)
						temp.push_back(num);
					ss.ignore();
				}
				x.push_back(temp);
				tnod++;

			}
		}

		if(line.substr(0,8) == "*Element"){

			type = line.substr(15,line.size()-15);
 			if(type.size() >= 4 && type.substr(0,4) == "C3D4"){
				ndof = 3;
				nnod = 4;
			}
			if(type.size() >= 5 && type.substr(0,5) == "C3D10"){
				ndof = 3;
				nnod = 10;
			}
			cout << nnod << endl;
			while(getline(input, line) && (line.substr(0,1).compare("*"))){
				cout << line << endl;
				stringstream ss(line);
				ll k;
				vd temp;

				REP(j, nnod + 1){
					ss >> k;
					if(j != 0)
						temp.push_back(k);
					ss.ignore();
				}
				nelm++;
				connectivity.push_back(temp);
			}

		}
	}


	Assembly 		m_assembly(nelm, tnod, ndof);
	vector<Node> 	nodes(tnod,Node(ndof));
	if(type.size() >= 4 && type.substr(0,4) == "C3D4")
		vector<Element> mesh(nelm,Tetra_linear());
	if(type.size() >= 5 && type.substr(0,5) == "C3D10")
		vector<Element> mesh(nelm,Tetra_quadratic());

	REP(i, tnod){
		nodes[i].build_x(x[i]);
	}


	cout << "Nodes: " << endl << endl;
	REP(i, tnod){
		cout << "Node " << i+1 << ": ";
		REP(j, 3){
			cout << x[i][j] << " ";
		}
		cout << endl;
	}

	double kl[nelm*nnod*ndof*nnod*ndof];

	REP(k, nelm){
		REP(i, nnod*ndof){
			REP(j, nnod*ndof){
				kl[k*nnod*ndof*nnod*ndof + i*nnod*ndof + j] = 0.0;
				//cout << kl[i*nnod*ndof + j] << " ";
			}
			//cout << endl;
		}
	}

	cout << endl;
	cout << "Connectivity matrix: " << endl << endl;
	REP(i,nelm){
		cout << "Element " << i+1 << ": ";
		vdd node(nnod,vd(3));
	    REP(j, nnod){
	        REP(k, 3){
	        	//cout << connectivity[i][j] << "->" << x[connectivity[i][j]-1][k] << " ";
	            node[j][k] = x[connectivity[i][j]-1][k];
	        }
	       // cout << endl;
	    }
	    vdd k_local;
	    if(type.size() >= 4 && type.substr(0,4) == "C3D4")
			k_local = build_k(node);
		if(type.size() >= 5 && type.substr(0,5) == "C3D10")
			k_local = vdd(30,vd(30,0));
		
		REP(j, nnod*ndof){
			REP(k, nnod*ndof){
				kl[i*nnod*ndof*nnod*ndof + j*nnod*ndof + k] = k_local[j][k];
				//cout << kl[i*nnod*ndof + j] << " ";
			}
			//cout << endl;
		}

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

	int dof[nelm*nnod*ndof];
	REP(i, nelm){
		REP(j, m_assembly.connectivity[i].size()){
			REP(k, ndof){
				dof[i*nnod*ndof + j*ndof + k] = (ndof * m_assembly.connectivity[i][j]) - (ndof - k);
				//cout << dof[i*nnod*ndof + j*ndof + k] << " ";
			}
		}
		//cout << endl;
	}

	double kg[tnod*ndof*tnod*ndof];
	
	REP(i, tnod*ndof){
		REP(j, tnod*ndof){
			kg[i*tnod*ndof + j] = 0.0;
		}
	}


/*
	cout << endl << "Dof matrix:" << endl;
	REP(i, nelm){
		REP(j, nnod*ndof){
			cout << dof[i*nnod*ndof + j] << " ";
		}
		cout << endl;
	}
*/

	double (*pkg), (*pkl);
	int (*pdof);

	cudaMalloc((void**)&pdof, (nelm*nnod*ndof)*sizeof(int));
	cudaMalloc((void**)&pkg, (tnod*ndof*tnod*ndof)*sizeof(double));
	cudaMalloc((void**)&pkl, (nelm*nnod*ndof*nnod*ndof)*sizeof(double));

	cudaMemcpy(pdof, dof, (nelm*nnod*ndof)*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(pkl, kl, (nelm*nnod*ndof*nnod*ndof)*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(pkg, kg, (tnod*ndof*tnod*ndof)*sizeof(double), cudaMemcpyHostToDevice);

	int numBlocks = nelm;
	dim3 threadsPerBlock(nnod*ndof,nnod*ndof);
	MatAdd<<<numBlocks,threadsPerBlock>>>(pkg,pkl,pdof,nnod*ndof,tnod*ndof);

	cudaMemcpy(kg, pkg, (tnod*ndof*tnod*ndof)*sizeof(double), cudaMemcpyDeviceToHost);

	cudaFree(pdof); 
	cudaFree(pkl);
	cudaFree(pkg);


	cout << endl;
	cout << "K global:" << endl << endl;
	REP(i,tnod*ndof){
		REP(j,tnod*ndof){
			cout << kg[i*tnod*ndof + j] << " ";
		}
		cout << ";" << endl;
	}
}
