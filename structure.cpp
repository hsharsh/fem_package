#include "structure.h"

//Global vector class

//Class : Element

Element::Element(int ndof, int nnod){
	this->ndof 			= ndof;
	this->nnod 			= nnod;
	this->stress 		= vdd(3,vd(3));
	this->strain 		= vdd(3,vd(3));
	this->connectivity 	= vd(nnod);
}

void Element::build_connectivity(vd conn){
	this->connectivity = conn;
}

//Class : Node

Node::Node(){
	this->z 			= vd(3);
	this->x 			= vd(3);
	this->gradz 		= vdd(3,vd(3));

}	