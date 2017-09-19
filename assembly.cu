#include "structure.h"
#include <bits/stdc++.h>
using namespace std;


__device__ double datomicAdd(double* address, double val)
{
    unsigned long long int* address_as_ull =
                             (unsigned long long int*)address;
    unsigned long long int old = *address_as_ull, assumed;
    do {
        assumed = old;
old = atomicCAS(address_as_ull, assumed,
                        __double_as_longlong(val +
                               __longlong_as_double(assumed)));
    } while (assumed != old);
    return __longlong_as_double(old);
}

__global__ void MatAdd(double kg[], double kl[], int dof[], int sizekl, int sizekg){
           int i = blockIdx.x;
           int j = threadIdx.x;
           int k = threadIdx.y;
           //printf("Element %d: %d %d Dofi:%d Dofj:%d Kl:%d Kg:%d\n", i, j, k, dof[i][j], dof[i][k], kl[j][k], kg[dof[i][j]][dof[i][k]]);
           //kg[dof[i][j]][dof[i][k]] = kg[dof[i][j]][dof[i][k]] + kl[j][k];
           datomicAdd( &(kg[dof[i*sizekl + j]*sizekg + dof[i*sizekl + k]]), kl[j*sizekl +k]);
			__syncthreads();
       }

ll stoll(string s){
	ll number = 0;
	DFOR(i,s.size()-1,0){
		number = number + (s[i]-'0') * pow(10,s.size()-i-1);
	}
	return number;
}

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
					num = stoll(s.substr(0,decimal));
					if(decimal != (s.size()-1)){
						num += stoll("0" + s.substr(decimal+1,s.size()-decimal-2)) * pow(10, -1 * (int)(s.size()-decimal-2)) ;
					}
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
				nelm++;				
				connectivity.push_back(temp);
			}
		}
	}


	Assembly 		m_assembly(nelm, tnod, ndof);
	vector<Node> 	nodes(tnod,Node(ndof));
	if(type == "C3D4")
		vector<Element> mesh(nelm,Tetra());

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


	cout << endl;
	cout << "Connectivity matrix: " << endl << endl;
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

	int dof[nelm*nnod*ndof];
	REP(i, nelm){
		REP(j, m_assembly.connectivity[i].size()){
			REP(k, ndof){
				dof[i*nnod*ndof + j*ndof + k] = (ndof * m_assembly.connectivity[i][j]) - (ndof - k);
			}
		}
	}

	double kg[tnod*ndof*tnod*ndof];
	
	REP(i, tnod*ndof){
		REP(j, tnod*ndof){
			kg[i*tnod*ndof + j] = 0.0;
		}
	}

	double kl[nnod*ndof*nnod*ndof];

	REP(i, nnod*ndof){
		REP(j, nnod*ndof){
			kl[i*nnod*ndof + j] = 1.0;
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
	cudaMalloc((void**)&pkl, (nnod*ndof*nnod*ndof)*sizeof(double));

	cudaMemcpy(pdof, dof, (nelm*nnod*ndof)*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(pkl, kl, (nnod*ndof*nnod*ndof)*sizeof(double), cudaMemcpyHostToDevice);
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
		cout << endl;
	}
}
