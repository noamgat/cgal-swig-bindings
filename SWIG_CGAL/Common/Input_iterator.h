#ifndef CGAL_SWIG_INPUT_ITERATOR_H
#define CGAL_SWIG_INPUT_ITERATOR_H

#include <SWIG_CGAL/Common/triple.h>

#ifndef SWIG  
template <class T>
struct Iterator_helper{
  
  template <class Iterator>
  static T convert(const Iterator& it,typename boost::enable_if< 
                                                      boost::is_same<
                                                        typename T::cpp_base,
                                                        typename std::iterator_traits<Iterator>::value_type
                                                      >
                                              >::type* =0)
  {
    return T(*it);
  }

  template <class Ti>
  static T convert(const Ti& i,typename boost::enable_if< 
                                    boost::is_same< 
                                      boost::false_type,
                                      typename boost::is_same<
                                        typename T::cpp_base,
                                        typename std::iterator_traits<Ti>::value_type
                                      >::type
                                    >
                                  >::type* =0)
  {
    return T(i);
  }
  

  static T
  default_value(){return T();}
};

template<class T1>
struct Iterator_helper<std::pair<T1,int> >{
  template <class T>
  static std::pair<T1,int> convert(const T& i){
    return std::pair<T1,int>(T1(i->first),i->second);
  }
  
  static std::pair<T1,int>
  default_value(){return std::pair<T1,int>(T1(),-1);}
};

template<class T1>
struct Iterator_helper<std::pair<T1,double> >{
  template <class T>
  static std::pair<T1,double> convert(const T& i){
    return std::pair<T1,double>(T1(i->first),i->second);
  }
  
  static std::pair<T1,double>
  default_value(){return std::pair<T1,double>(T1(),-1);}
};

template<class T1>
struct Iterator_helper<CGAL_SWIG::Triple<T1,int,int> >{
  template <class T>
  static CGAL_SWIG::Triple<T1,int,int> convert(const T& i){
    return CGAL_SWIG::Triple<T1,int,int>(T1(i->first),i->second,i->third);
  }
  
  static CGAL_SWIG::Triple<T1,int,int>
  default_value(){return CGAL_SWIG::Triple<T1,int,int>(T1(),-1,-1);}
};

template<>
struct Iterator_helper<double>{
  template <class T>
  static double convert(const T& i){  return *i; }
  static double default_value(){return 0.;}
};


#endif

#ifdef SWIGPYTHON

#include <SWIG_CGAL/Python/exceptions.h>

#define DECLARE_ITERATOR_CLASS_2(NAME,EXPOSEDNAME)             \
template<class T,class R>                                      \
class EXPOSEDNAME{                                             \
  typename T::NAME cur;                                        \
  typename T::NAME end;                                        \
public:                                                        \
                                                               \
  EXPOSEDNAME(                                                 \
    typename T::NAME cur_,                                     \
    typename T::NAME end_                                      \
  ):cur(cur_),end(end_){}                                      \
                                                               \
  EXPOSEDNAME<T,R> __iter__(){return *this;}                   \
  R next()                                                     \
  {                                                            \
    if (cur!=end)                                              \
      return Iterator_helper<R>::convert ( (cur++) );          \
    throw Stop_iteration();                                    \
    return Iterator_helper<R>::default_value();                \
  }                                                            \
                                                               \
  bool hasNext(){                                              \
    return cur!=end;                                           \
  }                                                            \
};       
#else
#define DECLARE_ITERATOR_CLASS_2(NAME,EXPOSEDNAME)             \
template<class T,class R>                                      \
class EXPOSEDNAME{                                             \
  typename T::NAME cur;                                        \
  typename T::NAME end;                                        \
public:                                                        \
                                                               \
  EXPOSEDNAME(                                                 \
    typename T::NAME cur_,                                     \
    typename T::NAME end_                                      \
  ):cur(cur_),end(end_){}                                      \
                                                               \
  R next()                                                     \
  {                                                            \
    if (cur!=end)                                              \
      return Iterator_helper<R>::convert ( (cur++) );          \
    return Iterator_helper<R>::default_value();                \
  }                                                            \
                                                               \
  bool hasNext(){                                              \
    return cur!=end;                                           \
  }                                                            \
};
#endif



#define DECLARE_CIRCULATOR_CLASS_2(NAME,EXPOSEDNAME)           \
template<class T,class R>                                      \
class EXPOSEDNAME{                                             \
  typename T::NAME cur;                                        \
public:                                                        \
  typedef typename T::NAME cpp_base;                           \
  EXPOSEDNAME( typename T::NAME cur_):cur(cur_){}              \
    EXPOSEDNAME<T,R> __iter__(){return *this;}                 \
  R next() {                                                   \
    return Iterator_helper<R>::convert ( (cur++) );            \
  }                                                            \
  R prev() {                                                   \
    return Iterator_helper<R>::convert ( (cur--) );            \
  }                                                            \
  bool hasNext(){return true; }                                \
};

#define DECLARE_ITERATOR_CLASS(NAME)            DECLARE_ITERATOR_CLASS_2(NAME,CGAL_##NAME)
#define DECLARE_CIRCULATOR_CLASS(NAME)          DECLARE_CIRCULATOR_CLASS_2(NAME,CGAL_##NAME)


//place here iterator wrapper classes to be defined. There are template classes that
//can be reused between class. The idea is data store is that 
//DECLARE_ITERATOR_CLASS(foo) declares template <class T,class R> storing iterator T::foo.
DECLARE_ITERATOR_CLASS(All_cells_iterator)
DECLARE_ITERATOR_CLASS(Finite_cells_iterator)
DECLARE_ITERATOR_CLASS(All_facets_iterator)
DECLARE_ITERATOR_CLASS(Finite_facets_iterator)
DECLARE_ITERATOR_CLASS(Finite_edges_iterator)
DECLARE_ITERATOR_CLASS(Point_iterator)
DECLARE_ITERATOR_CLASS(Halfedge_iterator)
DECLARE_ITERATOR_CLASS(Edge_iterator)
DECLARE_ITERATOR_CLASS(Vertex_iterator)
DECLARE_ITERATOR_CLASS(Facet_iterator)
DECLARE_ITERATOR_CLASS(Plane_iterator)
DECLARE_ITERATOR_CLASS(Cell_iterator)
DECLARE_ITERATOR_CLASS(Finite_vertices_iterator)
DECLARE_ITERATOR_CLASS(All_vertices_iterator)
DECLARE_ITERATOR_CLASS(All_edges_iterator)
DECLARE_ITERATOR_CLASS(Finite_faces_iterator)
DECLARE_ITERATOR_CLASS(All_faces_iterator)
DECLARE_ITERATOR_CLASS(Hidden_vertices_iterator)
DECLARE_ITERATOR_CLASS(Constraint_iterator)
DECLARE_ITERATOR_CLASS(Subconstraint_iterator)
DECLARE_ITERATOR_CLASS(Vertices_in_constraint_iterator)
DECLARE_ITERATOR_CLASS(Context_iterator)
DECLARE_ITERATOR_CLASS(Alpha_iterator)
DECLARE_ITERATOR_CLASS(Alpha_shape_vertices_iterator)
DECLARE_ITERATOR_CLASS(Alpha_shape_edges_iterator)
DECLARE_ITERATOR_CLASS(Boundary_edges_iterator)


#endif //CGAL_SWIG_INPUT_ITERATOR_H