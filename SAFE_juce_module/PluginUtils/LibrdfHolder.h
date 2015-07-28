#ifndef LIB_RDF_HOLDER_H_INCLUDED
#define LIB_RDF_HOLDER_H_INCLUDED

/** 
 *  A class for holding onto some useful librdf things.
 */
struct LibrdfHolder
{
    //==========================================================================
    //      Constructor and Destructor
    //==========================================================================
    /** Create a new feature extractor. */
    LibrdfHolder();

    /** Destructor */
    ~LibrdfHolder();

    librdf_world *world; /**< An instance of a librdf world object. */
    librdf_storage *storage; /**< An instance of an in memory librdf storage object. */
    librdf_model *model; /**< An instance of a librdf model object. */
    librdf_serializer *serializer; /**< A librdf serializer for the turtle syntax. */
};

#endif // LIB_RDF_HOLDER_H_INCLUDED
