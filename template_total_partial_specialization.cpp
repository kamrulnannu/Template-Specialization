#include <bits/stdc++.h>

using namespace std;

template<int I, class T>
class X                     // #1, primary template
{
    public:
        static const int s = 1;
};

template<int I>
class X<I, int>                   // #2, partial specialization primary template #1
{
    public:
        static const int s = 2;
};

#if 0
Note that there is a concrete type "int I" in primary template. So there is not a
total/explicit/full specialization as show below code which will cause compile
time error.
template<>       // #3 Total or explicit specilization of primary template #1
class X<int, int>
{
    public:
        static const int s = 3;
};
#endif

template<>       // #4 Total or explicit specilization of primary template #1
class X<3, int>
{
    public:
        static const int s = 4;
};

//----------------------------------------------------------------------------------
template<class T1, class T2, class T3>
class Y                              // Primary template
{
    public:
        static const int y = 100;
        Y()
        {
            cout<<"template<T1,T2,T3>:class Y::y="<<y<<endl;
        }
};
template<>
class Y <int, double, char> // Total specialization #1
{
    public:
        static const int y = -1;
        Y()
        {
            cout<<"template<>:class Y<int, double, char>::y="<<y<<endl;
        }
};

template<class T1, class T2>
class Y<T1, T2, float>     // Partial specialization #1
{
    public:
        static const int y = 1;
        Y()
        {
            cout<<"template<T1,T2>:class Y<T1,T2,float>::y="<<y<<endl;
        }
};
template<class T>
class Y<T, T*, float>     // Partial specialization #2
{
    public:
        static const int y = 2;
        Y()
        {
            cout<<"template<T>:class Y<T, T*, float>::y="<<y<<endl;
        }
};
template<class T>
class Y<T, double*, T>     // Partial specialization #3
{
    public:
        static const int y = 3;
        Y()
        {
            cout<<"template<T>:class Y<T,double*,T>::y="<<y<<endl;
        }
};
template<>
class Y<int *, char *, double>     // Total specialization #2
{
    public:
        static const int y = -2;
        Y()
        {
            cout<<"template<>:class Y<int *,char*,doubel>::y="<<y<<endl;
        }
};
template<class T>
class Y<char*, T, int>     // Partial specialization #4
{
    public:
        static const int y = 4;
        Y()
        {
            cout<<"template<T>:class Y<char*,T,int>::y="<<y<<endl;
        }
};
template<class T>
class Y<T, T, T>     // Partial specialization #5
{
    public:
        static const int y = 5;
        Y()
        {
            cout<<"template<T>:class Y<T,T,T>::y="<<y<<endl;
        }
};
int main()
{
    X<0, int> x;      // Declartion here matches with #2
    cout<<x.s<<endl;  // 2

    X<3, int> x1;    // It matches with #4
    cout<<x1.s<<endl;  // 4

    cout<<"-----------------------Y---------------------------\n";
    Y<double, double, double*> y1;   // template<T1,T2,T3>:class Y::y=100, Matches primary template
    Y<int, double, char> y2;         // template<>:class Y<int, double, char>::y=-1, Matches total specialization #1
    Y<int, char, float> y3;          // template<T1,T2>:class Y<T1,T2,float>::y=1, Matches partial specialization #1
    Y<char, char *, float> y4;       // template<T>:class Y<T, T*, float>::y=2, Matches partial specialization #2
    //Y<float, double*, float> y5;
                                   /* y5 is ambiuious because it matches with
                                    * two templates above:
                                    * 1. Partial template# 1:
                                    *    temaplate<T1, T2> class Y <T1,T2, float>,
                                    *                            where T1 = float and T2=double*
                                    *    and
                                    * 2. Partial template# 3:
                                    *    template<T>::class Y<T,double*, T>,
                                    *                   where T=float
                                    *
                                    * See below example of y5 which is not ambiguous
                                    */
    Y<long, double*, long> y5;       // template<T>:class Y<T,double*,T>::y=3, Matches partial specilaization #3
    Y<int*, char*, double> y6;       //template<>:class Y<int *,char*,doubel>::y=-2, Matches total specilaization #2
    Y<char*, long int, int> y7;      //template<T>:class Y<char*,T,int>::y=4, Matches partial specialization #4
    Y<char*, char*, char*> y8;       //template<T>:class Y<T,T,T>::y=5, Matches partial specialization #5
}
