#include "structure.h"

//	Global Class : Assembly

Assembly::Assembly(ll nelm, ll tnod, int ndof){
	this->nelm 			= nelm;
	this->tnod			= tnod;	
	this->connectivity 	= vdd(nelm,vd());
	this->k_global		= vdd(tnod*ndof,vd(tnod*ndof,0));
}

void Assembly::build_connectivity(vdd connectivity){
	this->connectivity = connectivity;
}


//Class : Node

Node::Node(int ndof){
	this->z 			= vd(3);
	this->x 			= x;
	this->gradz 		= vdd(3,vd(3));
}	

void Node::build_x(vd x){
	this->x = x;
}

//Class : Element

Element::Element(int ndof, int nnod){
	this->ndof 			= ndof;
	this->nnod 			= nnod;
	this->stress 		= vdd(3,vd(3));
	this->strain 		= vdd(3,vd(3));
	this->nodes			= vi(nnod);
}

vdd Element::build_kl(){
	vdd kl(this->nnod* this->ndof,vd(this->nnod*this->ndof,1));
	return kl;
}

//Class : Tetra
Tetra::Tetra():Element(3,4){

}