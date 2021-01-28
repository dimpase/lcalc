/*

   Copyright (C) 2001,2002,2003,2004 Michael Rubinstein

   This file is part of the L-function package L.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   Check the License for details. You should have received a copy of it, along
   with the package; see the file 'COPYING'. If not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

*/

#include "Lelliptic.h"

//returns 0 if initialization goes smoothly, 1 if there's an error
// given the elliptic curve
// y^2 + a1 xy + a3 y = x^3 + a2 x^2 + a4 x + a6
// computes the sign, the conductor, and first N_terms dirichlet coefficients
// of the corresponding L-function. The nth dirichlet coefficient is normalized by
// sqrt(n) so as to have functional equation s <-> 1-s rather than s <-> 2-s
//

#ifdef INCLUDE_PARI

// given the elliptic curve
// y^2 + a1 xy + a3 y = x^3 + a2 x^2 + a4 x + a6
// i.e. computes, the sign, the conductor, and first N_terms dirichlet coefficients
// of the corresponding L-function. The nth dirichlet coefficient is normalized by
// sqrt(n)
void data_E(char *a1, char *a2, char *a3, char *a4, char *a6, int N_terms,Double * coeff)
{


    int sign; //sign stores the sign of the functional equation
    Long p; //denotes a prime
    Long m,n;
    Double x,r,tmp,tmp2;
    Long conductor; //the conductor of the elliptic curve

    GEN y, F, E, C;





    //if a1 etc are integers, we can use gaffsg to
    //assign F[1] etc. However, I am treating a1 etc as character
    //strings to allow for larger integers, and therefore use gaffect


    F = cgetg(6, t_VEC);
    //F[1] = lgeti(BIGDEFAULTPREC);
    //F[2] = lgeti(BIGDEFAULTPREC);
    //F[3] = lgeti(BIGDEFAULTPREC);
    //F[4] = lgeti(BIGDEFAULTPREC);
    //F[5] = lgeti(BIGDEFAULTPREC);
    F[1] = (long) cgeti(BIGDEFAULTPREC);
    F[2] = (long) cgeti(BIGDEFAULTPREC);
    F[3] = (long) cgeti(BIGDEFAULTPREC);
    F[4] = (long) cgeti(BIGDEFAULTPREC);
    F[5] = (long) cgeti(BIGDEFAULTPREC);

    //gaffsg(a1,(GEN) F[1]);
    //gaffsg(a2,(GEN) F[2]);
    //gaffsg(a3,(GEN) F[3]);
    //gaffsg(a4,(GEN) F[4]);
    //gaffsg(a6,(GEN) F[5]);

    gaffect(gp_read_str(a1), (GEN) F[1]);
    gaffect(gp_read_str(a2), (GEN) F[2]);
    gaffect(gp_read_str(a3), (GEN) F[3]);
    gaffect(gp_read_str(a4), (GEN) F[4]);
    gaffect(gp_read_str(a6), (GEN) F[5]);

    E = initell(F,NULL,BIGDEFAULTPREC);

    y = cgeti(64);
    C = cgetg(4, t_VEC);

    C=ellglobalred(E);

    x=gtodouble((GEN) C[1]);

    //if(x<1e18) conductor=(Long) (x+.1);

    if(x<Double(1.*my_LLONG_MAX)) conductor=Long(x+.1);

    else{
        cout << "conductor equals " << x << " and is too large" << endl;
        exit(1);
    }


    gaffsg(1, (GEN) y);
    sign = ellrootno(E,y); //sign of the functional equation


    for(n=1;n<=N_terms;n++) coeff[n]=1.;

    n=2;
    do{
        if(isprime(n)){

            p=n;
            gaffsg(p,y);
            coeff[p] = Double(1.*llrint(gtodouble(ellap(E,y))))/sqrt(Double(1.*p));
            //coeff[p] = Double(1.*Long(gtodouble(ellap(E,y))+.1))/sqrt(Double(1.*p));

            if(gtolong(gmod((GEN) E[12],(GEN) y))==0) // if p|discriminant, i.e. bad reduction
            {

               tmp=coeff[p];
               r=tmp*tmp;
               x=Double(1.*p)*Double(1.*p);
               m=Long(x+.1);
               if(m<=N_terms)
               do{
                   coeff[m]=coeff[m]*r;
                   x=x*Double(1.*p);
                   m=Long(x+.1);
                   r=r*tmp;
               }while(m<=N_terms);

            }

            else{ // a(p^(j+1)) = a(p)a(p^j) - p a(p^(j-1)) so normalizng by sqrt
                  // gives coeff[p^(j+1)] = coeff[p] coeff[p^j]-coeff[p^(j-1)]

               x=Double(1.*p)*Double(1.*p);
               m=Long(x+.1);
               if(m<=N_terms)
               do{
                   tmp2=0.;
                   coeff[m]=coeff[m]*(coeff[p]*coeff[m/p]-coeff[m/(p*p)]);
                   x=x*Double(1.*p);
                   m=Long(x+.1);
                   r=r*tmp;
               }while(m<=N_terms);
            }
        }
        else{

            p=1;
            do{
                p++;
            }while(n%p!=0);

            m=p;
            do{
                m=m*p;
            }while(n%m==0&&m<n);

            if(n%m!=0) m=m/p;

            coeff[n]=coeff[m]*coeff[n/m];
        }
//if(n%10000==1) cout << n << endl;
        n++;

    }while(n<=N_terms);

    coeff[0]=1.*sign; coeff[1]=1.*conductor; //the first two spots are used
                                       //for the sign and conductor. The rest are
                                       //used for the Dirichlet coefficients.

}

#endif //ifdef INCLUDE_PARI

