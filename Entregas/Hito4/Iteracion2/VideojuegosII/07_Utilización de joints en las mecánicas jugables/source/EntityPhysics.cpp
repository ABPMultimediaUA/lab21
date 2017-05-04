//...
// Extracto del archivo EntityPhysics reference a la creación de joints

////////////////////
void EntityPhysics::createJointBody(const dwe::vec3f& pos, float width, float height, float32 angleDegrees)
{
    createBody(b2_dynamicBody, pos, width, height, angleDegrees);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x*_ratio, pos.z*_ratio);
    bodyDef.type            = b2_kinematicBody;
    bodyDef.angle           = -(angleDegrees*M_PI/180);  // Lo pasamos a radianes
    bodyDef.fixedRotation   = true;
    bodyDef.angularDamping  = m_damping;
    bodyDef.linearDamping   = m_damping;

    m_bodyJoint = World->createBody(&bodyDef);
    m_bodyJoint->SetUserData(this);  // Sin esta linea no funcionan los callbacks

    // Define another box shape for our dynamic body.
    m_shapeJoint.SetAsBox(0.1, 0.1);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape    = &m_shapeJoint;
    fixtureDef.isSensor = true;

    // Add the shape to the body.
    m_bodyJoint->CreateFixture(&fixtureDef);

    // Prismatic joint
    b2RevoluteJointDef jointDef;
    if (angleDegrees == 90)
        jointDef.Initialize(m_body, m_bodyJoint, m_body->GetWorldPoint(b2Vec2(0,-(height*_ratio/2.0))));
    else
        jointDef.Initialize(m_body, m_bodyJoint, m_body->GetWorldPoint(b2Vec2(-(width*_ratio/2.0),0)));
    jointDef.maxMotorTorque = 10.0;
    jointDef.motorSpeed = 0.0;
    jointDef.enableMotor = true;

    m_revoluteJoint = (b2RevoluteJoint*)World->createJoint(&jointDef);
}

//...