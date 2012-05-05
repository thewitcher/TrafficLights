#ifndef USERPACKAGE_H
#define USERPACKAGE_H

class BaseAlgorithm;
class Junction;

struct UserPackage
{
    UserPackage( Junction* junction, BaseAlgorithm* baseAlgorithm ):
        m_junction( junction ),
        m_baseAlgorithm( baseAlgorithm )
    {}

    Junction* m_junction;
    BaseAlgorithm* m_baseAlgorithm;
};

#endif // USERPACKAGE_H
