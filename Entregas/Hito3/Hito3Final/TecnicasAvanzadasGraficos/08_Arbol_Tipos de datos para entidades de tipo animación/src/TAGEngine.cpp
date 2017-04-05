
////////////////////////////
tag::EAnimation* tag::TAGEngine::createNumAnimations(int numAnimations)
{
    // Creamos malla
    EAnimation* animations = new EAnimation();
    animations->createNumAnimations(numAnimations);//num animaciones

    return animations;
}
////////////////////////////
tag::EAnimation* tag::TAGEngine::createAnimation(EAnimation* animations, const std::string fileName, int numAnimation, int numFrames)
{
    animations->createAnimation(numAnimation,numFrames, fileName);//creamos la animacion con sus frames y sus mallas
    return animations;//la devolvemos
}

/////////////////////////////
tag::GraphicNode* tag::TAGEngine::createNodeAnimations(EAnimation* animations, const vec3f position, const vec3f rotation, GraphicNode* parent)
{
    // Creamos nodo de animation
    GraphicNode* nodoAnimation = createNodePR(position, rotation, parent);
    nodoAnimation->setEntity(animations);//asignamos la animacion al nodo
    return nodoAnimation;

}
//////////////////////////////////