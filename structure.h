#ifndef STRUCTURE_H
	#define STRUCTURE_H
	#include <bits/stdc++.h>

	using namespace std;

	#define ll 			long long
	#define vdd 		vector<vector<double> >
	#define vd 			vector<double>
	#define vi 			vector<int>
	#define REP(i,n) 	for(ll i=0;i<(n);++i)
	#define FOR(i,a,b) 	for(ll i=(a);i<(b);++i)
	#define DFOR(i,a,b) for(ll i=(a);i>=(b);--i)
	#define DEBUG(x) 	cout << '>' << #x << ':' << x << endl
	#define x(node,a,b)  (node[a-1][0]-node[b-1][0])
	#define y(node,a,b)  (node[a-1][1]-node[b-1][1])
	#define z(node,a,b)  (node[a-1][2]-node[b-1][2])
	
	class Assembly{
		private:
			ll nelm;
			ll tnod;

		public:
			vdd connectivity;
			vdd k_global;
			Assembly(ll nelm, ll tnod, int ndof);
			void build_connectivity(vdd connectivity);
	};

	class Node{
		private:
			vd z;
			vd x;
			vdd gradz;

		public:
			Node(int ndof);
			void build_x(vd x);
	};

	class Element{
		private:
			int ndof;			
			vdd stress;
			vdd strain;
			vi nodes;
			//Material type and material number(based on input file declaration)

		public:
			int nnod;
			Element(int ndof, int nnod);
	};

	ll stoll(string s);

#endif