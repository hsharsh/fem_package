#include "structure.h"

using namespace std;

#define ll long long


void shape_fn(double Nfx[], double Nfy[], double Nfz[],double Jdet, double x[], double y[], double z[], double zeta[]){ 
	double Jx1 = 4*(x[0]*(zeta[0]-1/4)+x[4]*zeta[0]+x[6]*zeta[1]+x[7]*zeta[3]);
	double Jy1 = 4*(y[0]*(zeta[0]-1/4)+y[4]*zeta[0]+y[6]*zeta[1]+y[7]*zeta[3]);
	double Jz1 = 4*(z[0]*(zeta[0]-1/4)+z[4]*zeta[0]+z[6]*zeta[1]+z[7]*zeta[3]);
	double Jx2 = 4*(x[4]*zeta[0]+x[1]*(zeta[0]-1/4)+x[5]*zeta[1]+x[8]*zeta[3]);
	double Jy2 = 4*(y[4]*zeta[0]+y[1]*(zeta[0]-1/4)+y[5]*zeta[1]+y[8]*zeta[3]);
	double Jz2 = 4*(z[4]*zeta[0]+z[1]*(zeta[0]-1/4)+z[5]*zeta[1]+z[8]*zeta[3]);
	double Jx3 = 4*(x[6]*zeta[0]+x[5]*zeta[0]+x[2]*(zeta[1]-1/4)+x[9]*zeta[3]);
	double Jy3 = 4*(y[6]*zeta[0]+y[5]*zeta[0]+y[2]*(zeta[1]-1/4)+y[9]*zeta[3]);
	double Jz3 = 4*(z[6]*zeta[0]+z[5]*zeta[0]+z[2]*(zeta[1]-1/4)+z[9]*zeta[3]);
	double Jx4 = 4*(x[7]*zeta[0]+x[8]*zeta[0]+x[9]*zeta[1]+x[3]*(zeta[3]-1/4));
	double Jy4 = 4*(y[7]*zeta[0]+y[8]*zeta[0]+y[9]*zeta[1]+y[3]*(zeta[3]-1/4));
	double Jz4 = 4*(z[7]*zeta[0]+z[8]*zeta[0]+z[9]*zeta[1]+z[3]*(zeta[3]-1/4));

	double Jx12=Jx1-Jx2;
	double Jx13=Jx1-Jx3;
	double Jx14=Jx1-Jx4;
	double Jx23=Jx2-Jx3;
	double Jx24=Jx2-Jx4;
	double Jx34=Jx3-Jx4;

	double Jy12=Jy1-Jy2;
	double Jy13=Jy1-Jy3;
	double Jy14=Jy1-Jy4;
	double Jy23=Jy2-Jy3;
	double Jy24=Jy2-Jy4;
	double Jy34=Jy3-Jy4; 

	double Jz12=Jz1-Jz2;
	double Jz13=Jz1-Jz3;
	double Jz14=Jz1-Jz4;
	double Jz23=Jz2-Jz3;
	double Jz24=Jz2-Jz4;
	double Jz34=Jz3-Jz4;


	double Jx21=-Jx12;
	double Jx31=-Jx13;
	double Jx41=-Jx14;
	double Jx32=-Jx23;
	double Jx42=-Jx24;
	double Jx43=-Jx34;


	double Jy21=-Jy12;
	double Jy31=-Jy13;
	double Jy41=-Jy14;
	double Jy32=-Jy23;
	double Jy42=-Jy24;
	double Jy43=-Jy34;


	double Jz21=-Jz12;
	double Jz31=-Jz13;
	double Jz41=-Jz14;
	double Jz32=-Jz23;
	double Jz42=-Jz24;
	double Jz43=-Jz34;


	Jdet=Jx21*(Jy23*Jz34-Jy34*Jz23)+Jx32*(Jy34*Jz12-Jy12*Jz34)+Jx43*(Jy12*Jz23-Jy23*Jz12);


	double a1=Jy42*Jz32-Jy32*Jz42;
	double a2=Jy31*Jz43-Jy34*Jz13;
	double a3=Jy24*Jz14-Jy14*Jz24;
	double a4=Jy13*Jz21-Jy12*Jz31;
	double b1=Jx32*Jz42-Jx42*Jz32;
	double b2=Jx43*Jz31-Jx13*Jz34;
	double b3=Jx14*Jz24-Jx24*Jz14;
	double b4=Jx21*Jz13-Jx31*Jz12;
	double c1=Jx42*Jy32-Jx32*Jy42;
	double c2=Jx31*Jy43-Jx34*Jy13;
	double c3=Jx24*Jy14-Jx14*Jy24;
	double c4=Jx13*Jy21-Jx12*Jy31;

	Nfx[0] = (4*zeta[0] - 1) * a1;
	Nfx[1] = (4*zeta[1] - 1) * a2;
	Nfx[2] = (4*zeta[2] - 1) * a3;
	Nfx[3] = (4*zeta[3] - 1) * a4;
	Nfx[4] = 4*(zeta[0]*a2 + zeta[1]*a1);
	Nfx[5] = 4*(zeta[1]*a3 + zeta[2]*a2);
	Nfx[6] = 4*(zeta[2]*a1 + zeta[0]*a3);
	Nfx[7] = 4*(zeta[0]*a4 + zeta[3]*a1);
	Nfx[8] = 4*(zeta[1]*a4 + zeta[3]*a2);
	Nfx[9] = 4*(zeta[2]*a4 + zeta[3]*a3);

	Nfy[0] = (4*zeta[0] - 1) * b1;
	Nfy[1] = (4*zeta[1] - 1) * b2;
	Nfy[2] = (4*zeta[2] - 1) * b3;
	Nfy[3] = (4*zeta[3] - 1) * b4;
	Nfy[4] = 4*(zeta[0]*b2 + zeta[1]*b1);
	Nfy[5] = 4*(zeta[1]*b3 + zeta[2]*b2);
	Nfy[6] = 4*(zeta[2]*b1 + zeta[0]*b3);
	Nfy[7] = 4*(zeta[0]*b4 + zeta[3]*b1);
	Nfy[8] = 4*(zeta[1]*b4 + zeta[3]*b2);
	Nfy[9] = 4*(zeta[2]*b4 + zeta[3]*b3);

	Nfz[0] = (4*zeta[0] - 1) * c1;
	Nfz[1] = (4*zeta[1] - 1) * c2;
	Nfz[2] = (4*zeta[2] - 1) * c3;
	Nfz[3] = (4*zeta[3] - 1) * c4;
	Nfz[4] = 4*(zeta[0]*c2 + zeta[1]*c1);
	Nfz[5] = 4*(zeta[1]*c3 + zeta[2]*c2);
	Nfz[6] = 4*(zeta[2]*c1 + zeta[0]*c3);
	Nfz[7] = 4*(zeta[0]*c4 + zeta[3]*c1);
	Nfz[8] = 4*(zeta[1]*c4 + zeta[3]*c2);
	Nfz[9] = 4*(zeta[2]*c4 + zeta[3]*c3);

}

void build_B(double B[][30], double Nfx[], double Nfy[], double Nfz[],double Jdet){
	REP(i, 10){
		B[0][3*i] = Nfx[i];
		B[3][3*i+1] = Nfx[i];
		B[5][3*i+2] = Nfx[i];

		B[1][3*i+1] = Nfy[i];
		B[3][3*i] = Nfy[i];
		B[4][3*i+2] = Nfy[i];

		B[1][3*i+2] = Nfz[i];
		B[4][3*i+1] = Nfz[i];
		B[5][3*i] = Nfz[i];
	}

}


int main(){
	freopen("tetraout.o","w",stdout);

	double x[] = {0, 1, 0, 0, 0.5, 0.5, 0, 0, 0.5, 0};
	double y[] = {0, 0 ,1 ,0 ,0 , 0.5, 0.5, 0, 0, 0.5};
	double z[] = {0, 0, 0, 1, 0, 0, 0, 0.5, 0.5, 0.5};

    double v = 0;
    double E = 1;

    double d = (E/(1+v)*(1-2*v));
    double C[6][6] = {
        {d*(1-v) , d*v, d*v, 0, 0, 0},
        {d*v, d*(1-v), d*v, 0, 0, 0},
        {d*v, d*v, d*(1-v), 0, 0, 0},
        {0, 0, 0, d*(0.5-v), 0, 0},
        {0, 0, 0, 0, d*(0.5-v), 0},
        {0, 0, 0, 0, 0, d*(0.5-v)},
    };

    double Kl[30][6] = {0};

    double zeta[][4] = { 
    	{0.25,0.25,0.25,0.25},
    	{0.166666,0.166666,0.166666,0.5},
    	{0.166666,0.166666,0.5,0.166666},
    	{0.166666,0.5,0.166666,0.166666},
    	{0.5,0.166666,0.166666,0.166666},
    };
    double weights[5] = {-0.133333,0.075,0.075,0.075,0.075}; 

    REP(num, 5){
		double B[6][30];
		double Nfx[10] = {0}, Nfy[10] = {0}, Nfz[10] = {0}, Jdet = 0;
		double kl[30][30] = {0};

		shape_fn(Nfx, Nfy, Nfz, Jdet, x, y, z, zeta[num]);	
		build_B(B, Nfx, Nfy, Nfz, Jdet);	


		REP(i,30){
		    REP(j,6){
		        REP(k,6){
		            kl[i][j] += B[k][i] * C[k][j];
		        }
		    }
		}
		REP(i,30){
		    REP(j,30){
		        REP(k,6){
		            Kl[i][j] += kl[i][k] * B[k][j] * weights[num]/(6/* *Jdet */);
		        }
		    }
		}
	}

    REP(i,30){
        REP(j,30){
            cout << Kl[i][j] << " ";
        }
        cout << endl;
    }    

}

