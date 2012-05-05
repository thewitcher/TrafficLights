#ifndef HELPER_H
#define HELPER_H

class GA1DBinaryStringGenome;
class GAGenome;
class Junction;

class Helper
{
public:
    static GA1DBinaryStringGenome& genomeToBinaryGenome( GAGenome& genome );
    static Junction* userDataToJunction( GAGenome& genome );
    static int toDec( GAGenome& genome );
};

#endif // HELPER_H
