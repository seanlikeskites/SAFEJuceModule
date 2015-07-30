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
      qudtQuantityValue (librdf_new_node_from_uri_local_name (world.get(), qudt.get(), 
                                                              (const unsigned char*) "QuantityValue"), librdf_free_node),
      qudtNumericValue (librdf_new_node_from_uri_local_name (world.get(), qudt.get(), 
                                                             (const unsigned char*) "numericValue"), librdf_free_node),
      afxParameterId (librdf_new_node_from_uri_local_name (world.get(), afx.get(), 
                                                           (const unsigned char*) "parameter_id"), librdf_free_node)
{
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
