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


    //use Brent's method to locate a zero given a sign change.
    //see the wikipedia article: http://en.wikipedia.org/wiki/Brent's_method
    template <class ttype>
    Double L_function <ttype>::
    zeros_zoom_brent(Double L1, Double L2, Double u, Double v)
    {

        Double a=u,b=v,L_a=L1,L_b=L2,c,L_c,L_s,d;
        bool my_flag=true;
        Double tmp,tmp2;
        Double s,x,y,z;
        //Double tol=tolerance2*sqrt(v*v+1);

        if(my_norm(L_a)<my_norm(L_b)){
            tmp=a;a=b;b=tmp;
            tmp=L_a;L_a=L_b;L_b=tmp;
        }
        c=a; L_c=L_a;

        do{
            if(my_verbose>3)
                cout << "#                brent zoom: " << setprecision(DIGITS) << a << " " << b << " " << L_a <<" "  << L_b << endl;
            x=L_a-L_b; y=L_a-L_c; z=L_b-L_c;
            if(y!=0&&z!=0){
                s=a*L_b*L_c/(x*y)-b*L_a*L_c/(x*z)+c*L_a*L_b/(y*z); //inverse quad interpolation
                //cout << setprecision(DIGITS);
                //cout << "quad:     " << s << endl;
            }
            else{
                s=b-L_b*(b-a)/(L_b-L_a); //secant rule
                //cout << setprecision(DIGITS);
                //cout << "secant:   " << s << endl;
            }

            if(a<b){
                tmp=(3*a+b)/4;tmp2=b;
            }
            else{
                tmp2=(3*a+b)/4;tmp=b;
            }
            if ((s<tmp||s>tmp2) || (my_flag &&my_norm(s-b)>= my_norm(b-c) / 2) || (!my_flag && my_norm(s-b)>=my_norm(c-d)/2)){
                s=(a+b)/2; my_flag=true;
                //cout << setprecision(DIGITS);
                //cout << "midpoint: " << s << endl;
            }
            else my_flag=false;

            L_s= real(value(.5+I*s,0,"rotated pure"));
            d=c;
            c=b; L_c=L_b;
            if (L_a*L_s<0){
                b=s;L_b=L_s;
            }
            else{
                a=s;
                L_a=L_s;
            }
            if(my_norm(L_a)< my_norm(L_b)){
                tmp=a;a=b;b=tmp;
                tmp=L_a;L_a=L_b;L_b=tmp;
            }

        }while(abs(L_b)>tolerance3 && abs((b-a)/(abs(b)+1))>tolerance2);
        // sqrt(v*v+1) is only good for zeta. Other L-functions have more
        // precision loss.

        //if(abs(L_b)>tolerance*1000)
        //    cout << "Mofu. Big zero  " << b << " " <<L_b<<endl;


        return(b);


    }

    template <class ttype>
    void L_function <ttype>::
    find_zeros(Double t1, Double t2, Double step_size, const char* filename, const char* message_stamp)
    {
        Double t,x,y;
        Double u,v,tmp2;
        Long count2=0;
        Double previous_zero=t1;

        fstream file;


        if(my_verbose>2) cout << "#            entering find_zeros" << endl;

        if(!strcmp(filename,"cout"))
        {
            cout << setprecision(DIGITS3);
        }
        else
        {
            file.open(filename, ios::out|ios::app);
            file << setprecision(DIGITS3);
        }

        t=t1; u=t;
        x=real(value(.5+I*t,0,"rotated pure"));

        if(my_verbose>1)
        cout << "#        look for sign change " << t << " " << x << endl;


        do{
            t=t+step_size;
            y=real(value(.5+I*t,0,"rotated pure"));
            if(my_verbose>1)
            cout << "#        look for sign change " << t << " " << y << endl;
            v=t;
            if(sn(x)!=sn(y))  //if sign change is found...divide and conquer
                              //until the difference is small.
            {

                tmp2=zeros_zoom_brent(x,y,u,v);
                count2++;

                int tmp_DIGITS = Int(DIGITS3+log(abs(tmp2)+2)/2.3)+1;
                if(!strcmp(filename,"cout"))
                {
                    //cout << tmp2 << endl;
                    cout << message_stamp << " ";
                    if(tmp_DIGITS<DIGITS)
                        cout << setprecision(tmp_DIGITS);
                    else
                        cout << setprecision(DIGITS);
                    cout << tmp2 << " ";
                    cout << setprecision(DIGITS3);
                    if(t1>0)
                    cout << Nmain((tmp2+previous_zero)/2)/2 -Nmain(t1)/2-(count2-1.) << endl;
                    else
                    cout << Nmain((tmp2+previous_zero)/2)/2 -(count2-1.) << endl;
                    previous_zero=tmp2;
                }
                else
                {
                    //file << tmp2 << endl;
                    file << message_stamp << " ";
                    if(tmp_DIGITS<DIGITS)
                        file << setprecision(tmp_DIGITS);
                    else
                        file << setprecision(DIGITS);
                    file << tmp2 << " ";
                    file << setprecision(DIGITS3);
                    if(t1>0)
                    file << Nmain((tmp2+previous_zero)/2)/2 -Nmain(t1)/2-(count2-1.) << endl;
                    else
                    file << Nmain((tmp2+previous_zero)/2)/2-(count2-1.) << endl;
                    previous_zero=tmp2;
                }
            }
            u=t;
            x=y;
        }while((t1<t&&t<t2)||(t2<t&&t<t1));
        if(strcmp(filename,"cout")) file.close();

    }

//The following function is the same as above function. The only difference is that it
//puts the result in the vector result which is passed by reference
    template <class ttype>
    void L_function <ttype>::
    find_zeros_v(Double t1, Double t2, Double step_size, vector<Double> &result)
    {
        Double t,x,y;
        Double u,v,tmp2;
        Long count2=0;
        Double previous_zero=t1;

        t=t1; u=t;
        x=real(value(.5+I*t,0,"rotated pure"));


        do{
            t=t+step_size;
            y=real(value(.5+I*t,0,"rotated pure"));
            v=t;
            if(sn(x)!=sn(y))  //if sign change is found...divide and conquer
                              //until the difference is small.
            {

                tmp2=zeros_zoom_brent(x,y,u,v);
                count2++;
                result.push_back( tmp2);
                previous_zero=tmp2;
            }
            u=t;
            x=y;
        }while((t1<t&&t<t2)||(t2<t&&t<t1));
    }



    template <class ttype>
    int L_function <ttype>::
    compute_rank(bool print_rank){

        Complex w,z;
        Double x,y,h1,h2,tmp_h;
        int r;

        z=value(.5);
        x=abs(z);
        if(x>.00001){
                if(print_rank||my_verbose>3) cout << "#                analytic rank equals "<< 0 << endl;
            return 0;
        }

        h2=.00001;
        y=abs(value(.5+h2));
        if(y>1.e-9){
            x=abs(value(.5+1.01*h2));
            r = Int(rint(lcalc_to_double(abs(log(x)-log(y)))/log(1.01)));
            if(print_rank||my_verbose>3) cout << "#                analytic rank equals "<< r << endl;
            return r;
        }

        h2=.001;
        y=abs(value(.5+h2));
        if(y>1.e-9){
             x=abs(value(.5+1.01*h2));
             r = Int(rint(lcalc_to_double(abs(log(x)-log(y)))/log(1.01)));
             if(print_rank||my_verbose>3) cout << "#                analytic rank equals "<< r << endl;
             return r;
        }

        h1=.001;
        do{
            h2=h1;
            h1=h1*5;
            x=abs(value(.5+h1));
            //cout << x << " multiply by 5, at " << h1<<endl;
        }while(x<1.e-9&&h1<2);
        if(x>1.e-8){
            do{
                do{
                    tmp_h=h1;
                    h1=(h1+h2)/2;
                    x=abs(value(.5+h1));
                    //cout << x << " divide and conquer, at " << h1<<endl;
                }while(x>1.e-8);
                if(x<1.e-9)
                {
                    h2=h1;
                    h1=tmp_h;
                }
            }while(x<1.e-9);
        }
        //y=abs(value(.5+h2));
        y=x;
        x=abs(value(.5+1.01*h1));
        //cout << h1<< " " << x << " " << y << " "<<(log(x)-log(y))/log(1.01)<<endl;
        r = Int(rint(lcalc_to_double(abs(log(x)-log(y)))/log(1.01)));
        if(print_rank||my_verbose>3) cout << "#                analytic rank equals "<< r << endl;
        return (r);

    }


    template <class ttype>
    void L_function <ttype>::
    verify_rank(int rank)
    {
        int analytic_rank=compute_rank();
        if(rank!=analytic_rank)
            cout<< "given rank "<<rank<< " is different than computed analytic rank "<<
        analytic_rank <<endl;
        //else
        //cout<< "given rank "<<rank<< " equals analytic rank"<<endl;
    }


    //elaborate zero finder keeps an array of zeros and goes back to find missing zeros
    //if they are detected via N(T) comparison. Also allows to start after Nth zero.
    //Finds zeros of L(1/2+It) or of L(1/2+It)*L(1/2-It) (depending on whether self dual or not)
    template <class ttype>
    int L_function <ttype>:: //return 0 on success
    //find_zeros(Long count, Long start_N, Double max_refine, int rank, bool do_test_explicit_formula, const char* message_stamp)
    find_zeros(Long count, Long start_N, Double max_refine, int rank, const char* message_stamp)
    {

        if(my_verbose>2)
            cout << "#            Entering find_zeros to look for " << count << " after zero number " << start_N << endl;

        if(count<1) return 0;

        //================================================================================
        //========== Set things up for testing with the explicit formula =================
        //================================================================================
        //int degree; //degree of the L-function
        Double *xxx_zeros; //for sending to the explicit formula test
        int xxx_number_zeros; //number of zeros to store for the explicit formula
                              //if self dual, we also send the -gammas (if gamma != 0).
                              //If not self dual (i.e. if do_negative)
                              //we are already computing zeros above and below
        int xxx_number_zeros_test; //number of zeros to use in the explicit formula (eventually equals xxx_number_zeros)
        int xxx_count=0; //used to count the number of zeros in the xxx_zeros array, mod the size of the array
        int xxx_current_zero=0; //the zero in the xxx_zeros array on which to center
        bool xxx_half_full=false; //once xxx_zeros is half full start doing the explicit formula test
        bool xxx_full=false; //to keep track of when the array is completely full
        Double xxx_T=1,xxx_local_density; // used to determine how many zeros to store for the explicit formula
        Complex *xxx_log_diff_coeffs; //stores Dirichlet coefficients of the logarithmic derivative

        xxx_max_DIFF=0.;

        do{
            xxx_T=xxx_T*1.3;
        }while(Nmain(xxx_T)<Double(2)*double(count+start_N)+100); //the 2 because in the self dual case we only count half the zeros with |t|<T.
                                                    //Extra 2 is no big deal since, in the line below, log is slowly changing, and there's no harm
                                                    //in over estimating the density of zeros slightly
        xxx_local_density=Nmain(xxx_T+1.)-Nmain(xxx_T); //N(T) counts zeros in |t|<T, so the length of the interval in question is 2. However,
                                                        //our array stores zeros above and below the axis, so that's okay

        //double theta=0;
        //for(j=1;j<=a;j++)
        //{
            //theta = theta+gamma[j];
        //}
        //degree=(int)(2*theta);

        xxx_number_zeros = 2*Int(10+DIGITS*xxx_local_density); //we need to multiply by 2 since we want the distance to the zero being tested to exceed Digits
        //and we are taking zeros above and below that zero.

        //if(!do_negative) xxx_number_zeros=xxx_number_zeros*2;
        //we might, at some point in the future have to make this size dynamic if I find that I'm not using enough zeros in the explicit formula test
        //or we might instead make xxx_alpha bigger and take more coefficients of the logarithmic derivative (right now I'm, taking 100)

        if(my_verbose>2) cout << "#            Initializing xxx_zeros array to contain " << xxx_number_zeros << " zeros" << endl;
        xxx_zeros = new Double[xxx_number_zeros];
        for(int i=0;i<xxx_number_zeros;i++) xxx_zeros[i] = 0.;

        int xxx_flag=0; //explicit formula test flag. Equals 1 on fail of the explicit formula.
        bool xxx_called=false; //set to true once the explicit formula is called
        Double xxx_alpha =2.3/DIGITS; //the A to use in phi(gamma)= exp(-alpha (gamma-x_0)^2). See notes in Lexplicit_formula.h

        //if(do_test_explicit_formula){
             xxx_log_diff_coeffs = new Complex[101];
             dirichlet_coeffs_log_diff(100, xxx_log_diff_coeffs); //compute coeffs of -L'(s)/L(s)
        //}
        //================================================================================
        //========== Done: Set things up for testing with the explicit formula ===========
        //================================================================================


        int analytic_rank; //order of vanishing at the critical point

        if(rank>=0) analytic_rank=rank;
        else analytic_rank=compute_rank();


        /* should now be okay to take start_N<analytic_rank, so this error is not used
        if(start_N<analytic_rank){
            cout << "error: start_N (=" << start_N << " ) needs to be > analytic_rank (="<< analytic_rank << ")." << endl;
            exit(1);
        }
        */

        bool do_negative=is_complex(); //controls whether to look for zeros below real axis too.

        Double start_T; //height at which to start searching for (N+1)st, (N+2)nd, etc zeros

        //find the height below which lies the Nth zero.
        //Afterwards, we'll look for zeros starting at that height.


        start_T=0.; //the default, including the situations: start_N==0, or if start_N<analytic_rank.

        //If the user asks to start, say, at the second zero of a rank 5 L-function, then start at the critical
        //point as if start_N=0 and just suppress the first few (2 in this example) zeros at s=1/2.
        int number_zeros_to_suppress=0;
        if(start_N<analytic_rank) number_zeros_to_suppress=start_N;

        else{

            if(do_negative) start_T=Nmain_inverse(start_N); //initial guess. This will be adjusted shortly.
            else start_T=Nmain_inverse(2*start_N-analytic_rank); //take into account not self dual

            Double adjusted_N=1.*start_N; //adjustment needed if self_dual or for zeros at 1/2. Stored as a double since it can take half integral values
            // zeros at s=1/2 should only be counted with weight 1/2 (rather than 1) if self_dual,
            // and weight 1 (rather than 2) if not self dual.
            adjusted_N-=.5*analytic_rank;
            if(!do_negative) adjusted_N*=2; //if is self_dual, zeros come in conjugate pairs
            if(my_verbose>2)
                cout << "#            adjusted_N:" << adjusted_N << endl;
            bool found_T_N=false;  //true if N(start_T) = adjusted_N
            Double incr_T=.1;
            Double N_T=analytic_rank;

            do{
                N_T=N(start_T);
                cout <<setprecision(DIGITS);
                if(my_verbose>2)
                   cout << "#            Searching for T_" << adjusted_N << ": N(" << start_T << " )= " << N_T << " vs adjusted_N: " << adjusted_N << endl;

                if(N_T<adjusted_N-.1){
                    do{
                        start_T+=incr_T;
                        N_T=N(start_T);
                        cout <<setprecision(DIGITS);
                        if(my_verbose>2)
                           cout << "#            Searching for T_" << adjusted_N << ": N(" << start_T << " )= " << N_T << endl;
                    }while(N_T<adjusted_N-.1);
                }

                if(N_T>adjusted_N+.1){
                    do{
                        start_T-=incr_T;
                        N_T=N(start_T);
                        cout <<setprecision(DIGITS);
                        if(my_verbose>2)
                           cout << "#            Searching for T_" << adjusted_N << ": N(" << start_T << " )= " << N_T << endl;
                    }while(N_T>adjusted_N+.1);
                }

                incr_T*=.5; //cout << "incr_T = " << incr_T << endl;

                if(abs(N_T-adjusted_N)<.01){
                    found_T_N=true;
                }

            }while(!found_T_N);
        }
        cout <<setprecision(DIGITS);
        if(my_verbose>2){
            cout<< setprecision(DIGITS);
            cout << "#            find zeros, start_T: " << start_T <<  endl;
        }



        int i,j;
        Double zeros_S[100][3]; // stores list of consecutive zeros: S[n][0]
                                // corresponding S(T) value: S[n][1]
                                // and the sign of the zero (+1 or -1) S[n][2]
        for(i=0;i<=99;i++)
        for(j=0;j<=2;j++)
            zeros_S[i][j]=0.;


        int ii=0; //counts number of local zeros in the zeros_S array
        Double t,x,y;
        Double u,v,tmp=0.;
        Long count2=0; //counts how many zeros have been printed

        Double count_all=0; //counts how many zeros have been found




        if(start_N>=analytic_rank){
            t=start_T;
            count_all=lcalc_to_double(start_N);
            if(!do_negative) count_all-=analytic_rank*.5;
        }
        else{ //if starting at s=1/2

            if(analytic_rank>0){
                count_all=analytic_rank;
                if(!do_negative) count_all=count_all*.5;
                ii=analytic_rank;
                 for(i=1;i<=ii;i++){
                      zeros_S[i][0]=0.;
                      zeros_S[i][1]=0.;
                      zeros_S[i][2]=1.;
                 }
             }

            if(analytic_rank==0) t=0.;
            else t=exp(log(.00001)/analytic_rank); //ad hoc method that will eventually fail


        }


        if(my_verbose>2) cout <<"#            find_zeros: t initialized to: " << t << endl;


        zeros_S[0][0]=t;
        zeros_S[0][1]=0.;
        zeros_S[0][2]=sn(real(value(.5+I*t,0,"rotated pure")));

        u=t;

        Double previous_zero=start_T;
        Double step_size,refined_step_size;






        int i1,i2; //used for looping through blocks for missing zeros
        Double local_average;
        int found_missing=0; //number missing zeros found
        int to_find=0; //number of missing zeros to find
        Double x2,y2,u2,v2,tmp2=0.,tmp3=0.,tmp4; //used to search for missing zeros
        Double x3=0.,x3_c=0.,u3;
        Double x_c=1,y_c=1,x2_c=1,y2_c=1; //used to search for zeros below the real axis
        int number_insert; //1 or 2 according to whether we find zeros below and/or above real axis

        bool also_do_end_pt; //when looking for missing zeros between found zeros,
                                //we need to do one last sign check step in the case
                                //that we are simultaneously looking for zeros of the
                                //conjugate as well.

        bool just_found=false; //for keeping track if a missing zero has just been found


        int number_duplicates=0; //keeps track, when lloking for missing zeros of how many duplicates are detected
                                 //Too many indicates that more precision is needed to distinguish neighbouring zeros


        cout << setprecision(DIGITS3);

        //count multiplicity of zero at 0, then start slightly higher.
        //doesn't matter if I miss a zero inbetween, since this
        //will then be detected by N(T) comparison and searched for.


        x=real(value(.5+I*t,0,"rotated pure"));
        if(do_negative) x_c=real(value(.5-I*t,0,"rotated pure"));

        if(my_verbose>1){
            cout << setprecision(DIGITS);
            cout << "#        look for sign change " << t << " " << x << endl;
        }


        do{

            //XXXXXXXXX might need to adapt the shift for case where the imag part
            //of the lambda's can be large XXXXXXXXXXX


            step_size=.3/density_zeros(t+20); //i.e. increment by .3 the average, determined experimentally. Play with this some more


            if(do_negative) step_size=step_size/2;

            if(my_verbose>4) cout << "#                    find_zeros: step_size= " << step_size <<endl;


            t=t+step_size;
            y=real(value(.5+I*t,0,"rotated pure"));
            if(do_negative) y_c=real(value(.5-I*t,0,"rotated pure"));

            if(my_verbose>1){
                cout << setprecision(DIGITS);
                cout << "#        look for sign change " << t << " " << y << " " << y_c<<endl;
            }

            v=t;
            if(sn(x)!=sn(y))  //if sign change is found...zoom in
            {

                tmp=zeros_zoom_brent(x,y,u,v);

                if(abs((tmp-zeros_S[ii][0]*zeros_S[ii][2])/(tmp+1))>100*tolerance) //make sure it is not a duplicated zero
                {
                    count_all+=1; ii++;

                    zeros_S[ii][0]=tmp;
                    zeros_S[ii][2]=1;


                    if(do_negative)zeros_S[ii][1]=Nmain((tmp+previous_zero)/2) -(count_all-1);
                    else zeros_S[ii][1]=Nmain((tmp+previous_zero)/2)/2 -(count_all-1);
                }


                else if(my_verbose>1){
                   cout << "#        detected duplicate zeros A: " << tmp << endl;
                   cout << "#        detected duplicate zeros B: " << zeros_S[ii][0]*zeros_S[ii][2] << endl;
                   cout << "#        relative difference: " << abs((tmp-zeros_S[ii][0]*zeros_S[ii][2])/(tmp+1)) << endl;
                   cout << " 100 tolerance " << 100*tolerance << endl;
               }

            }
            if(sn(x_c)!=sn(y_c))  //if sign change is found...zoom in
            {

                tmp=-zeros_zoom_brent(y_c,x_c,-v,-u);

                if(abs((tmp-zeros_S[ii][0]*zeros_S[ii][2])/(tmp+1))>100*tolerance) //make sure it is not a duplicated zero
                {
                    count_all+=1; ii++;

                    zeros_S[ii][0]=tmp;
                    zeros_S[ii][2]=-1;
                    if(zeros_S[ii][0]<zeros_S[ii-1][0]){

                       tmp2=zeros_S[ii-1][0];
                       zeros_S[ii-1][0]= zeros_S[ii][0];
                       zeros_S[ii][0]= tmp2;

                       tmp2=zeros_S[ii-1][2];
                       zeros_S[ii-1][2]= zeros_S[ii][2];
                       zeros_S[ii][2]= tmp2;

                       tmp2=zeros_S[ii-1][1];
                       zeros_S[ii-1][1]= Nmain((zeros_S[ii-1][0]+previous_zero)/2) -(count_all-2);
                    }
                    zeros_S[ii][1]=Nmain((tmp+zeros_S[ii-1][0])/2)-(count_all-1);
                }



            }


            if(ii>15){
                local_average=0.;
                for(i=ii;i>=ii-15;i--){
                    local_average=local_average+zeros_S[i][1]/16;
                }
                //cout << "local average: " << ii << " " << local_average << endl;

                if(local_average>.7) to_find=1;
                if(local_average>1.5) to_find=Int(local_average+.5);


                if(to_find>0){

                    if(my_verbose>1){
                        cout << setprecision(DIGITS);
                        cout << "#        missing zeros detected. Looking for " << to_find << "zeros in the interval:" << zeros_S[1][0] << " ... " << zeros_S[ii][0]  <<endl;
                        if(my_verbose>2)
                        for(i=1;i<=ii+found_missing;i++){
                            cout << setprecision(DIGITS); //increase precision for diagnosing purposes
                            cout << "#            zeros : " << zeros_S[i][0]*zeros_S[i][2] << setprecision(6) << " " << zeros_S[i][1]<< endl;
                        }


                    }


                    refined_step_size=step_size/2;
                    if(my_verbose>1){
                        cout << setprecision(DIGITS);
                        cout << "#        refinining step size: " << refined_step_size << endl;
                    }
                    i1=ii-7; i2=i1;


                    found_missing=0;
                    do{

                        if(i2>ii-1+found_missing)i2=ii-1+found_missing;
                        if(i1<1&&count2>0)i1=1; if(i1<1&&count2==0)i1=0;

                        for(i=i1;i<=i2;i++){


                            u2=zeros_S[i][0];
                            if(do_negative){
                                if(zeros_S[i][2]>0){
                                    x2=real(value(.5+I*(u2+refined_step_size),0,"rotated pure"));
                                    x2_c=real(value(.5-I*u2,0,"rotated pure"));
                                }
                                else{
                                    x2=real(value(.5+I*u2,0,"rotated pure"));
                                    x2_c=real(value(.5-I*(u2+refined_step_size),0,"rotated pure"));
                                }


                            }
                            else{
                                u2=zeros_S[i][0]+.5*refined_step_size;
                                x2=real(value(.5+I*u2,0,"rotated pure"));
                            }


                            also_do_end_pt=false;

                            do{
                                v2=u2+refined_step_size;
                                if(my_verbose>3)
                                    cout << setprecision(DIGITS) << "#                v2: " << v2 << " vs " << zeros_S[i+1][0] << endl;

                                if(v2<zeros_S[i+1][0])
                                {
                                    also_do_end_pt=true;
                                    y2=real(value(.5+I*v2,0,"rotated pure"));
                                    if(do_negative) y2_c=real(value(.5-I*v2,0,"rotated pure"));
                                    x3=y2;x3_c=y2_c;u3=v2;
                                    just_found=false;

                                    if(my_verbose>3){
                                        cout<< "#                x2 y2 x2_c y2_c: "
                                        << setprecision(DIGITS) << x2 << " and " << y2
                                        << " :::: " << x2_c << " and " << y2_c << endl;
                                        cout<< "#                their signs: "
                                        << setprecision(DIGITS) << sn(x2) << " and " << sn(y2)
                                        << " :::: " << sn(x2_c) << " and " << sn(y2_c) << endl;
                                    }

                                    if(sn(x2)!=sn(y2)||sn(x2_c)!=sn(y2_c))  //if sign change is found
                                    {

                                        if(my_verbose>2)
                                            cout<< "#            detected missing zero between: " << setprecision(DIGITS) << u2 << " and " << v2 << endl;

                                        just_found=true;
                                        number_insert=0;
                                        if(sn(x2)!=sn(y2)){
                                            tmp2=zeros_zoom_brent(x2,y2,u2,v2);
                                            found_missing++;i2=i2+1;
                                            count_all+=1;
                                            number_insert++;

                                        }
                                        if(sn(x2_c)!=sn(y2_c)){
                                            tmp3=-zeros_zoom_brent(y2_c,x2_c,-v2,-u2);
                                            if(sn(x2)!=sn(y2)&&tmp2>tmp3){tmp4=tmp2;tmp2=tmp3;tmp3=tmp4;}
                                            found_missing++;i2=i2+1;
                                            count_all+=1;
                                            number_insert++;
                                        }
                                        for(j=ii+found_missing;j>=i+1+number_insert;j--){
                                            zeros_S[j][0]=zeros_S[j-number_insert][0];
                                            zeros_S[j][2]=zeros_S[j-number_insert][2];
                                            zeros_S[j][1]=zeros_S[j-number_insert][1]-number_insert;
                                        //cout << "        AAAA: " << zeros_S[j][0]*zeros_S[j][2] << endl;
                                        }
                                        if(number_insert==1&&sn(x2)!=sn(y2)){
                                            zeros_S[i+1][0]=tmp2;
                                            zeros_S[i+1][2]=1;
                                            zeros_S[i+1][1]=zeros_S[i+2][1]-1; //not strictly correct, but close enough
                                        //cout << "        BBBB: " << zeros_S[i+1][0]*zeros_S[i+1][2] << endl;
//XXXXXXXXXXXXX do this more precisely.don't be lazy!
                                        }
                                        else if(number_insert==1&&sn(x2_c)!=sn(y2_c)){
                                            zeros_S[i+1][0]=tmp3;
                                            zeros_S[i+1][2]=-1;
                                            zeros_S[i+1][1]=zeros_S[i+2][1]-1; //not strictly correct, but close enough
                                        //cout << "        CCCC: " << zeros_S[i+1][0]*zeros_S[i+1][2] << endl;
//XXXXXXXXXXXXX do this more precisely.don't be lazy!
                                        }
                                        else{
                                            zeros_S[i+2][0]=tmp3;
                                            zeros_S[i+2][2]=-1;
                                            zeros_S[i+2][1]=zeros_S[i+3][1]-1; //not strictly correct, but close enough
                                            zeros_S[i+1][0]=tmp2;
                                            zeros_S[i+1][2]=1;
                                            zeros_S[i+1][1]=zeros_S[i+2][1]-1; //not strictly correct, but close enough
                                        //cout << "        DDDD: " << zeros_S[i+1][0]*zeros_S[i+1][2] << endl;

                                        }

                                        i=i-2*number_insert;if(i<1)i=1;
                                        //cout << "i = " << i << " zeros_S[i+1]: " << zeros_S[i+1][2]*zeros_S[i+1][0] << endl;


                                    }
                                    //x3=x2;x3_c=x2_c;u3=u2;
                                    x2=y2;x2_c=y2_c;u2=v2;
                                }

                            }while(v2<zeros_S[i+1][0]);

                            //cout << "IIII = " << i << " zeros_S[i+1]: " << zeros_S[i+1][2]*zeros_S[i+1][0] << endl;
                            //in the do_negative case, there is one final sign change check needed
                            if(also_do_end_pt&&!just_found&&found_missing<to_find&&do_negative&&zeros_S[i+1][2]>0){
                            //if(also_do_end_pt&&found_missing==0&&do_negative&&zeros_S[i+1][2]>0){
                                v2=zeros_S[i+1][0];

                                y2_c=real(value(.5-I*v2,0,"rotated pure"));

                                if(sn(x3_c)!=sn(y2_c))
                                {

                                    if(my_verbose>2)
                                         cout<< "#            detected missing zero between: " << setprecision(DIGITS) << -v2 << " and " << -u3 << endl;
                                    tmp3=-zeros_zoom_brent(y2_c,x3_c,-v2,-u3);
                                    found_missing++;i2=i2+1;
                                    if(my_verbose>2)
                                        cout<< "#            found missing zero: " << setprecision(DIGITS) << -tmp3 << endl;

                                    count_all+=1;
                                    for(j=ii+found_missing;j>=i+2;j--){
                                        zeros_S[j][0]=zeros_S[j-1][0];
                                        zeros_S[j][2]=zeros_S[j-1][2];
                                        zeros_S[j][1]=zeros_S[j-1][1]-1;
                                        //cout << "        here: " << zeros_S[j][0]*zeros_S[j][2] << endl;
                                    }
                                    zeros_S[i+1][0]=tmp3;
                                    zeros_S[i+1][2]=-1;
                                    zeros_S[i+1][1]=zeros_S[i+2][1]-1;
                                    //cout << "        here insert: " << zeros_S[i+1][0]*zeros_S[i+1][2] << endl;

                                    i=i-2;if(i<1)i=1;
                                 }


                            } //if(do_negative&&zeros_S[i+1][2]>0)
                            else if(also_do_end_pt&&!just_found&&found_missing<to_find&&do_negative&&zeros_S[i+1][2]<0){
                            //else if(also_do_end_pt&&found_missing==0&&do_negative&&zeros_S[i+1][2]<0){
                                v2=zeros_S[i+1][0];
                                y2=real(value(.5+I*v2,0,"rotated pure"));


                                if(sn(x3)!=sn(y2))
                                {

                                    if(my_verbose>2)
                                        cout<< "#            detected missing zero between: " << setprecision(DIGITS) << u3 << " and " << v2 << endl;
                                    tmp2=zeros_zoom_brent(x3,y2,u3,v2);
                                    found_missing++;i2=i2+1;
                                    if(my_verbose>2)
                                        cout<< "#            found missing zero: " << setprecision(DIGITS) << tmp2 << endl;
                                    count_all+=1;
                                    for(j=ii+found_missing;j>=i+2;j--){
                                        zeros_S[j][0]=zeros_S[j-1][0];
                                        zeros_S[j][1]=zeros_S[j-1][1]-1;
                                        zeros_S[j][2]=zeros_S[j-1][2];
                                    }
                                    zeros_S[i+1][0]=tmp2;
                                    zeros_S[i+1][2]=1;
                                    zeros_S[i+1][1]=zeros_S[i+2][1]-1;

                                    i=i-2;if(i<1)i=1;

                                }
                             }
                        }//for i
                        refined_step_size=refined_step_size/2;
                        i2=i2+2;i1=i1-2;
                        if(refined_step_size/step_size< .1){i2=i2+1;i1=i1-2;}
                        if(my_verbose>1){
                            cout << setprecision(DIGITS);
                            cout << "#        refinining step size: " << refined_step_size << endl;
                            cout << "#        i1 i2: " << i1 << " " << i2 << endl;
                        }
                    }while(found_missing<to_find && refined_step_size > step_size/max_refine);
                    to_find=0;


                    if(refined_step_size <= step_size/max_refine){
                        cout<<"missing zeros detected." << endl;
                        cout<<"failed to find using refined step sizes of " << refined_step_size << endl;
                        for(i=1;i<=ii+found_missing;i++){
                            cout << setprecision(DIGITS); //increase precision for diagnosing purposes
                            cout << zeros_S[i][0]*zeros_S[i][2] << setprecision(6) << " " << zeros_S[i][1]<< endl;
                        }
                        exit(1);
                    }

                }

            }

            ii+=found_missing; found_missing=0;

            //double check for duplicates amongst neighbours (due to finite precision, on rare occasion
            //the same zero is mistaken as two separate zeros), and, to be safe, also next to neighbours
            //in the case of not self dual. Remove if needed. If there are duplicates, dumping of zeros 
            //is delayed until the next time around or later.

            //Make sure not to run this code on actual duplicates at s=1/2, i.e. when the rank is positive.
            bool duplicates=false;
            int starting_i;
            if (analytic_rank>0) starting_i=analytic_rank+1;
            else starting_i=2;

            for(i=starting_i;i<=ii;i++){
                Double zz=zeros_S[i][0]*zeros_S[i][2];
                Double n_zz=abs(zz);
                if(abs((zz-zeros_S[i-1][0]*zeros_S[i-1][2])/(n_zz+1))<100*tolerance){ //if a duplicate
                    duplicates=true;
                    number_duplicates++;
                    if(my_verbose>1){
                        cout << "#        detected duplicate zeros A: " << zz << endl;
                        cout << "#        detected duplicate zeros B: " << zeros_S[i-1][0]*zeros_S[i-1][2] << endl;
                        cout << "#        relative difference: " << abs((zz-zeros_S[i-1][0]*zeros_S[i-1][2])/(zz+1)) << endl;
                        cout << "#        100 tolerance " << 100*tolerance << endl;
                        cout << "#        recent number duplicates: " << number_duplicates << endl;

                    }
                    for(int j=i;j<=ii-1;j++){ //shift over zeros. adjust N(T) values.
                        zeros_S[j][0]=zeros_S[j+1][0];
                        zeros_S[j][1]=zeros_S[j+1][1]+1;
                        zeros_S[j][2]=zeros_S[j+1][2];
                    }
                    ii--; count_all=count_all-1;
                }
                else if(i>starting_i+1&&abs((zz-zeros_S[i-2][0]*zeros_S[i-2][2])/(n_zz+1))<100*tolerance){ //if a duplicate
                    duplicates=true;
                    number_duplicates++;
                    if(my_verbose>1){
                        cout << "#        detected duplicate zeros A: " << zz << endl;
                        cout << "#        detected duplicate zeros B: " << zeros_S[i-2][0]*zeros_S[i-2][2] << endl;
                        cout << "#        relative difference: " << abs((zz-zeros_S[i-2][0]*zeros_S[i-2][2])/(zz+1)) << endl;
                        cout << "#        100 tolerance " << 100*tolerance << endl;
                    }
                    for(int j=i;j<=ii-1;j++){ //shift over zeros. adjust N(T) values.
                        zeros_S[j][0]=zeros_S[j+1][0];
                        zeros_S[j][1]=zeros_S[j+1][1]+1;
                        zeros_S[j][2]=zeros_S[j+1][2];
                    }
                    ii--; count_all=count_all-1;
                }

            }

            if(number_duplicates>3){
                cout <<"Error: Having trouble distinguishing neighbouring zeros. Try using a higher precision version of lcalc." << endl;
                exit(2);
            }

            //dump up to 10 zeros
            //start dumping once there are enough zeros
            if(ii>=50&&!duplicates){
                number_duplicates=0;

                i=1;
                do{
                    //int tmp_DIGITS = Int(DIGITS3+log(zeros_S[i][0]+2)/2.3)+1;



                    //if(do_test_explicit_formula){
                        if(!xxx_half_full&&xxx_count<xxx_number_zeros/2){ //initially fill up half of the xxx_zeros array
                             xxx_zeros[xxx_count]=zeros_S[i][0]*zeros_S[i][2];
                             xxx_count++;
                             if(!do_negative&&xxx_count>analytic_rank){ //the latter because we don't want to double count zeros at s=1/2
                                 xxx_zeros[xxx_count]=-zeros_S[i][0]*zeros_S[i][2];
                                 xxx_count++;
                             }
                        }
                        else{ //array is half full so now proceed to do explicit formula test, and then place a new zero or pair of zeros
                              //wrapping around to the front end of the array if needed.

                             xxx_half_full=true; //is now half full

                             if(xxx_count<2) xxx_full=true; //i.e. if xxx_count has wrapped around to the beginning of the array

                             if(!xxx_full) xxx_number_zeros_test=xxx_count; else xxx_number_zeros_test=xxx_number_zeros;

                             xxx_flag=0;
                             if(start_N<=analytic_rank||count2>(1+do_negative)*xxx_number_zeros/2){
                                 if(!xxx_full||count2%5==0){ //run the test on the first few zeros and then every 5th zero
                                     //add .5 so as to de-symmetrize the test function, i.e. not an even function. That makes the test more sensitive
                                     //to errors in the zero upon which we are centering since linear terms then appear in the Taylor expansion
                                     //wrt to the error of the centered zero.
                                     xxx_flag = test_explicit_formula(xxx_zeros[xxx_current_zero]+.5, xxx_alpha,xxx_zeros,xxx_number_zeros_test,xxx_log_diff_coeffs,100,"hermite",0); //the zero at the end is for the hermite function of order 0, i.e. Gaussian exponential
                                     xxx_called=true;
                                 }
                             }

                             if(xxx_flag!=0){
                                 cout << "WARNING: FAILURE OF THE EXPLICIT FORMULA. " << endl;
                                 cout << "DUMPING ZEROS in XXX ARRAY AND QUITTING." << endl;
                                 cout << setprecision(DIGITS); //increase output precision to aid in diagnosing
                                 cout << zeros_S[i][0]*zeros_S[i][2] << endl;
                                 for(i=0;i<xxx_number_zeros;i++){
                                     cout << xxx_zeros[i] << endl;
                                     //cout << zeros_S[i][0]*zeros_S[i][2] << " , S(T) approx: " << zeros_S[i][1];
                                     //cout <<  " , L value: " << value(.5+I*zeros_S[i][0]*zeros_S[i][2]) << endl;
                                 }
                                 exit(1);
                             }

                             //place another zero in the list
                             xxx_current_zero=(xxx_current_zero+1)%xxx_number_zeros;
                             xxx_zeros[xxx_count]=zeros_S[i][0]*zeros_S[i][2];
                             xxx_count=(xxx_count+1)%xxx_number_zeros;
                             if(!do_negative){ //and it's negative if self dual
                                  xxx_zeros[xxx_count]=-zeros_S[i][0]*zeros_S[i][2];
                                  xxx_count=(xxx_count+1)%xxx_number_zeros;
                                  xxx_current_zero=(xxx_current_zero+1)%xxx_number_zeros;
                             }

                        }
                    //}
                    if(xxx_called) cout << setprecision(DIGITS_xxx); //this is set in Lexplicit_formula.h
                    else cout << setprecision(Int(DIGITS3+log(zeros_S[i][0]+2)/2.3));

                    cout << message_stamp << " ";
                    //finally, output the zeros. XXXXXXX Add a vector option. XXXXXXXXX
                    count2++;
                    if(count2>number_zeros_to_suppress){

                        cout << zeros_S[i][0]*zeros_S[i][2];

                        //XXXXXXXXXXXXXX added for debugging purposes
                        //if(my_verbose==-1) cout << " " << setprecision(6) << " " << value(.5+I*zeros_S[i][0]*zeros_S[i][2]) << " " << zeros_S[i][1]; 
                        //if(i>1&&my_verbose==-1&&abs(zeros_S[i-1][0]-zeros_S[i][0])< exp(-2.3*(DIGITS3-3))) cout <<
                        //"XXXXXXXXX close zeros detected XXXXXXX " << i << " " << zeros_S[i-1][0] << " " << zeros_S[i][0];

                        cout<<endl;
                    }

                    i++;
                }while(i<=10&&count2<count);


/*
            //check that the explicit formula is satisfied using a test function that picks out local zeros.
            //test function is exp(-alpha(x-x_0-.5)^2) where , here, we set alpha=2.3/Digits, x_0 = current_zero,
            // the -.5 is to desymmetrize the test function so that it is not even about x_0, and thus has linear
            //term in it's Taylor expansion.

            //We basically want to detect anomalies as we spit out zeros one at a time.

            if(do_negative){
                for(i=1;i<=50;i++) xxx_zeros[i-1]=zeros_S[i][0]*zeros_S[i][2];
                //xxx_alpha = 2.3*DIGITS3/my_norm(xxx_zeros[49]-xxx_zeros[0]); 
                xxx_flag = test_explicit_formula(xxx_alpha,xxx_zeros[0], xxx_zeros,50);
            }

            if(xxx_flag==1){
                cout << "WARNING: FAILURE OF THE EXPLICIT FORMULA. DUMPING ZEROS AND QUITTING." << endl;
                cout << setprecision(DIGITS);
                for(i=1;i<=50;i++)
                cout << zeros_S[i][0]*zeros_S[i][2] << " " << zeros_S[i][1]<< endl;
                exit(1);
             }

*/

                for(i=11;i<=ii;i++){
                    zeros_S[i-10][0]=zeros_S[i][0];
                    zeros_S[i-10][2]=zeros_S[i][2];
                    zeros_S[i-10][1]=zeros_S[i][1];
                    //cout << "find zeros: shifting: " << i << " " << zeros_S[i][0] <<endl;
                }
                cout << setprecision(DIGITS3);
                ii=ii-10;
            }
            //}
            previous_zero=tmp;

            u=t;
            x=y;
            x_c=y_c;
        }while(count2<count);

        delete [] xxx_zeros;

        return 0;

    }


    //tests whether the L-function is self dual or not by examining Dirichlet coefficients
    template <class ttype>
    bool L_function <ttype>::
    is_complex(){

        if(my_verbose>2) cout << "#            start is_complex()" << endl;

        bool do_negative=false;

        int n=0;
        if(what_type_L!=-1) //if not the zeta function, check if self dual. If so, do_negative stays false
        do{
            n++;
            if(abs(imag(Complex(dirichlet_coefficient[n])))>.00001){
                do_negative=true;
                if(my_verbose>2) cout << "#            is_complex: Dirichlet coeff " << n << " " << setprecision(DIGITS) << dirichlet_coefficient[n] << endl;
            }
        }while(n<number_of_dirichlet_coefficients&&!do_negative);
        if(my_verbose>2) cout << "#            is_complex() = " << do_negative<< endl;

        return do_negative;

    }
