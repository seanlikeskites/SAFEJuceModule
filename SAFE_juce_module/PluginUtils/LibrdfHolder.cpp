LibrdfHolder::LibrdfHolder()
{
    // Initialise library 
    world = librdf_new_world();
    librdf_world_open (world);

    // Initialise storage, model and turtle serializer 
    storage = librdf_new_storage (world, "hashes", NULL, "hash-type='memory'");
    model = librdf_new_model (world, storage, NULL);
    serializer = librdf_new_serializer (world, NULL, "text/turtle", NULL);
}

LibrdfHolder::~LibrdfHolder()
{
    // Free everything
    librdf_free_serializer (serializer);
    librdf_free_model (model);
    librdf_free_storage (storage);
    librdf_free_world (world);
}
