#include "AudioEngine.h"

irrklang::ISoundSource* dwe::AudioEngine::_soundEscopeta;
irrklang::ISoundSource* dwe::AudioEngine::_soundGrenadeExplosion;
irrklang::ISoundSource* dwe::AudioEngine::_soundAccesoDenegado;
irrklang::ISoundSource* dwe::AudioEngine::_soundPuertaAbierta;
irrklang::ISoundSource* dwe::AudioEngine::_soundGrunyido;
irrklang::ISoundSource* dwe::AudioEngine::_soundEnemigoMuere;
irrklang::ISoundSource* dwe::AudioEngine::_soundGenerador;
irrklang::ISoundSource* dwe::AudioEngine::_soundAnillaGranada;
irrklang::ISoundSource* dwe::AudioEngine::_soundPistolaRecarga;


dwe::AudioEngine* dwe::AudioEngine::Instance()
{
    static AudioEngine instance;
    return &instance;
}

void dwe::AudioEngine::Create()
{
    engine = irrklang::createIrrKlangDevice();
    m_numSounds = 0;
    SetMasterVolume(0.5);

    // Cargar sonidos
    _soundEscopeta          = engine->addSoundSourceFromFile("media/Sounds/DisparoEscopeta.wav");
    _soundGrenadeExplosion  = engine->addSoundSourceFromFile("media/Sounds/Granada.wav");
    _soundAccesoDenegado    = engine->addSoundSourceFromFile("media/Sounds/AccesoDenegado.wav");
    _soundPuertaAbierta     = engine->addSoundSourceFromFile("media/Sounds/PuertaAbierta.wav");
    _soundGrunyido          = engine->addSoundSourceFromFile("media/Sounds/Grunyido.wav");
    _soundEnemigoMuere      = engine->addSoundSourceFromFile("media/Sounds/EnemigoMuere.wav");
    _soundGenerador         = engine->addSoundSourceFromFile("media/Sounds/Boop.wav");
    _soundAnillaGranada     = engine->addSoundSourceFromFile("media/Sounds/AnillaGranada.wav");
    _soundPistolaRecarga    = engine->addSoundSourceFromFile("media/Sounds/PistolaRecarga.wav");

    // Pre-ejecutar para que los guarde en caché y no haga un parón al sonar
    Play2D(_soundEscopeta, 0, false);
    Play2D(_soundGrenadeExplosion, 0, false);
    Play2D(_soundAccesoDenegado, 0, false);
    Play2D(_soundPuertaAbierta, 0, false);
    Play2D(_soundGrunyido, 0, false);
    Play2D(_soundEnemigoMuere, 0, false);
    Play2D(_soundGenerador, 0, false);
    Play2D(_soundAnillaGranada, 0, false);
    Play2D(_soundPistolaRecarga, 0, false);
}

void dwe::AudioEngine::Drop()
{
    engine->drop();
}

void dwe::AudioEngine::SetMasterVolume(float volume)
{
    m_volume = volume;
    engine->setSoundVolume(volume);
}

void dwe::AudioEngine::UpdateListenerPosition(dwe::vec3f pos)
{
    irrklang::vec3df position(pos.x*_ratio, pos.y, pos.z*_ratio);
    irrklang::vec3df rotation(0,0,1);
    engine->setListenerPosition(position, rotation);
}

void dwe::AudioEngine::Play2D(irrklang::ISoundSource* soundSource, float volume, bool loop)
{
    irrklang::ISound* sound = engine->play2D(soundSource, loop, false, true);
    sound->setVolume(volume);
    sound->drop();
}

void dwe::AudioEngine::Play2D(const char* fileName, float volume, bool loop)
{
    irrklang::ISound* sound = engine->play2D(fileName, loop, false, true);
    sound->setVolume(volume);
    sound->drop();
}

void dwe::AudioEngine::Play3D(const char* fileName, dwe::vec3f pos, float volume, bool loop)
{
    irrklang::vec3df position(pos.x*_ratio, pos.y, pos.z*_ratio);
    irrklang::ISound* sound = engine->play3D(fileName, position, loop, false, true);
    sound->setVolume(volume);
    sound->drop();
}

void dwe::AudioEngine::StopAllSounds()
{
    engine->stopAllSounds();
}

/*** GETTERS ***/

float dwe::AudioEngine::GetMasterVolume()
{
    return m_volume;
}
