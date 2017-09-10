#include "structure.h"

//	Global Class : Assembly

Assembly::Assembly(ll nelm, ll tnod){
	this->nelm 			= nelm;
	this->tnod			= tnod;	
	this->connectivity 	= vdd(nelm,vd());
	this->k_global		= vdd(tnod,vd(tnod,0));
}

void Assembly::build_connectivity(ll elem, vd connectivity){
	this->connectivity[elem] = connectivity;
}


//Class : Node

Node::Node(int ndof){
	this->z 			= vd(3);
	this->x 			= vd(3);
	this->gradz 		= vdd(3,vd(3));

}	


//Class : Element

Element::Element(){
	int ndof = 1, nnod = 2;
	this->ndof 			= ndof;
	this->nnod 			= nnod;
	this->stress 		= vdd(3,vd(3));
	this->strain 		= vdd(3,vd(3));
	this->nodes			= vector<Node>(nnod,Node(ndof));
}

vdd Element::build_kl(){
	vdd kl(2,vd(2));
	kl[0][0] = 1;
	kl[0][1] = -1;
	kl[1][0] = -1;
	kl[1][1] = 1;
	return kl;
}