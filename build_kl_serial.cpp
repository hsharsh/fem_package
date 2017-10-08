#include "structure.h"

using namespace std;

#define ll long long
#define x(node,a,b)  (node[a-1][0]-node[b-1][0])
#define y(node,a,b)  (node[a-1][1]-node[b-1][1])
#define z(node,a,b)  (node[a-1][2]-node[b-1][2])


void build_kl(vdd node){
    vd a(5), b(5), c(5);

    double Jdet=x(node,2,1)*(y(node,2,3)*z(node,3,4)-y(node,3,4)*z(node,2,3))+x(node,3,2)*(y(node,3,4)*z(node,1,2)-y(node,1,2)*z(node,3,4))+x(node,4,3)*(y(node,1,2)*z(node,2,3)-y(node,2,3)*z(node,1,2));

    a[1]=y(node,4,2)*z(node,3,2)-y(node,3,2)*z(node,4,2); 
    b[1]=x(node,3,2)*z(node,4,2)-x(node,4,2)*z(node,3,2); 
    c[1]=x(node,4,2)*y(node,3,2)-x(node,3,2)*y(node,4,2);
    a[2]=y(node,3,1)*z(node,4,3)-y(node,3,4)*z(node,1,3);
    b[2]=x(node,4,3)*z(node,3,1)-x(node,1,3)*z(node,3,4); 
    c[2]=x(node,3,1)*y(node,4,3)-x(node,3,4)*y(node,1,3);
    a[3]=y(node,2,4)*z(node,1,4)-y(node,1,4)*z(node,2,4);
    b[3]=x(node,1,4)*z(node,2,4)-x(node,2,4)*z(node,1,4);
    c[3]=x(node,2,4)*y(node,1,4)-x(node,1,4)*y(node,2,4);
    a[4]=y(node,1,3)*z(node,2,1)-y(node,1,2)*z(node,3,1);
    b[4]=x(node,2,1)*z(node,1,3)-x(node,3,1)*z(node,1,2);
    c[4]=x(node,1,3)*y(node,2,1)-x(node,1,2)*y(node,3,1);

    double B[6][4*3] = {
            {a[1],  0, 0, a[2], 0, 0, a[3], 0, 0, a[4], 0, 0},
            {0, b[1], 0, 0, b[2], 0, 0, b[3], 0, 0, b[4], 0},
            {0, 0, c[1], 0, 0, c[2], 0, 0, c[3], 0, 0, c[4]},
            {b[1], a[1], 0, b[2], a[2], 0, b[3], a[3], 0, b[4], a[4], 0},
            {0, c[1], b[1], 0, c[2], b[2], 0, c[3], b[3], 0, c[4], b[4]},
            {c[1], 0, a[1], c[2], 0, a[2], c[3], 0, a[3], c[4], 0, a[4]},
        };
    double V = Jdet;
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

    double K[12][12] = {0}, kl[12][6] = {0};

    REP(i,12){
        REP(j,6){
            REP(k,6){
                kl[i][j] += B[k][i] * C[k][j];
            }
        }
    }
    REP(i,12){
        REP(j,12){
            REP(k,6){
                K[i][j] += kl[i][k] * B[k][j];
            }
        }
    }

    REP(i,12){
        REP(j,12){
            K[i][j] *= V;
            cout << K[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    vdd node(4,vd(3,0));
    REP(i, 4){
        REP(j, 3){
            cin >> node[i][j];
        }
    }
    build_kl(node);

}
