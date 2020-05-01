
#ifndef TESTASS_SINGLETON_H_
#define TESTASS_SINGLETON_H_


namespace testass
{

  template < class T >
  class singleton
  {
      singleton( const singleton< T >& ) = delete; // Non-copy-constructable
      singleton( const singleton< T >&& ) = delete; // Non-move-constructable
      singleton< T >& operator=( const singleton< T >& ) = delete; // Non-copy-assignable
      singleton< T >& operator=( const singleton< T >&& ) = delete; // Non-move-assignable

    private:
      static T* _theInstance;

    protected:
      singleton() { }
      virtual ~singleton() { }

    public:
      static T* createInstance() { if ( _theInstance ) delete _theInstance; _theInstance = new T(); return _theInstance; }
      static T* getInstance() { return _theInstance; }
      static void killInstance() { if ( _theInstance ) delete _theInstance; _theInstance = 0; }

      virtual operator bool () const { return ( _theInstance != 0 ); }
      bool isAlive() const { return ( _theInstance != 0 ); }
  };

  template < class T >
  T* singleton< T >::_theInstance = 0;

}

#endif // TESTASS_SINGLETON_H_
