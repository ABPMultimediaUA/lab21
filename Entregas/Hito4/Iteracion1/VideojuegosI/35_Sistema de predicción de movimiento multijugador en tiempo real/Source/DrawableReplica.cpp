/*
    Parte de la definicion de la clase DrawableReplica de la cual
    hereda la clase Player y PlayerMate (clase que muestra el player
    remoto).
*/

/////////////////////////////////////////////////////////////////////////////////
// Se escribe en el Bitstream los datos que se quieren enviar.
// Solo se enviaran por ReplicaManager3 cuando haya cambiado alguno.
// Se envia la velocidad (x, z) y mantendra esta velocidad hasta que se cambie.
// Solo se envia la posicion cada 200ms establecidos en _timeUpdatePosition
/////////////////////////////////////////////////////////////////////////////////
RakNet::RM3SerializationResult dwn::DrawableReplica::Serialize(RakNet::SerializeParameters* serializeParameters)
{
    unsigned char data;

    serializeParameters->outputBitstream[0].Write(getVelocity());
    serializeParameters->outputBitstream[0].Write(getRotation());
    serializeParameters->outputBitstream[0].Write(getAnimation());
    if(RakNet::GetTime() - m_lastPosUpdate > _timeUpdatePosition)
    {
        data = 0b1;
        serializeParameters->outputBitstream[0].WriteBits(&data, 1);  // Marca de que enviamos position
        serializeParameters->outputBitstream[0].Write(getPosition());
        m_lastPosUpdate = RakNet::GetTime();
    }
    else
    {
        data = 0b0;
        serializeParameters->outputBitstream[0].WriteBits(&data, 1);  // Marca de que no enviamos position
    }

    return RakNet::RM3SR_BROADCAST_IDENTICALLY;
}

/////////////////////////////////////////////////////////////////////////////////
// Se leer los datos enviados, teniendo el cuenta el bit de marca de si se ha
// enviado o no la posicion.
/////////////////////////////////////////////////////////////////////////////////
void dwn::DrawableReplica::Deserialize(RakNet::DeserializeParameters* deserializeParameters)
{
    deserializeParameters->serializationBitstream[0].Read(m_remoteVel);
    deserializeParameters->serializationBitstream[0].Read(m_remoteRot);
    deserializeParameters->serializationBitstream[0].Read(m_remoteAnim);
    if (deserializeParameters->serializationBitstream[0].ReadBit())  // Si ha enviado posición
    {
        deserializeParameters->serializationBitstream[0].Read(m_remotePos);
        m_updatedPosition = true;
    }
    // Aqui no podemos hacer setPosition. Es solo para coger los parametros
    // y en el update mover
}

/////////////////////////////////////////////////////////////////////////////////
// Se actualizan las variables del objeto.
/////////////////////////////////////////////////////////////////////////////////
void dwn::DrawableReplica::update(RakNet::TimeMS curTime)
{
    if (!NetInstance->isLocalObject(creatingSystemGUID))
    {
        // Objeto creado por red
        setVelocity(m_remoteVel);
        setRotation(m_remoteRot);
        setAnimation(m_remoteAnim);
        if (m_updatedPosition)
        {
            DrawablePhysics::setPosition(m_remotePos);
            m_updatedPosition = false;
        }
    }
}
