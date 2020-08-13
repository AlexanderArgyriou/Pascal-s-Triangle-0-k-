#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class BigInt
{
    private:
        std::string Num;

    public:
        inline BigInt() noexcept = default; // Default constructor

        inline BigInt(const std::string &_N) noexcept
            : Num(_N)
        {}  // Constructor

        inline BigInt(const BigInt &other) noexcept
        {
            if (this != &other)
                Num = other.Num;
        }   // Copy constructor

        inline BigInt(const BigInt &&other) noexcept
        {
            if (this != &other)
                Num = std::move(other.Num);
        }   // Move constructor

        inline const BigInt &operator=(const BigInt& op2) noexcept { Num = op2.Num; return *this; }   // operator =
        inline const std::string &GetNum() const noexcept { return Num; }    // GetNnum
        inline bool operator!=(const BigInt &op2) const noexcept { return Num != op2.Num; }   // operator !=
        inline bool operator==(const BigInt &op2) const noexcept { return Num == op2.Num; }   // operator ==

        inline BigInt operator*(const BigInt &op2) const noexcept   // operator *
        {
            int Len1 = this->Num.size();
            int Len2 = op2.Num.size();
            if ( Len1 == 0 || Len2 == 0 )
                return BigInt("0");

            std::vector<int> result( Len1 + Len2, 0 );

            int In1 = 0;
            int In2 = 0;

            for ( int i = Len1 - 1; i >= 0; i-- )
            {
                int Carry = 0;
                int N1 = Num[i] - '0';
                In2 = 0;
           
                for ( int j = Len2 - 1; j >= 0; j-- )
                {
                    int N2 = op2.Num[j] - '0';
                    int sum = N1 * N2 + result[In1 + In2] + Carry;
                    Carry = sum / 10;
                    result[In1 + In2] = sum % 10;
                    In2++;
                }   // for

                if ( Carry > 0 )
                    result[In1 + In2] += Carry;
                In1++;
            }   // for

            int i = result.size() - 1;
            while ( i >= 0 && result[i] == 0 )
                i--;

            if ( i == -1 )
                return BigInt("0");

            std::string Res = "";

            while ( i >= 0 )
                Res += std::to_string(result[i--]);

            return BigInt(Res);
        }   // operator *

        inline BigInt operator-(int N) const noexcept
        {
            std::string::size_type sz;
            int op1 = std::stoi( this->Num, &sz );
            return BigInt( std::to_string( op1 - N ) );
        }   // operator -

        inline BigInt operator+(BigInt &op2) noexcept
        {
            if ( Num.length() > op2.Num.length() )
                std::swap( Num, op2.Num );

            std::string Res;
            int N1 = Num.length(), N2 = op2.Num.length();
            int Diff = N2 - N1;
            int Carry = 0;

            for ( int i = N1 - 1; i >= 0; i-- )
            {
                int sum = ( (Num[i] - '0') + (op2.Num[i + Diff] - '0') + Carry );
                Res.push_back( sum % 10 + '0' );
                Carry = sum / 10;
            }   // for

            for ( int i = N2 - N1 - 1; i >= 0; i-- )
            {
                int sum = ( (op2.Num[i] - '0') + Carry );
                Res.push_back( sum % 10 + '0' );
                Carry = sum / 10;
            }   // for

            if ( Carry )
                Res.push_back( Carry + '0' );

            std::reverse( Res.begin(), Res.end() );

            return BigInt(Res);
        } // operator+

        inline BigInt operator/(const BigInt& op2) noexcept
        {
            BigInt Ans("1");
            while ( (op2 * Ans) != *this )
            {
                BigInt Incr("1");
                Ans = Ans + Incr;
            }
            return Ans;
        }
};  // BigInt

inline BigInt Factorial(BigInt n) 
{
    if ( n == BigInt("0") || n == BigInt("1"))
        return BigInt("1");
    else
        return n * Factorial(n - 1);
}   

inline BigInt NchooseK(int Row, int Term)
{
    return  ((Factorial(BigInt(std::to_string(Row)))) / (Factorial(BigInt(std::to_string(Term))) * 
        Factorial(BigInt(std::to_string(Row - Term)))));
}

int main()
{
   const int Row = 20;
   const int Terms = Row + 1;
   std::string Show;
   for (int i = 0; i < Row * 2; ++i)
       Show += ' ';

   for (int i = 0; i < Row; ++i)
   {
       std::cout << i;
       std::cout << Show;
       for (int j = 0; j <= i; ++j)
           std::cout << NchooseK(i, j).GetNum() << " ";
       if(Show.length())
        Show.erase( Show.begin() );
       std::cout << std::endl;
   }

}
