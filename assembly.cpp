#include "structure.h"

using namespace std;

int main(){
	ll nelm, nnod, ndof;
	cout << "Enter the number of elements: ";
	cin >> nelm;
	
	cout << "Enter the number of nodes per element: ";
	cin >> nnod;

	cout << "Enter the dof per node: ";
	cin >> ndof;	

	
	vector<Element> mesh(nelm, Element(ndof,nnod));

/*	
	REP(i, nelm){
		cout << conn[i][0] << " " << conn[i][1] << endl;
	}
*/
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