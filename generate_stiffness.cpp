#include <bits/stdc++.h>

using namespace std;

#define DEBUG(x) 	cout << '>' << #x << ':' << x << endl
#define REP(i,n) 	for(ll i=0;i<(n);++i)
#define FOR(i,a,b) 	for(ll i=(a);i<(b);++i)
#define DFOR(i,a,b) for(ll i=(a);i>=(b);--i)
#define v 			vector<vector<double> >
#define ll 			long long


int main(){
	ll nelm, nnod;
	cout << "Enter the number of elements: ";
	cin >> nelm;
	nnod = nelm + 1;
	double conn[nelm][2];

	REP(i,nelm){
		conn[i][0] = i+1;
		conn[i][1] = i+2;
	}
/*	
	REP(i, nelm){
		cout << conn[i][0] << " " << conn[i][1] << endl;
	}
*/
	ll ndof;
	cout << "Enter the degrees of freedom: ";
	cin >> ndof;
/*	
	ll kg = zeros(ndof*nnod);          % Declaration of the global stiffness matrix.
kl = rand(ndof*2);              % Declaration of a random local stiffness matrix.

for lmn = 1:nelm
    n1 = conn(lmn,1);
    n2 = conn(lmn,2);
    dof = zeros(1, 2*ndof);
    %Construction of dof, which gives information pertaining to which rows/columns correspond to the nodes of the current element.                         
    for i = 1:ndof
    	dof(1, i) = ndof*n1 - (ndof - i);
    	dof(1, i + ndof) = ndof*n2 - (ndof - i);
    end
    %Assembly of the local stiffness matrix to the global stiffness matrix.
    kg(dof,dof) = kg(dof,dof) + kl;
end

spy(kg); %Plots the sparsity of the global stiffness matrix.
*/
}