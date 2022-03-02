#include <iostream>
#include <libAhatNumber.h>

int main() 
{
    ANumber num1("100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    ANumber num2("9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999888888");

    std::cout<<"1."<<"\n";
    std::cout<<num1.toStr().c_str()<<"\n";
    std::cout<<"-"<<"\n";
    std::cout<<num2.toStr().c_str()<<"\n";
    std::cout<<"="<<"\n";
    std::cout<<(num1 - num2).toStr().c_str()<<"\n\n";

    std::cout<<"2."<<"\n";
    std::cout<<num1.toStr().c_str()<<"\n";
    std::cout<<"+"<<"\n";
    std::cout<<num2.toStr().c_str()<<"\n";
    std::cout<<"="<<"\n";
    std::cout<<(num1 + num2).toStr().c_str()<<"\n\n";

    std::cout<<"3."<<"\n";
    std::cout<<num1.toStr().c_str()<<"\n";
    std::cout<<">"<<"\n";
    std::cout<<num2.toStr().c_str()<<"\n";
    std::cout<<"="<<"\n";
    std::cout<<(num1 > num2)<<"\n\n";

    std::cout<<"4."<<"\n";
    std::cout<<num1.toStr().c_str()<<"\n";
    std::cout<<"<="<<"\n";
    std::cout<<num2.toStr().c_str()<<"\n";
    std::cout<<"="<<"\n";
    std::cout<<(num1 <= num2)<<"\n\n\n";


    return 0;
}