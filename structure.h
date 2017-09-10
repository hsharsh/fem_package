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
	#define DEBUG(x) 	cout << '>' << #x << ':' << x << endl
	
	class Assembly{
		private:
			ll nelm;
			ll tnod;

		public:
			vdd connectivity;
			vdd k_global;
			Assembly(ll nelm, ll tnod);
			void build_connectivity(ll elem, vd connectivity);
	};

	class Node{
		private:
			vd z;
			vd x;
			vdd gradz;

		public:
			Node(int ndof);
	};

	class Element{
		private:
			vdd stress;
			vdd strain;
			vector<Node> nodes;
			//Material type and material number(based on input file declaration)

		public:
			int ndof;
			int nnod;
			Element();
			vdd build_kl();
	};

#endif