#ifndef STRUCTURE_H
	#define STRUCTURE_H
	#include <bits/stdc++.h>

	using namespace std;

	#define ll 	long long
	#define vdd vector<vector<double> >
	#define vd 	vector<double>
	#define REP(i,n) 	for(ll i=0;i<(n);++i)
	#define FOR(i,a,b) 	for(ll i=(a);i<(b);++i)
	#define DFOR(i,a,b) for(ll i=(a);i>=(b);--i)

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
		void build_connectivity(vd conn);
	};

	class Node{
	private:
		vd z;
		vd x;
		vdd gradz;

	public:
		Node();
	};	

#endif