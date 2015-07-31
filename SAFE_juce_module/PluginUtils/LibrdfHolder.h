#ifndef LIB_RDF_HOLDER_H_INCLUDED
#define LIB_RDF_HOLDER_H_INCLUDED

/** 
 *  A class for holding onto some useful librdf things.
 */
class LibrdfHolder
{
public:
    //==========================================================================
    //      Constructor and Destructor
    //==========================================================================
    /** Create a new feature extractor. */
    LibrdfHolder();

    /** Destructor */
    ~LibrdfHolder();

    //==========================================================================
    //      Useful typedefs
    //==========================================================================
    typedef std::unique_ptr <librdf_node, void (*)(librdf_node*)> NodePointer;
    typedef std::unique_ptr <librdf_uri, void (*)(librdf_uri*)> UriPointer;
    typedef std::unique_ptr <librdf_statement, void (*)(librdf_statement*)> StatementPointer;

    //==========================================================================
    //      librdf objects
    //==========================================================================
    std::unique_ptr <librdf_world, void (*)(librdf_world*)> world; /**< An instance of a librdf world object. */
    std::unique_ptr <librdf_storage, void (*)(librdf_storage*)> storage; /**< An instance of an in memory librdf storage object. */
    std::unique_ptr <librdf_model, void (*)(librdf_model*)> model; /**< An instance of a librdf model object. */
    std::unique_ptr <librdf_serializer, void (*)(librdf_serializer*)> serializer; /**< A librdf serializer for the turtle syntax. */

    //==========================================================================
    //      Ontology URIs
    //==========================================================================
    UriPointer mo; /**< The music ontology uri. */
    UriPointer af; /**< The audio feature ontology uri. */
    UriPointer rdfs; /**< The rdf schema ontology uri. */
    UriPointer prov; /**< The provenance ontology uri. */
    UriPointer qudt; /**< The quantity, unit, dimension and time ontology uri. */
    UriPointer afx; /**< The audio effects ontology uri. */
    UriPointer afxdb; /**< The audio effect database uri. */
    UriPointer xsd; /**< The XML schema ontology uri. */
    UriPointer safe; /**< The safe ontology uri. */
    UriPointer safedb; /**< The safe database uri. */
    UriPointer studio; /**< The studio ontology uri. */
    UriPointer tl; /**< The timeline ontology uri. */
    UriPointer event; /**< The event ontology uri. */

    UriPointer xsdString; /**< The XML schema string uri. */
    UriPointer xsdInteger; /**< The XML schema integer uri. */
    UriPointer xsdDouble; /**< The XML schema double uri. */

    //==========================================================================
    //      Useful Nodes
    //==========================================================================
    NodePointer dummyUser;

    // rdf namespace
    NodePointer rdfType;

    // rdfs namespace
    NodePointer rdfsLabel;
    NodePointer rdfsComment;

    // af namespace
    NodePointer afFeature;
    
    // afx namespace
    NodePointer afxImplementation;
    NodePointer afxHasParameter;
    NodePointer afxNumParameter;
    NodePointer afxDefaultValue;
    NodePointer afxMinValue;
    NodePointer afxMaxValue;
    NodePointer afxParameterId;
    NodePointer afxState;
    NodePointer afxParameterSetting;
    NodePointer afxParameterSettingItem;
    NodePointer afxParameter;

    // prov namespace
    NodePointer provSoftwareAgent;
    NodePointer provActivity;
    NodePointer provWasGeneratedBy;
    NodePointer provWasAssociatedWith;
    NodePointer provAssociation;
    NodePointer provAgent;
    NodePointer provQualifiedAssociation;
    NodePointer provHadRole;
    NodePointer provUsed;
    NodePointer provGenerated;

    // qudt namespace
    NodePointer qudtQuantityValue;
    NodePointer qudtNumericValue;
    NodePointer qudtValue;
    
    // studio namespace
    NodePointer studioTransform;
    NodePointer studioEffect;

    // mo namespace
    NodePointer moSignal;
    NodePointer moTime;

    // tl namespace
    NodePointer tlInterval;
    NodePointer tlOnTimeline;
    NodePointer tlTimeline;
    NodePointer tlInstant;
    NodePointer tlAt;

    // event namespace
    NodePointer eventEvent;
    NodePointer eventTime;

    // safe namespace
    NodePointer safeMetadata;
    NodePointer safeMetadataItem;
    NodePointer safeDescriptor;
    NodePointer safeDescriptorItem;
    NodePointer safeFeatureExtractionTransform;
    
    // safedb namespace
    NodePointer safedbLibxtract;

    //==========================================================================
    //      Add triples
    //==========================================================================
    void addTriple (NodePointer &subject, NodePointer &predicate, NodePointer &object);
    void addTriple (NodePointer &subject, NodePointer &predicate, const String &literalObject);

private:
    static librdf_world* createAndOpenWorld();

};

#endif // LIB_RDF_HOLDER_H_INCLUDED
