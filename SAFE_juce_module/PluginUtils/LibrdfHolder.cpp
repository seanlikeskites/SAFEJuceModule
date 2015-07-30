LibrdfHolder::LibrdfHolder()
    : world (createAndOpenWorld(), librdf_free_world),
      storage (librdf_new_storage (world.get(), "hashes", NULL, "hash-type='memory'"), librdf_free_storage),
      model (librdf_new_model (world.get(), storage.get(), NULL), librdf_free_model),
      serializer (librdf_new_serializer (world.get(), NULL, "text/turtle", NULL), librdf_free_serializer),
      // URIs
      mo (librdf_new_uri (world.get(), (const unsigned char*) "http://purl.org/ontology/mo/"), librdf_free_uri),
      af (librdf_new_uri (world.get(), (const unsigned char*) "http://purl.org/ontology/af/"), librdf_free_uri),
      rdfs (librdf_new_uri (world.get(), (const unsigned char*) "http://www.w3.org/2000/01/rdf-schema#"), librdf_free_uri),
      prov (librdf_new_uri (world.get(), (const unsigned char*) "http://www.w3.org/ns/prov#"), librdf_free_uri),
      qudt (librdf_new_uri (world.get(), (const unsigned char*) "http://qudt.org/schema/qudt#"), librdf_free_uri),
      afx (librdf_new_uri (world.get(), (const unsigned char*) "http://something.something/something/"), librdf_free_uri),
      afxdb (librdf_new_uri (world.get(), (const unsigned char*) "http://stuff.stuff/stuff/"), librdf_free_uri),
      xsd (librdf_new_uri (world.get(), (const unsigned char*) "http://www.w3.org/2001/XMLSchema#"), librdf_free_uri),
      safe (librdf_new_uri (world.get(), (const unsigned char*) "http://safe.safe/safe/"), librdf_free_uri),
      safedb (librdf_new_uri (world.get(), (const unsigned char*) "http://safe.safe/safedb/"), librdf_free_uri),
      studio (librdf_new_uri (world.get(), (const unsigned char*) "http://yuk.yuk/yuk/"), librdf_free_uri),
      xsdString (librdf_new_uri_from_uri_local_name (xsd.get(), (const unsigned char*) "string"), librdf_free_uri),
      xsdInteger (librdf_new_uri_from_uri_local_name (xsd.get(), (const unsigned char*) "integer"), librdf_free_uri),
      // Nodes
      rdfType (librdf_new_node_from_node (LIBRDF_MS_type (world.get())), librdf_free_node),
      afxImplementation (librdf_new_node_from_uri_local_name (world.get(), afx.get(), 
                                                              (const unsigned char*) "Implementation"), librdf_free_node),
      provSoftwareAgent (librdf_new_node_from_uri_local_name (world.get(), prov.get(), 
                                                              (const unsigned char*) "SoftwareAgent"), librdf_free_node),
      afxHasParameter (librdf_new_node_from_uri_local_name (world.get(), afx.get(), 
                                                            (const unsigned char*) "has_parameter"), librdf_free_node),
      afxNumParameter (librdf_new_node_from_uri_local_name (world.get(), afx.get(), 
                                                            (const unsigned char*) "NumParameter"), librdf_free_node),
      rdfsLabel (librdf_new_node_from_uri_local_name (world.get(), rdfs.get(), 
                                                      (const unsigned char*) "label"), librdf_free_node),
      afxDefaultValue (librdf_new_node_from_uri_local_name (world.get(), afx.get(), 
                                                            (const unsigned char*) "default_value"), librdf_free_node),
      afxMinValue (librdf_new_node_from_uri_local_name (world.get(), afx.get(), 
                                                        (const unsigned char*) "minimum_value"), librdf_free_node),
      afxMaxValue (librdf_new_node_from_uri_local_name (world.get(), afx.get(), 
                                                        (const unsigned char*) "maximum_value"), librdf_free_node),
      qudtQuantityValue (librdf_new_node_from_uri_local_name (world.get(), qudt.get(), 
                                                              (const unsigned char*) "QuantityValue"), librdf_free_node),
      qudtNumericValue (librdf_new_node_from_uri_local_name (world.get(), qudt.get(), 
                                                             (const unsigned char*) "numericValue"), librdf_free_node),
      afxParameterId (librdf_new_node_from_uri_local_name (world.get(), afx.get(), 
                                                           (const unsigned char*) "parameter_id"), librdf_free_node),
      provActivity (librdf_new_node_from_uri_local_name (world.get(), prov.get(), 
                                                         (const unsigned char*) "Activity"), librdf_free_node),
      studioTransform (librdf_new_node_from_uri_local_name (world.get(), studio.get(), 
                                                            (const unsigned char*) "Transform"), librdf_free_node),
      safeMetadata (librdf_new_node_from_uri_local_name (world.get(), safe.get(), 
                                                         (const unsigned char*) "Metadata"), librdf_free_node),
      safeMetadataItem (librdf_new_node_from_uri_local_name (world.get(), safe.get(), 
                                                             (const unsigned char*) "MetadataItem"), librdf_free_node),
      safeDescriptor (librdf_new_node_from_uri_local_name (world.get(), safe.get(), 
                                                           (const unsigned char*) "Descriptor"), librdf_free_node),
      safeDescriptorItem (librdf_new_node_from_uri_local_name (world.get(), safe.get(), 
                                                             (const unsigned char*) "DescriptorItem"), librdf_free_node),
      rdfsComment (librdf_new_node_from_uri_local_name (world.get(), rdfs.get(), 
                                                        (const unsigned char*) "comment"), librdf_free_node),
      provWasGeneratedBy (librdf_new_node_from_uri_local_name (world.get(), prov.get(), 
                                                               (const unsigned char*) "wasGeneratedBy"), librdf_free_node),
      provWasAssociatedWith (librdf_new_node_from_uri_local_name (world.get(), prov.get(), 
                                                                  (const unsigned char*) "wasAssociatedWith"), librdf_free_node)
{
    // set up namespaces
    librdf_serializer_set_namespace (serializer.get(), mo.get(), "mo");
    librdf_serializer_set_namespace (serializer.get(), af.get(), "af");
    librdf_serializer_set_namespace (serializer.get(), rdfs.get(), "rdfs");
    librdf_serializer_set_namespace (serializer.get(), prov.get(), "prov");
    librdf_serializer_set_namespace (serializer.get(), qudt.get(), "qudt");
    librdf_serializer_set_namespace (serializer.get(), afx.get(), "afx");
    librdf_serializer_set_namespace (serializer.get(), afxdb.get(), "afxdb");
    librdf_serializer_set_namespace (serializer.get(), xsd.get(), "xsd");
    librdf_serializer_set_namespace (serializer.get(), safe.get(), "safe");
    librdf_serializer_set_namespace (serializer.get(), safedb.get(), "safedb");
    librdf_serializer_set_namespace (serializer.get(), studio.get(), "studio");
}

LibrdfHolder::~LibrdfHolder()
{
}

//==========================================================================
//      Add triples
//==========================================================================
void LibrdfHolder::addTriple (NodePointer &subject, NodePointer &predicate, NodePointer &object)
{
    StatementPointer statement (librdf_new_statement_from_nodes (world.get(),
                                                                 librdf_new_node_from_node (subject.get()),
                                                                 librdf_new_node_from_node (predicate.get()),
                                                                 librdf_new_node_from_node (object.get())),
                                librdf_free_statement);
    librdf_model_add_statement (model.get(), statement.get());
}

void LibrdfHolder::addTriple (NodePointer &subject, NodePointer &predicate, const String &literalObject)
{
    NodePointer objectNode (librdf_new_node_from_literal (world.get(), (const unsigned char*) literalObject.toRawUTF8(),
                                                          NULL, 0),
                            librdf_free_node);
    addTriple (subject, predicate, objectNode);
}

librdf_world* LibrdfHolder::createAndOpenWorld()
{
    librdf_world *newWorld = librdf_new_world();
    librdf_world_open (newWorld);
    return newWorld;
}
