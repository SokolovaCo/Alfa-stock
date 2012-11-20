#pragma once
#ifndef singleton_hpp__
#define singleton_hpp__

template< class T >
class singleton
{
private:
    singleton();
    singleton( const singleton& );
    singleton& operator = ( const singleton& );
    ~singleton() {};

public:
    static T& instance()
    {
        static T tmp;
        return tmp;
    }

    struct ForceInit
    { 
        ForceInit()
        {
            instance();
        } 
    };
};

#endif // singleton_hpp__
