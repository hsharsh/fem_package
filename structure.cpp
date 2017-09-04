#include <bits/stdc++.h>

using namespace std;

#define ll 	long long
#define vdd vector<vector<double> >
#define vd 	vector<double>
#define REP(i,n) 	for(ll i=0;i<(n);++i)

//Global vector class

class Vectors{

};

class Element{
	private:
		int ndof;
		int nnod;
		vdd stress;
		vdd strain;
		vd 	connectivity;
		//Material type and material number(based on input file declaration)

	public:
		Element(int ndof, int nnod);
};

Element::Element(int ndof, int nnod){
	this->ndof 			= ndof;
	this->nnod 			= nnod;
	this->stress 		= vdd(3,vd(3));
	this->strain 		= vdd(3,vd(3));
	this->connectivity 	= vd(nnod);
}


class Node{
	private:
		vd z;
		vd x;
		vdd gradz;

	public:
		Node();
};

Node::Node(){
	this->z 			= vd(3);
	this->x 			= vd(3);
	this->gradz 		= vdd(3,vd(3));

}


int main(){

	Element a(2,2);
	Node b(),c();
}