#ifndef LIB_RDF_HOLDER_H_INCLUDED
#define LIB_RDF_HOLDER_H_INCLUDED

struct LibrdfHolder
{
    LibrdfHolder();
    ~LibrdfHolder();

    librdf_world *world;
    librdf_storage *storage;
    librdf_model *model;
    librdf_serializer *serializer;
};

#endif // LIB_RDF_HOLDER_H_INCLUDED
