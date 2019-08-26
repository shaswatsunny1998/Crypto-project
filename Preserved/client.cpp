#include"netinet/in.h"
#include"sys/socket.h"
#include"stdio.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#define MAX 80
#include<netinet/in.h>
#include <string>
#define PORT 8080
#define SA struct sockaddr
using namespace std;

#include <math.h>
#include "FiniteFieldElement.hpp"


namespace Cryptography
{
        template<int P>
        class   EllipticCurve
        {
            public:
                typedef FiniteFieldElement<P> ffe_t;
                class   Point
                {
                    friend  class   EllipticCurve<P>;
                    typedef FiniteFieldElement<P> ffe_t;
                    ffe_t  x_;
                    ffe_t  y_;
                    EllipticCurve    *ec_;
                    void   addDouble(int m, Point& acc)
                    {
                        if ( m > 0 )
                        {
                            Point r = acc;
                            for ( int n=0; n < m; ++n )
                            {
                                r += r;     // doubling step
                            }
                            acc = r;
                        }
                    }
                    Point scalarMultiply(int k, const Point& a)
                    {
                        Point acc = a;
                        Point res = Point(0,0,*ec_);
                        int i = 0, j = 0;
                        int b = k;

                        while( b )
                        {
                            if ( b & 1 )
                            {
                                // bit is set; acc = 2^(i-j)*acc
                                addDouble(i-j,acc);
                                res += acc;
                                j = i;  // last bit set
                            }
                            b >>= 1;
                            ++i;
                        }
                        return res;
                    }
                    void    add(ffe_t x1, ffe_t y1, ffe_t x2, ffe_t y2, ffe_t & xR, ffe_t & yR) const
                    {
                        if ( x1 == 0 && y1 == 0 )
                        {
                            xR = x2;
                            yR = y2;
                            return;
                        }
                        if ( x2 == 0 && y2 == 0 )
                        {
                            xR = x1;
                            yR = y1;
                            return;
                        }
                        if ( y1 == -y2 )
                        {
                            xR = yR = 0;
                            return;
                        }
                        ffe_t s;
                        if ( x1 == x2 && y1 == y2 )
                        {
                            //2P
                            s = (3*(x1.i()*x1.i()) + ec_->a()) / (2*y1);
                            xR = ((s*s) - 2*x1);
                        }
                        else
                        {
                            s = (y1 - y2) / (x1 - x2);
                            xR = ((s*s) - x1 - x2);
                        }

                        if ( s != 0 )
                        {
                            yR = (-y1 + s*(x1 - xR));
                        }
                        else
                        {
                            xR = yR = 0;
                        }
                    }

                    Point(int x, int y)
                    : x_(x),
                      y_(y),
                      ec_(0)
                    {}

                    Point(int x, int y, EllipticCurve<P> & EllipticCurve)
                     : x_(x),
                       y_(y),
                       ec_(&EllipticCurve)
                    {}

                    Point(const ffe_t& x, const ffe_t& y, EllipticCurve<P> & EllipticCurve)
                     : x_(x),
                       y_(y),
                       ec_(&EllipticCurve)
                    {}

                public:
                    static  Point   ONE;

                    // copy ctor
                    Point(const Point& rhs)
                    {
                        x_ = rhs.x_;
                        y_ = rhs.y_;
                        ec_ = rhs.ec_;
                    }
                    // assignment
                    Point& operator=(const Point& rhs)
                    {
                        x_ = rhs.x_;
                        y_ = rhs.y_;
                        ec_ = rhs.ec_;
                        return *this;
                    }
                    // access x component as element of Fp
                    ffe_t x() const { return x_; }
                    // access y component as element of Fp
                    ffe_t y() const { return y_; }
                    unsigned int     Order(unsigned int maxPeriod = ~0) const
                    {
                        Point r = *this;
                        unsigned int n = 0;
                        while( r.x_ != 0 && r.y_ != 0 )
                        {
                            ++n;
                            r += *this;
                            if ( n > maxPeriod ) break;
                        }
                        return n;
                    }
                    // negate
                    Point   operator-()
                    {
                        return Point(x_,-y_);
                    }
                    // ==
                    friend bool    operator==(const Point& lhs, const Point& rhs)
                    {
                        return (lhs.ec_ == rhs.ec_) && (lhs.x_ == rhs.x_) && (lhs.y_ == rhs.y_);
                    }
                    // !=
                    friend bool    operator!=(const Point& lhs, const Point& rhs)
                    {
                        return (lhs.ec_ != rhs.ec_) || (lhs.x_ != rhs.x_) || (lhs.y_ != rhs.y_);
                    }
                    // a + b
                    friend Point operator+(const Point& lhs, const Point& rhs)
                    {
                        ffe_t xR, yR;
                        lhs.add(lhs.x_,lhs.y_,rhs.x_,rhs.y_,xR,yR);
                        return Point(xR,yR,*lhs.ec_);
                    }
                    // a * int
                    friend  Point operator*(int k, const Point& rhs)
                    {
                        return Point(rhs).operator*=(k);
                    }
                    // +=
                    Point& operator+=(const Point& rhs)
                    {
                        add(x_,y_,rhs.x_,rhs.y_,x_,y_);
                        return *this;
                    }
                    // a *= int
                    Point& operator*=(int k)
                    {
                        return (*this = scalarMultiply(k,*this));
                    }
                    friend ostream& operator <<(ostream& os, const Point& p)
                    {
                        return (os << "(" << p.x_ << ", " << p.y_ << ")");
                    }
                };
                typedef EllipticCurve<P> this_t;
                typedef class EllipticCurve<P>::Point point_t;

                EllipticCurve(int a, int b)
                : a_(a),
                  b_(b),
                  m_table_(),
                  table_filled_(false)
                {
                }
                void    CalculatePoints()
                {
                    int x_val[P];
                    int y_val[P];
                    for ( int n = 0; n < P; ++n )
                    {
                        int nsq = n*n;
                        x_val[n] = ((n*nsq) + a_.i() * n + b_.i()) % P;
                        y_val[n] = nsq % P;
                    }

                    for ( int n = 0; n < P; ++n )
                    {
                        for ( int m = 0; m < P; ++m )
                        {
                            if ( x_val[n] == y_val[m] )
                            {
                                m_table_.push_back(Point(n,m,*this));
                            }
                        }
                    }

                    table_filled_ = true;
                }
                Point   operator[](int n)
                {
                    if ( !table_filled_ )
                    {
                        CalculatePoints();
                    }

                    return m_table_[n];
                }
                size_t  Size() const { return m_table_.size(); }
                // the degree P of this EC
                int     Degree() const { return P; }
                FiniteFieldElement<P>  a() const { return a_; }
                FiniteFieldElement<P>  b() const { return b_; }
                template<int T>
                friend ostream& operator <<(ostream& os, const EllipticCurve<T>& EllipticCurve);
                ostream&    PrintTable(ostream &os, int columns=4);

                private:
                    typedef std::vector<Point>  m_table_t;

                    m_table_t                   m_table_;   // table of points
                    FiniteFieldElement<P>       a_;         // paramter a of the EC equation
                    FiniteFieldElement<P>       b_;         // parameter b of the EC equation
                    bool    table_filled_;                  // true if the table has been calculated
        };

        template<int T>
            typename EllipticCurve<T>::Point EllipticCurve<T>::Point::ONE(0,0);

        template<int T>
        ostream& operator <<(ostream& os, const EllipticCurve<T>& EllipticCurve)
        {
            os << "y^2 mod " << T << " = (x^3" << showpos;
            if ( EllipticCurve.a_ != 0 )
            {
                os << EllipticCurve.a_ << "x";
            }

            if ( EllipticCurve.b_.i() != 0 )
            {
                os << EllipticCurve.b_;
            }

            os << noshowpos << ") mod " << T;
            return os;
        }

        template<int P>
        ostream&    EllipticCurve<P>::PrintTable(ostream &os, int columns)
        {
            if ( table_filled_ )
            {
                int col = 0;
                typename EllipticCurve<P>::m_table_t::iterator iter = m_table_.begin();
                for ( ; iter!=m_table_.end(); ++iter )
                {
                    os << "(" << (*iter).x_.i() << ", " << (*iter).y_.i() << ") ";
                    if ( ++col > columns )
                    {
                        os << "\n";
                        col = 0;
                    }
                }
            }
            else
            {
                os << "EllipticCurve, F_" << P;
            }
            return os;
        }
}
namespace   utils
{
    float   frand()
    {
        static float norm = 1.0f / (float)RAND_MAX;
        return (float)rand()*norm;
    }

    int irand(int min, int max)
    {
        return min+(int)(frand()*(float)(max-min));
    }
}

using namespace Cryptography;
using namespace utils;




















int main()
{
    int sockfd, connfd,n;
    struct sockaddr_in servaddr, cli;

    int m1,m2,buff,buff1;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);


    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection with the server failed...\n");
        exit(0);
    }
    else
        printf("Connected to the server..\n");



    if(n=read(sockfd,&buff,sizeof(buff))<0)
    {
        printf("\nError in Reading");
        exit(0);
    }
    else
    {
    }

    if(n=read(sockfd,&buff1,sizeof(buff1))<0)
    {
        printf("\nError in Reading");
        exit(0);
    }
    else
    {
    }
    m2=buff;
    m1=buff1;


    typedef EllipticCurve<263> ec_t;
    ec_t   myEllipticCurve(1,1);
    cout << "The elliptic curve: " << myEllipticCurve << "\n";
    myEllipticCurve.CalculatePoints();
            //cout << "\nPoints on the curve (i.e. the group elements):\n";
            //myEllipticCurve.PrintTable(cout,5);
    cout << "\n\n";
    ec_t::Point P = myEllipticCurve[2];
    cout << "some point P  = " << P << ", 2P = " << (P+P) << "\n";
    ec_t::Point Q = myEllipticCurve[3];
    cout << "some point Q = " << Q << ", P+Q = " << (P+Q) << "\n";
    ec_t::Point R = P;
    R += Q;
    cout << "P += Q = " << R << "\n";
    R = P;
    R += R;
    cout << "P += P = 2P = " << R << "\n";

    cout << "\nEC message encryption example\n===============================================\n\n";
    ec_t::Point G = myEllipticCurve[0];
    while( (G.y() == 0 || G.x() == 0) || (G.Order()<2) )
    {
        int n = (int)(frand()*myEllipticCurve.Size());
        G = myEllipticCurve[n];
    }

    cout << "G = " << G << ", order(G) is " << G.Order() << "\n\n";
    int a = irand(1,myEllipticCurve.Degree()-1);
    ec_t::Point Pa = a*G;  // public key
    cout << "Shaswat's public key Pa = " << a << "*" << G << " = " << Pa << endl<<"\n";
    int b = irand(1,myEllipticCurve.Degree()-1);;
    cout<<"Amitesh's private key is b = "<<b<<endl;
    ec_t::Point Pb = b*G;  // public key
    cout << "Amitesh's public key Pb = " << b << "*" << G << " = " << Pb << endl<<"\n";
    int j = irand(1,myEllipticCurve.Degree()-1);;
    ec_t::Point Pj = j*G;
    cout << "Mam's public key Pj = " << j << "*" << G << " = " << Pj << endl;
    //shared key comes out to be (24,35)
    cout << "\n\n";
    ec_t::Point Pk = a*Pb;
    cout << "Shared secret between Shaswat and Amitesh Pk = " << a << "*" << Pb <<" = " << Pk << endl;
    ec_t::ffe_t c1( m1*Pk.x() );
    ec_t::ffe_t c2( m2*Pk.y() );
    cout << "Message Read from Shaswat = {Pa,(c1,c2)} = {" << Pa << ", (" << c1 << ", " << c2 << ")}\n\n";
    Pk = b*Pa;
    ec_t::ffe_t m1d = c1/Pk.x();
    ec_t::ffe_t m2d = c2/Pk.y();
    cout << "Decrypted message = (" << m1d << ", " << m2d << ")" << endl;
    Pk = j*Pa;
    m1d = c1/Pk.x();
    m2d = c2/Pk.y();
    printf("\nThe OTP received is: %d%d\n",m1,m2);

    int auth;
    printf("Enter the OTP received: ");
    scanf("%d",&auth);
    if(auth==m1*100+m2)
    {
        printf("\nAuthenticated.......");
        printf("\nThank you for choosing this bank.......\n");
    }
    else
    {
        printf("\nAuthentication Failed.......");
        printf("\nTry After Sometime.......\n");
    }

}
