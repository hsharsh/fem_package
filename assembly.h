#ifndef ASSEMBLY_H
	#define ASSEMBLY_H
	#include "structure.h"

	using namespace std;

	vdd build_k(vdd node);

	class Tetra_linear: public Element{
		private:

		public:
			Tetra_linear();
	};

	class Tetra_quadratic: public Element{
		private:

		public:
			Tetra_quadratic();
	};
	
#endif